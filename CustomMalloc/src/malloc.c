#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ALIGN4(s)         (((((s) - 1) >> 2) << 2) + 4)
#define BLOCK_DATA(b)     ((b) + 1)
#define BLOCK_HEADER(ptr) ((struct _block *)(ptr) - 1)

static int atexit_registered = 0;
static int num_mallocs       = 0;
static int num_frees         = 0;
static int num_reuses        = 0;
static int num_grows         = 0;
static int num_splits        = 0;
static int num_coalesces     = 0;
static int num_blocks        = 0;
static int num_requested     = 0;
static int max_heap          = 0;

struct _block {
    size_t size;         /* Size of the allocated block */
    struct _block *next; /* Next block in the free list */
    struct _block *prev; /* Previous block in the free list */
    bool free;           /* Is the block free? */
    char padding[3];     /* Padding for alignment */
};

struct _block *heapList = NULL; /* Head of the free list */

void printStatistics(void) {
    printf("\nheap management statistics\n");
    printf("mallocs:\t%d\n", num_mallocs);
    printf("frees:\t\t%d\n", num_frees);
    printf("reuses:\t\t%d\n", num_reuses);
    printf("grows:\t\t%d\n", num_grows);
    printf("splits:\t\t%d\n", num_splits);
    printf("coalesces:\t%d\n", num_coalesces);
    printf("blocks:\t\t%d\n", num_blocks);
    printf("requested:\t%d\n", num_requested);
    printf("max heap:\t%d\n", max_heap);
}

struct _block *findFreeBlock(struct _block **last, size_t size) 
{
   struct _block *curr = heapList;

#if defined FIT && FIT == 0
   /* First fit */

   while (curr && !(curr->free && curr->size >= size)) 
   {
      *last = curr;
      curr  = curr->next;
   }
#endif

// \TODO Put your Best Fit code in this #ifdef block
#if defined BEST && BEST == 0
   /** \TODO Implement best fit here */
   struct _block *bf = NULL;
   while (curr) {
      if (curr->free && curr->size >= size) {
         if (!bf || curr->size < bf->size) {
            bf = curr;
         }
      }
      *last = curr;
      curr = curr->next;
   }
   curr = bf;
#endif

// \TODO Put your Worst Fit code in this #ifdef block
#if defined WORST && WORST == 0
   /** \TODO Implement worst fit here */
   struct _block *wf = NULL;
   while (curr) {
      if (curr->free && curr->size >= size) 
      {
         if (!wf || curr->size > wf->size) 
         {
            wf = curr;
         }
      }
      *last = curr;
      curr = curr->next;
   }
   curr = wf;
#endif

// \TODO Put your Next Fit code in this #ifdef block
#if defined NEXT && NEXT == 0
   /** \TODO Implement next fit here */
   static struct _block *last_checked = NULL;

   
   curr = last_checked ? last_checked->next : heapList;

   while (curr) {
      if (curr->free && curr->size >= size) 
      {
         break;
      }
      *last = curr;
      curr = curr->next;
   }

  
   if (!curr) {
      curr = heapList;
      while (curr && curr != last_checked) 
      {
         if (curr->free && curr->size >= size) 
         {
            break;
         }
         *last = curr;
         curr = curr->next;
      }
   }

   last_checked = curr;
#endif

   return curr;
}


struct _block *growHeap(struct _block *last, size_t size) {
    struct _block *curr = (struct _block *)sbrk(0);
    struct _block *prev = (struct _block *)sbrk(sizeof(struct _block) + size);

    assert(curr == prev);

    if (curr == (struct _block *)-1) 
    {
        return NULL;
    }

    if (heapList == NULL) 
    {
        heapList = curr;
    }

    if (last) 
    {
        last->next = curr;
    }

    curr->size = size;
    curr->next = NULL;
    curr->prev = last;
    curr->free = false;

    num_grows++;
    num_blocks++;
    max_heap += size;


    return curr;
}


void *malloc(size_t size) 
{
    if (atexit_registered == 0) 
    {
        atexit_registered = 1;
        atexit(printStatistics);
    }

    size_t original_size = size;

    // Align the size
    size = ALIGN4(size);
    if (size == 0) 
    {
        return NULL;
    }

    num_requested += original_size;

    struct _block *last = heapList;
    struct _block *next = findFreeBlock(&last, size);

    if (next) 
    {
        // Increment num_reuses because we're reusing an existing free block
        num_reuses++;

        if (next->size >= size + sizeof(struct _block) + 4) 
        {
            // Split the block if it's larger than required
            struct _block *newBlock = (struct _block *)((char *)BLOCK_DATA(next) + size);
            newBlock->size = next->size - size - sizeof(struct _block);
            newBlock->free = true;
            newBlock->next = next->next;
            newBlock->prev = next;

            if (newBlock->next) 
            {
                newBlock->next->prev = newBlock;
            }

            next->next = newBlock;
            next->size = size;
            num_splits++;
            num_blocks++;
        }
    } else 
    {
        // No free block found; grow the heap
        next = growHeap(last, size);
    }

    if (next == NULL) 
    {
        return NULL;
    }

    next->free = false;
    num_mallocs++;
    return BLOCK_DATA(next);
}

void free(void *ptr) 
{
    if (ptr == NULL) 
    {
        return;
    }

    struct _block *curr = BLOCK_HEADER(ptr);
    if (curr->free) 
    { 
    return;
    }
    assert(curr->free == 0);
    curr->free = true;
    num_frees++;


    if (curr->next && curr->next->free) 
    {
        curr->size += sizeof(struct _block) + curr->next->size;
        curr->next = curr->next->next;
        if (curr->next) 
        {
            curr->next->prev = curr;
        }
        num_coalesces++;
        num_blocks--;
    }

    // Coalesce with previous block if it's free
    if (curr->prev && curr->prev->free) 
    {
        curr->prev->size += sizeof(struct _block) + curr->size;
        curr->prev->next = curr->next;
        if (curr->next) 
        {
            curr->next->prev = curr->prev;
        }
        num_coalesces++;
        num_blocks--;
    }
}

void *calloc(size_t nmemb, size_t size) 
{
    size_t totalSize = nmemb * size;
    void *ptr = malloc(totalSize);
    if (ptr) 
    {
        memset(ptr, 0, totalSize);
    }
    return ptr;
}

void *realloc(void *ptr, size_t size) 
{
    if (!ptr) 
    {
        return malloc(size);
    }

    struct _block *curr = BLOCK_HEADER(ptr);
    if (curr->size >= size) 
    {
        return ptr;
    }

    void *newPtr = malloc(size);
    if (newPtr) 
    {
        memcpy(newPtr, ptr, curr->size);
        free(ptr);
    }
    return newPtr;
}
