/*******************************************************************
  APO semestral project file.
  Module for allocating and freeing of memory with error handling.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

/*Allocates memory of given size and return pointer*/
void *allocate_memory(int size);
/*Allocates memory for n_mem members of mem_size size,
 sets the memory to zero and returns pointer to it*/
void *allocate_memory_calloc(int n_mem, int mem_size);
/*Reallocates memory at given pointer to block of size of new_size*/
void reallocate_memory(void **ptr, int new_size);
/*Deallocates memory at given pointer*/
void deallocate_memory(void **ptr);

#endif //__MY_MALLOC_H__