/*
    A journey of a thousand miles begins with a single step
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

typedef struct{

    char*   buffer;
    size_t  buffer_length;
    size_t  input_length;

} InputBuffer;


InputBuffer*
new_input_buffer()
{
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer        = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length  = 0;

    return input_buffer;
}


void
print_prompt()
{
    printf("db > ");
    return;    
}


void
read_input(InputBuffer* input_buffer)
{
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if(bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
    return;
}


void
close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
    return;
}





// we'll need a read-execute-print loop. we'll need an infinite loop
// that prints the prompt, gets a line of input, then processes that 
// line of input
int
main(int argc, char* argv[])
{
    InputBuffer* input_buffer = new_input_buffer();
    while (1){
        read_input(input_buffer);
        print_prompt();

        if(strcmp(input_buffer->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        else{
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    } 

    return 0;
}