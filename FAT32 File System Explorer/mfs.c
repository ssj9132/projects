#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <fcntl.h>
#include <dirent.h>

#define WHITESPACE " \t\n"      
#define MAX_COMMAND_SIZE 255    
#define MAX_NUM_ARGUMENTS 32    
int fileFlag = 0; 
uint32_t currentCluster;  
#define FREE 0x00000000  
#define END 0x0FFFFFFF   

struct BPBInfo 
{

    int16_t BPB_BytsPerSec;   
    int8_t BPB_SecPerClus;    
    int16_t BPB_RsvdSecCnt;   
    int8_t BPB_NumFATs;       
    int32_t BPB_FATSz32;      
    int32_t BPB_RootClus;     
    int16_t BPB_ExtFlags;
    int16_t BPB_FSInfo;
    
} bpb;

struct __attribute__((__packed__)) DirectoryEntry 
{
    char DIR_Name[11];
    uint8_t DIR_Attr;
    uint8_t Unused1[8];
    uint16_t DIR_FirstClusterHigh;
    uint8_t Unused2[4];
    uint16_t DIR_FirstClusterLow;
    uint32_t DIR_FileSize;
};

  void exit_cmd(char *command_string, char *headptr)
  {
    free(command_string);
    free(headptr);
    exit(0);
  }


void formatName(const char *filename, char *formattedName) 
{
    memset(formattedName, ' ', 11);
    formattedName[11] = '\0';
    char tempName[256];
    strncpy(tempName, filename, 255);
    tempName[255] = '\0';

    for(int i = 0; tempName[i]; i++)
    {
        tempName[i] = toupper(tempName[i]);
    }

    char *dot = strchr(tempName, '.');
    
    if (dot) 
    {
        *dot = '\0';  
        size_t baseLength = (dot - tempName);
        if(baseLength > 8) baseLength = 8;
        memcpy(formattedName, tempName, baseLength);
        const char *ext = dot + 1;
        size_t extLength = strlen(ext);
        if(extLength > 3) extLength = 3;
        memcpy(formattedName + 8, ext, extLength);
    } 
    else 
    {

        size_t nameLen = strlen(tempName);
        if(nameLen > 8) nameLen = 8;
        memcpy(formattedName, tempName, nameLen);
    }
}

uint32_t getFirstSectorOfCluster(uint32_t cluster, struct BPBInfo *bpb) {
    uint32_t FirstDataSector = bpb->BPB_RsvdSecCnt + (bpb->BPB_NumFATs * bpb->BPB_FATSz32);
    return ((cluster - 2) * bpb->BPB_SecPerClus) + FirstDataSector;
}

