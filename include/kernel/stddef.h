/**
 * \file stddef.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Basic C standard definitions
 */
#ifndef H_STDDEF
#define H_STDDEF

#include <kernel/stdint.h>

/** NULL pointer constant */
#define NULL ((void *)0)

/** Unsigned integer type capable of holding the size of an object */
typedef uint32_t size_t;

/**
 * Signed integer type capable of holding the result of the subtraction of two
 * pointers
 */
typedef int32_t ptrdiff_t;

/**
 * Macro giving the offset in bytes of a structure member relative to the
 * beginning of the structure
 */
#define offsetof(type, member) __builtin_offsetof(type, member)

#endif
