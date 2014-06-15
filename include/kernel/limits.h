/**
 * \file limits.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Implementation-define limits
 */
#ifndef H_LIMITS
#define H_LIMITS

#include <kernel/stdint.h>

/** Number of bits in a byte */
#define CHAR_BIT (8)

/** Minimum value of a signed char */
#define SCHAR_MIN INT8_MIN

/** Maximum value of a signed char */
#define SCHAR_MAX INT8_MAX

/** Maximum value of an unsigned char */
#define UCHAR_MAX UINT8_MAX

/** Minimum value of a char */
#define CHAR_MIN (0)

/** Maximum value of a char */
#define CHAR_MAX UCHAR_MAX

/** Minimum value of a signed short */
#define SHRT_MIN INT16_MIN

/** Maximum value of a signed short */
#define SHRT_MAX INT16_MAX

/** Maximum value of an unsigned short */
#define USHRT_MAX UINT16_MAX

/** Minimum value of a signed int */
#define INT_MIN INT32_MIN

/** Maximum value of a signed int */
#define INT_MAX INT32_MAX

/** Maximum value of an unsigned int */
#define UINT_MAX UINT32_MAX

/** Minimum value of a signed long */
#define LONG_MIN INT32_MIN

/** Maximum value of a signed long */
#define LONG_MAX INT32_MAX

/** Maximum value of an unsigned long */
#define ULONG_MAX UINT32_MAX

/** Minimum value of a signed long long */
#define LLONG_MIN INT64_MIN

/** Maximum value of a signed long long */
#define LLONG_MAX INT64_MAX

/** Maximum value of an unsigned long long */
#define ULLONG_MAX UINT64_MAX

#endif