int main(int argc, char *argv[]) 
{
  char *command_string = (char*) malloc(MAX_COMMAND_SIZE);
  FILE *file = NULL;

  while (1)
  {
    printf("msh> ");
    
    while (!fgets(command_string, MAX_COMMAND_SIZE, stdin));

    char *token[MAX_NUM_ARGUMENTS];
    int token_count = 0;
    char *argptr;                                         
    char *working_string  = strdup(command_string);
    char *headptr = working_string;
    
    while (((argptr = strsep(&working_string, WHITESPACE)) != NULL) && (token_count < MAX_NUM_ARGUMENTS))
    {
      if (strlen(argptr) > 0) 
      {
        token[token_count] = strndup(argptr, MAX_COMMAND_SIZE);
        token_count++;
      }
    }

    token[token_count] = NULL;

    if (token[0] == NULL) 
    {
      continue;  
    }
    for (int i = 0; token[0][i]; i++) 
    {
    token[0][i] = tolower(token[0][i]);
    }


    if ((strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0) && token[1] == NULL)
    {
      exit_cmd(command_string, headptr);
    }
    else if (strcmp(token[0], "open") == 0)
    {
      if (file != NULL)
      {
        printf("Error: File system image already open.\n");
      }
      else
      {
        file = fopen(token[1], "rb+");
        
        if (file != NULL)
        {
          printf("File opened successfully\n");
          fileFlag = 1;  
        }
        else
        {
          printf("Error: File system image not found.\n");
        }

          fseek(file, 11, SEEK_SET); 
          fread(&bpb.BPB_BytsPerSec, sizeof(bpb.BPB_BytsPerSec), 1, file);

          fseek(file, 13, SEEK_SET); 
          fread(&bpb.BPB_SecPerClus, sizeof(bpb.BPB_SecPerClus), 1, file);

          fseek(file, 14, SEEK_SET); 
          fread(&bpb.BPB_RsvdSecCnt, sizeof(bpb.BPB_RsvdSecCnt), 1, file);

          fseek(file, 16, SEEK_SET); 
          fread(&bpb.BPB_NumFATs, sizeof(bpb.BPB_NumFATs), 1, file);

          fseek(file, 36, SEEK_SET); 
          fread(&bpb.BPB_FATSz32, sizeof(bpb.BPB_FATSz32), 1, file);

          fseek(file, 44, SEEK_SET); 
          fread(&bpb.BPB_RootClus, sizeof(bpb.BPB_RootClus), 1, file);

          fseek(file, 40, SEEK_SET); 
          fread(&bpb.BPB_ExtFlags, sizeof(bpb.BPB_ExtFlags), 1, file);

          fseek(file, 48, SEEK_SET); 
          fread(&bpb.BPB_FSInfo, sizeof(bpb.BPB_FSInfo), 1, file);

          currentCluster = bpb.BPB_RootClus;


      }
    }
else if (strcmp(token[0], "close") == 0)
{
    if (file == NULL) 
    {
        printf("Error: File system not open.\n");
    }
    else
    {
        fclose(file);
        file = NULL;
        fileFlag = 0;  
        printf("File system image closed.\n");
    }
}
    else if(strcmp(token[0], "info") == 0)
    {

       if (!fileFlag)
       {  
        printf("Error: File system image must be opened first.\n");
        continue;
       }


    printf("BPB_BytesPerSec: %d , %x\n", bpb.BPB_BytsPerSec, bpb.BPB_BytsPerSec);
    printf("BPB_SectorsPerClus: %d ,%x\n", bpb.BPB_SecPerClus, bpb.BPB_SecPerClus);
    printf("BPB_RsvdSecCnt: %d ,%x\n", bpb.BPB_RsvdSecCnt, bpb.BPB_RsvdSecCnt);
    printf("BPB_NumFATS: %d ,%x\n", bpb.BPB_NumFATs, bpb.BPB_NumFATs);
    printf("BPB_FATSz32: %d ,%x\n", bpb.BPB_FATSz32, bpb.BPB_FATSz32);
    printf("BPB_ExtFlags: %d , %x\n", bpb.BPB_ExtFlags, bpb.BPB_ExtFlags);
    printf("BPB_RootClus: %d ,%x\n", bpb.BPB_RootClus, bpb.BPB_RootClus);
    printf("BPB_FSInfo: %d , %x\n", bpb.BPB_FSInfo, bpb.BPB_FSInfo);
}

else if (strcmp(token[0], "ls") == 0) 
{
    if (!fileFlag)
       {  
        printf("Error: File system image must be opened first.\n");
        continue;
       }

    uint32_t targetCluster = currentCluster;

    if (token[1] != NULL) 
    {
        if (strcmp(token[1], ".") == 0) 
        {
            targetCluster = currentCluster; 
        } 
        else if (strcmp(token[1], "..") == 0) 
        {
            if (currentCluster != bpb.BPB_RootClus) 
            {
                uint32_t firstSector = getFirstSectorOfCluster(currentCluster, &bpb);
                uint32_t directoryAddress = firstSector * bpb.BPB_BytsPerSec;
                
                fseek(file, directoryAddress, SEEK_SET);
                struct DirectoryEntry dir;
                
                while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
                {
                    if (strncmp(dir.DIR_Name, "..", 2) == 0) 
                    {
                        targetCluster = (dir.DIR_FirstClusterHigh << 16) | dir.DIR_FirstClusterLow;
                        if (targetCluster == 0) 
                        {
                            targetCluster = bpb.BPB_RootClus;
                        }
                        break;
                    }
                }
            }
            else 
            {
                targetCluster = bpb.BPB_RootClus; 
            }
        } 
    }

    uint32_t firstSector = getFirstSectorOfCluster(targetCluster, &bpb);
    uint32_t directoryAddress = firstSector * bpb.BPB_BytsPerSec;
    fseek(file, directoryAddress, SEEK_SET);

    struct DirectoryEntry dir;
    while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
    {
        if (dir.DIR_Name[0] == 0x00) 
        {
            break;
        }

        if ((unsigned char)dir.DIR_Name[0] == 0xE5) 
        {
            continue;
        }

        if (dir.DIR_Attr == 0x0F) 
        {
            continue;
        }

        if (dir.DIR_Attr != 0x01 && dir.DIR_Attr != 0x10 && dir.DIR_Attr != 0x20) 
        {
            continue;
        }

        char name[13] = {0};
        int nameLen = 8;
        while (nameLen > 0 && dir.DIR_Name[nameLen - 1] == ' ') nameLen--;
        strncpy(name, dir.DIR_Name, nameLen);

        if (dir.DIR_Name[8] != ' ') 
        {
            name[nameLen++] = '.';
            int extLength = 3;
            while (extLength > 0 && dir.DIR_Name[8 + extLength - 1] == ' ') extLength--;
            strncpy(name + nameLen, dir.DIR_Name + 8, extLength);
        }

        printf("%s\n", name);
    }
}



else if (strcmp(token[0], "read") == 0 && token[1] != NULL && token[2] != NULL && token[3] != NULL) 
{
    if (!fileFlag)
       {  
        printf("Error: File system image must be opened first.\n");
        continue;
       }

    for (int i = 0; token[1][i]; i++) 
    {
        token[1][i] = toupper(token[1][i]);
    }

    char *filename = token[1];
    int position = atoi(token[2]);
    int numBytes = atoi(token[3]);
    char *option = token_count > 4 ? token[4] : NULL;

    
    uint32_t firstSector = getFirstSectorOfCluster(currentCluster, &bpb);
    uint32_t DirectoryAddress = firstSector * bpb.BPB_BytsPerSec;
    fseek(file, DirectoryAddress, SEEK_SET);

    struct DirectoryEntry dir;
    int found = 0;

    

   
    char formattedName[12] = {0};
    formatName(filename, formattedName);

    
    while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
    {
        if (dir.DIR_Name[0] == 0x00) break; 
        if (dir.DIR_Name[0] == 0xE5) continue; 
        if (strncmp(dir.DIR_Name, formattedName, 11) == 0) 
        {
            found = 1;
            break;
        }
    }
    if (!found) 
    {
        printf("Error: File not found.\n");
        continue;
    }

    uint32_t cluster = (dir.DIR_FirstClusterHigh << 16) | dir.DIR_FirstClusterLow;
    uint32_t firstSectorOfFile = ((cluster - 2) * bpb.BPB_SecPerClus) +
                                 ((bpb.BPB_NumFATs * bpb.BPB_FATSz32) + bpb.BPB_RsvdSecCnt);

    
    fseek(file, firstSectorOfFile * bpb.BPB_BytsPerSec + position, SEEK_SET);

    
    if (position + numBytes > dir.DIR_FileSize) 
    {
        printf("Error: Attempt to read beyond end of file.\n");
        continue;
    }

    
    for (int i = 0; i < numBytes; i++) 
    {
        uint8_t byte;
        if (fread(&byte, 1, 1, file) != 1) 
        {
            printf("Error: Could not read requested number of bytes.\n");
            break;
        }

        
        if (option && strcmp(option, "-ascii") == 0) 
        {
            printf("%c", isprint(byte) ? byte : '.');
        } else if (option && strcmp(option, "-dec") == 0) 
        {
            printf("%d ", byte);
        } else {
            printf("%02X ", byte);  
        }
    }
    printf("\n");
}



else if (strcmp(token[0], "stat") == 0 && token[1] != NULL) 
{

    if (!fileFlag)
    {  
        printf("Error: File system image must be opened first.\n");
        continue;
    }

    if (file == NULL) 
    {
        printf("Error: File system not open.\n");
        return 0;
    }

    
    uint32_t directoryAddress = getFirstSectorOfCluster(currentCluster, &bpb) * bpb.BPB_BytsPerSec;
    fseek(file, directoryAddress, SEEK_SET);

    struct DirectoryEntry dir;
    int found = 0;

    
    char formattedName[12] = {0};
    formatName(token[1], formattedName);

   
    while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
    {
        if (dir.DIR_Name[0] == 0x00) break; 
        if (dir.DIR_Name[0] == 0xE5) continue; 

        if (strncmp(dir.DIR_Name, formattedName, 11) == 0) 
        {
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("Error: File not found.\n");
        return 0;
    }

    
    printf("Name: %.11s\n", dir.DIR_Name);
    printf("Attributes: ");
    if (dir.DIR_Attr & 0x01) printf("0x01 ");
    if (dir.DIR_Attr & 0x10) printf("0x10 ");
    if (dir.DIR_Attr & 0x20) printf("0x20 ");
    printf("\n");

    uint32_t cluster = (dir.DIR_FirstClusterHigh << 16) | dir.DIR_FirstClusterLow;
    printf("Starting Cluster: %d\n", cluster);

    
    if (dir.DIR_Attr & 0x10) 
    {
        printf("Size: 0\n");  
    } else 
    {
        printf("Size: %d\n", dir.DIR_FileSize);
    }
}


else if (strcmp(token[0], "get") == 0) 
{
    if (!fileFlag)
    {  
        printf("Error: File system image must be opened first.\n");
        continue;
    }
    

    if (token[1] == NULL) 
    {
        printf("Error: No filename specified.\n");
        continue;
    }

    char *sourceFilename = token[1];
    char *destFilename = token[2] ? token[2] : sourceFilename;

    char formattedName[12] = {0};
    formatName(sourceFilename, formattedName);

    uint32_t directoryAddress = getFirstSectorOfCluster(currentCluster, &bpb) * bpb.BPB_BytsPerSec;
    fseek(file, directoryAddress, SEEK_SET);

    struct DirectoryEntry dir;
    int found = 0;

    while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
    {
        if (dir.DIR_Name[0] == 0x00) 
        {
            break;
        }

        if (dir.DIR_Name[0] == 0xE5)
        {
            continue;
        } 

        if (strncmp(dir.DIR_Name, formattedName, 11) == 0) 
        {
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("Error: File not found.\n");
        continue;
    }

    uint32_t cluster = (dir.DIR_FirstClusterHigh << 16) | dir.DIR_FirstClusterLow;
    uint32_t remainingBytes = dir.DIR_FileSize;
    uint32_t bytesPerCluster = bpb.BPB_SecPerClus * bpb.BPB_BytsPerSec;
    
    FILE *output = fopen(destFilename, "wb");
    if (!output) 
    {
        printf("Error: Could not create output file '%s'.\n", destFilename);
        continue;
    }

    uint8_t *buffer = (uint8_t *)malloc(bytesPerCluster);
    if (!buffer) 
    {
        printf("Error: Could not allocate buffer.\n");
        fclose(output);
        continue;
    }

   
    while (remainingBytes > 0 && cluster >= 2 && cluster < 0x0FFFFFF8) 
    {
        uint32_t firstSector = ((cluster - 2) * bpb.BPB_SecPerClus + (bpb.BPB_NumFATs * bpb.BPB_FATSz32 + bpb.BPB_RsvdSecCnt)) * bpb.BPB_BytsPerSec;

        fseek(file, firstSector, SEEK_SET);
        
        size_t bytesToRead = (remainingBytes < bytesPerCluster) ? remainingBytes : bytesPerCluster;
        size_t bytesRead = fread(buffer, 1, bytesToRead, file);
        
        if (bytesRead == 0) 
        {
            printf("Error: Failed to read from cluster %u\n", cluster);
            break;
        }

        size_t bytesWritten = fwrite(buffer, 1, bytesRead, output);
        if (bytesWritten != bytesRead) 
        {
            printf("Error: Failed to write all data to output file.\n");
            break;
        }

        remainingBytes -= bytesRead;

        
        uint32_t fatOffset = cluster * 4;
        uint32_t fatSecNum = fatOffset / bpb.BPB_BytsPerSec;
        uint32_t fatEntOffset = fatOffset % bpb.BPB_BytsPerSec;
        uint32_t fatStart = bpb.BPB_RsvdSecCnt * bpb.BPB_BytsPerSec;
        
        
        fseek(file, fatStart + (fatSecNum * bpb.BPB_BytsPerSec) + fatEntOffset, SEEK_SET);
        
    
        uint32_t nextCluster;
        if (fread(&nextCluster, sizeof(uint32_t), 1, file) != 1) 
        {
            printf("Error: Failed to read next cluster from FAT\n");
            break;
        }
        
        cluster = nextCluster & 0x0FFFFFFF;
       
    }

    free(buffer);
    fclose(output);

    if (remainingBytes > 0) 
    {
        printf("Warning: Could not read entire file (missing %u bytes)\n", remainingBytes);
    } 
    else 
    {
        if (token[2]) 
        {
            printf("File '%s' retrieved successfully as '%s'\n", sourceFilename, destFilename);
        } 
        else 
        {
            printf("File '%s' retrieved successfully\n", sourceFilename);
        }
    }
}
else if (strcmp(token[0], "del") == 0) 
{
    if (!fileFlag)
       {  
        printf("Error: File system image must be opened first.\n");
        continue;
       }
    
    if (token[1] == NULL) 
    {
        printf("Error: No filename specified.\n");
        continue;
    }

    uint32_t firstSector = getFirstSectorOfCluster(currentCluster, &bpb);
    uint32_t directoryAddress = firstSector * bpb.BPB_BytsPerSec;

    char formattedName[12] = {0};
    formatName(token[1], formattedName);

    struct DirectoryEntry dir;
    int found = 0;
    long dirEntryPos = 0;

    fseek(file, directoryAddress, SEEK_SET);
    while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
    {
        if (dir.DIR_Name[0] == 0x00) 
        {
            break;
        }
        if (memcmp(dir.DIR_Name, formattedName, 11) == 0 && (dir.DIR_Attr == 0x01 || dir.DIR_Attr == 0x20)) 
        {
            found = 1;
            break;
        }
        dirEntryPos += sizeof(struct DirectoryEntry);
    }

    if (!found) 
    {
        printf("Error: File not found.\n");
        continue;
    }

    fseek(file, directoryAddress + dirEntryPos, SEEK_SET);
    uint8_t deleteMark = 0xE5;
    if (fwrite(&deleteMark, 1, 1, file) != 1) 
    {
        printf("Error: Failed to mark file as deleted.\n");
        continue;
    }
    fflush(file);
    printf("File %s deleted.\n", token[1]);
}

else if (strcmp(token[0], "undel") == 0) 
{
    if (!fileFlag)
       {  
        printf("Error: File system image must be opened first.\n");
        continue;
       }

    

    if (token[1] == NULL) 
    {
        printf("Error: No filename specified.\n");
        continue;
    }

    uint32_t firstSector = getFirstSectorOfCluster(currentCluster, &bpb);
    uint32_t directoryAddress = firstSector * bpb.BPB_BytsPerSec;

 
    char formattedName[12] = {0};
    formatName(token[1], formattedName);

    struct DirectoryEntry dir;
    int found = 0;
    long dirEntryPos = 0;

    fseek(file, directoryAddress, SEEK_SET);
    while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
    {
        if (dir.DIR_Name[0] == 0x00) 
        {
            break;
        }
        
       
        if ((unsigned char)dir.DIR_Name[0] == 0xE5 && strncmp(dir.DIR_Name + 1, formattedName + 1, 10) == 0 && (dir.DIR_Attr == 0x01 || dir.DIR_Attr == 0x20)) 
        {
            found = 1;
            break;
        }
        dirEntryPos += sizeof(struct DirectoryEntry);
    }

    if (!found) 
    {
        printf("Error: Deleted file not found.\n");
        continue;
    }

    
    fseek(file, directoryAddress + dirEntryPos, SEEK_SET);
    fwrite(formattedName, 1, 1, file); 
    fflush(file);
}


else if (strcmp(token[0], "cd") == 0) 
{
    if (token[1] == NULL) 
    {
        printf("Error: No directory specified.\n");
        continue;
    }
    
    if (!fileFlag)
       {  
        printf("Error: File system image must be opened first.\n");
        continue;
       }

    char path[256];
    strncpy(path, token[1], sizeof(path)-1);
    path[sizeof(path)-1] = '\0';
    
    uint32_t startingCluster = currentCluster;

   
    if (path[0] == '/')
     {
        currentCluster = bpb.BPB_RootClus;
        memmove(path, path + 1, strlen(path)); 
    }

    
    if (strlen(path) == 0) 
    {
        continue;
    }

    char *segment = strtok(path, "/");
    int success = 1;

    while (segment != NULL && success)
    {
        
        if (strcmp(segment, "..") == 0) 
        {
            if (currentCluster != bpb.BPB_RootClus) 
            {
                uint32_t firstSector = getFirstSectorOfCluster(currentCluster, &bpb);
                uint32_t DirectoryAddress = firstSector * bpb.BPB_BytsPerSec;
                
                fseek(file, DirectoryAddress, SEEK_SET);
                struct DirectoryEntry dir;
                int found = 0;
                
                while (fread(&dir, sizeof(struct DirectoryEntry), 1, file) == 1) 
                {
                    if (dir.DIR_Name[0] == '.' && dir.DIR_Name[1] == '.') 
                    {
                        currentCluster = (dir.DIR_FirstClusterHigh << 16) | dir.DIR_FirstClusterLow;
                        if (currentCluster == 0) 
                        {
                            currentCluster = bpb.BPB_RootClus;
                        }
                        found = 1;
                        break;
                    }
                }
                
                if (!found) 
                {
                    success = 0;
                    break;
                }
            } else if (strcmp(token[1], "..") == 0) 
              { 
                printf("At root directory.\n");
                success = 0;
                continue;
              }
        }
        else 
        {
            char formattedName[12];
            formatName(segment, formattedName);
            
            uint32_t firstSector = getFirstSectorOfCluster(currentCluster, &bpb);
            uint32_t DirectoryAddress = firstSector * bpb.BPB_BytsPerSec;
            
            fseek(file, DirectoryAddress, SEEK_SET);
            
            struct DirectoryEntry entry;
            int found = 0;
            
            while (fread(&entry, sizeof(struct DirectoryEntry), 1, file) == 1) 
            {
                if (entry.DIR_Name[0] == 0x00) break;
                if (entry.DIR_Name[0] == 0xE5 || entry.DIR_Attr == 0x0F) continue;
                
                if (memcmp(entry.DIR_Name, formattedName, 11) == 0 && (entry.DIR_Attr & 0x10)) 
                {
                    currentCluster = (entry.DIR_FirstClusterHigh << 16) | entry.DIR_FirstClusterLow;
                    found = 1;
                    break;
                }
            }
            
            if (!found) 
            {
                currentCluster = startingCluster;
                success = 0;
                break;
            }
        }
        
        segment = strtok(NULL, "/");
    }

  
}
else if (strcmp(token[0], "put") == 0) 
{
   if (!fileFlag)
       {  
        printf("Error: File system image must be opened first.\n");
        continue;
       }

    if (token[1] == NULL) 
    {
        printf("Error: No filename specified.\n");
        continue;
    }

    
    for (int i = 0; token[1][i]; i++) 
    {
        token[1][i] = toupper(token[1][i]);
    }

    
    if (token[2] != NULL) 
    {
        for (int i = 0; token[2][i]; i++) 
        {
            token[2][i] = toupper(token[2][i]);
        }
    }

    
    FILE *inputFile = fopen(token[1], "rb");
    if (!inputFile) 
    {
        printf("Error: File not found.\n");
        continue;
    }

    
    char formattedName[11] = {' '};
    formatName(token[2] ? token[2] : token[1], formattedName);

    
    struct DirectoryEntry dirEntry;
    memcpy(dirEntry.DIR_Name, formattedName, 11);
    dirEntry.DIR_Attr = 0x20; 

    
    fseek(inputFile, 0, SEEK_END);
    dirEntry.DIR_FileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    
    uint32_t startCluster = END;
    uint32_t fatStart = bpb.BPB_RsvdSecCnt * bpb.BPB_BytsPerSec;
    uint32_t cluster;
    fseek(file, fatStart, SEEK_SET);

    for (uint32_t i = 2; i < bpb.BPB_FATSz32 * bpb.BPB_BytsPerSec / 4; i++) 
    {
        fread(&cluster, sizeof(cluster), 1, file);
        if (cluster == FREE) 
        {
            fseek(file, -sizeof(cluster), SEEK_CUR);
            cluster = END;
            fwrite(&cluster, sizeof(cluster), 1, file);
            startCluster = i;
            break;
        }
    }

    if (startCluster == END) 
    {
        fclose(inputFile);
        continue;
    }

    dirEntry.DIR_FirstClusterHigh = (startCluster >> 16) & 0xFFFF;
    dirEntry.DIR_FirstClusterLow = startCluster & 0xFFFF;

    
    uint32_t directoryAddress = getFirstSectorOfCluster(currentCluster, &bpb) * bpb.BPB_BytsPerSec;
    fseek(file, directoryAddress, SEEK_SET);
    struct DirectoryEntry entry;

    int entryAdded = 0;
    while (fread(&entry, sizeof(entry), 1, file) == 1) 
    {
        if (entry.DIR_Name[0] == 0x00 || entry.DIR_Name[0] == 0xE5) 
        {
            fseek(file, -sizeof(entry), SEEK_CUR);
            fwrite(&dirEntry, sizeof(dirEntry), 1, file);
            fflush(file); 
            entryAdded = 1;
            break;
        }
    }

    if (!entryAdded) 
    {
        fclose(inputFile);
        continue;
    }

    
    uint32_t currentCluster = startCluster;
    uint8_t buffer[bpb.BPB_BytsPerSec * bpb.BPB_SecPerClus];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) 
    {
        uint32_t firstSector = getFirstSectorOfCluster(currentCluster, &bpb) * bpb.BPB_BytsPerSec;
        fseek(file, firstSector, SEEK_SET);
        fwrite(buffer, 1, bytesRead, file);

        if (bytesRead < sizeof(buffer)) 
        {
            
            fseek(file, fatStart + (currentCluster * 4), SEEK_SET);
            uint32_t endMarker = END;
            fwrite(&endMarker, sizeof(endMarker), 1, file);
            break;
        }

        
        uint32_t nextCluster = END;
        fseek(file, fatStart, SEEK_SET);
        for (uint32_t i = 2; i < bpb.BPB_FATSz32 * bpb.BPB_BytsPerSec / 4; i++) 
        {
            fread(&cluster, sizeof(cluster), 1, file);
            if (cluster == FREE) 
            {
                fseek(file, -sizeof(cluster), SEEK_CUR);
                cluster = END;
                fwrite(&cluster, sizeof(cluster), 1, file);
                nextCluster = i;
                break;
            }
        }

        if (nextCluster == END) 
        {
            fclose(inputFile);
            return 0;
        }

        
        fseek(file, fatStart + (currentCluster * 4), SEEK_SET);
        fwrite(&nextCluster, sizeof(nextCluster), 1, file);
        currentCluster = nextCluster;
    }

    fclose(inputFile);
}

}

    return 0;
}


