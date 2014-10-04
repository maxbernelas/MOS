/**
 * \file string.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * String management functions
 */
#ifndef H_STRING
#define H_STRING

#include <kernel/stddef.h>

/**
 * Copy a memory area
 * \param[out] dest Destination pointer
 * \param[in] src Source pointer
 * \param[in] n Number of bytes to copy
 * \note Source and destination areas must not overlap
 */
void *memcpy(void *dest, const void *src, size_t n);

/**
 * Fill a memory area with a constant byte value
 * \param[out] dest Destination pointer
 * \param[in] val Value used to fill the memory area
 * \param[in] n Number of bytes to fill
 */
void *memset(void *dest, int val, size_t n);

#endif
