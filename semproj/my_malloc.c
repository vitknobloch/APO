/*******************************************************************
  APO semestral project file.
  Module for allocating and freeing of memory with error handling.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "my_malloc.h"

/*Allocates memory of given size and return pointer*/
void *allocate_memory(int size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        fprintf(stderr, "Error allocating memory\n");
        exit(-1);
    }
    return ptr;
}

/*Allocates memory for n_mem members of mem_size size,
 sets the memory to zero and returns pointer to it*/
void *allocate_memory_calloc(int n_mem, int mem_size)
{
    void *ptr = calloc(n_mem, mem_size);
    if (ptr == NULL)
    {
        fprintf(stderr, "Error allocating memory\n");
        exit(-1);
    }
    return ptr;
}

/*Reallocates memory at given pointer to block of size of new_size*/
void reallocate_memory(void **ptr, int new_size)
{
    *ptr = realloc(*ptr, new_size);
    if (*ptr == NULL)
    {
        fprintf(stderr, "Error re-allocating memory\n");
        exit(-1);
    }
}

/*Deallocates memory at given pointer*/
void deallocate_memory(void **ptr)
{
    if (*ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
    }
}