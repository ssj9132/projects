// The MIT License (MIT)
// 
// Copyright (c) 2024 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#define _GNU_SOURCE

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

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 32     

int main(int argc, char *argv[]) //added parameters for reading arguments for file functions
{
  
  char * command_string = (char*) malloc( MAX_COMMAND_SIZE ); //Allocates memory for storing a command string that the user will input.

//Functions
  void error_cmd() //error function
  {
    const char error_message[] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));

  }

  void exit_cmd(char *command_string, char *head_ptr) //exit function
  {
    free(command_string);
    free(head_ptr);
    exit(0);
  }

  //batch file part

    FILE *file = NULL;  

    if (argc > 1) //because it reads 2 arguments incldg msh and filename
    { 
        file = fopen(argv[1], "r");  //argv[1] contains the filename, and only needing to read it
        if (file == NULL) {  //to verify that the file exists
            error_cmd();
            exit(1);  
        }
    }

    if (file != NULL) {  //batch file only usable if content present...hence to make sure
        if (fgets(command_string, MAX_COMMAND_SIZE, file) == NULL) { //to verify file has content 
            error_cmd();
            fclose(file);
            exit(1);
        }

        rewind(file); 
    }
 

  while( 1 )
  {
    
    if(file != NULL)
    {
      if(fgets(command_string, MAX_COMMAND_SIZE, file) == NULL)
      {
        fclose(file);
        exit(0);
      }
    }
    else
    {
    // Print out the msh prompt
      printf ("msh> ");
    

    // Read the command from the commandi line.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something.
    /* Parse input */

      while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );
    }
    char *token[MAX_NUM_ARGUMENTS];

    int token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *argument_pointer;                                         
                                                           
    char *working_string  = strdup( command_string );                

    // we are going to move the working_string pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    
    char *head_ptr = working_string;
    
    // Tokenize the input with whitespace used as the delimiter
    while ( ( (argument_pointer = strsep(&working_string, WHITESPACE ) ) != NULL) &&(token_count<MAX_NUM_ARGUMENTS))
    {
      if (strlen(argument_pointer) > 0) 
      {
        token[token_count] = strndup(argument_pointer, MAX_COMMAND_SIZE);
        token_count++;
      }
    }

token[token_count] = NULL; 

token_count++;

int token_index = 0;
int count = token_count - 1;

if (token[token_index] == NULL) 
{
    continue;  
}


    if (( (strcmp(token[token_index], "exit") == 0) || (strcmp(token[token_index], "quit") == 0)) && token[1] == NULL)
    {
        exit_cmd(command_string, head_ptr);
        exit(0);
    }


    else if (strcmp(token[token_index],"cd")==0)
    {

      if ((chdir(token[1])) == -1)
      {
        error_cmd();
        free(head_ptr);
        continue;  			
      }		
    }
    
    else
    {
        pid_t pid = fork( );
        if( pid == 0 )
        {
            int i;
            for( i=1; i<count; i++ )
            {
              if(i == 0)
              {
                error_cmd();
                free(head_ptr);
              }
              else if( strcmp( token[i], ">" ) == 0 )
              {
              
                  int fd = open( token[i+1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
                  if( fd < 0 || token[i+2]!=NULL)
                  {
                      error_cmd();
                      free(head_ptr);
                      exit( 0 );                    
                  }
                  dup2( fd, 1 );
                  close( fd );
                  
                  // Trim off the > output part of the command
                  token[i] = NULL;
              }
            }

            if(execvp( token[0], token) == -1 )
            {
              error_cmd();
              free(head_ptr);
            }
        }
        else if( pid > 0 )
        {
          wait( NULL );
        }
        else
        {
          error_cmd();
          free(head_ptr);
        }
    }
  }
  return 0;
  // e2520ca2-76f3-90d6-0242ac1210022 




}

