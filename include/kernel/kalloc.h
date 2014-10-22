/**
 * \file kalloc.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Kernel memory allocator interface
 */
#ifndef H_KALLOC
#define H_KALLOC

#include <kernel/stddef.h>

/**
 * Initialize the memory allocator
 * \retval 0 Success
 */
int kalloc_init(void);

/**
 * Allocate a block of memory
 * \param[in] n Requested memory block size in bytes
 * \return A pointer to the allocated block or NULL on failure
 * \note This function returns NULL on allocation of a 0 byte block
 */
void * kmalloc(size_t n);

/**
 * Allocate a block of memory initialized to zero
 * \param[in] n Size of the requested block in bytes
 * \return A pointer to the allocated block or NULL on failure
 * \note This function returns NULL on allocation of a 0 byte block
 */
void * kcalloc(size_t n);

/**
 * Free an allocated memory block
 * \param[in] p Pointer to the block to free
 * \note If p is NULL, the function does nothing
 */
void kfree(void *p);

#endif
