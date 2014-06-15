/**
 * \file stdint.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Standard integer types definitions
 */
#ifndef H_STDINT
#define H_STDINT

/*
 * Fixed width types
 */
/** 8-bits signed integer */
typedef signed char int8_t;

/** 8-bits unsigned integer */
typedef unsigned char uint8_t;

/** 16-bits signed integer */
typedef signed short int int16_t;

/** 16-bits unsigned integer */
typedef unsigned short int uint16_t;

/** 32-bits signed integer */
typedef int int32_t;

/** 32-bits unsigned integer */
typedef unsigned int uint32_t;

/** 64-bits signed integer */
typedef signed long long int64_t;

/** 64-bits unsigned integer */
typedef unsigned long long uint64_t;


/*
 * Minimum width types
 */
/** Minimum 8 bits signed integer */
typedef int8_t int_least8_t;

/** Minimum 8 bits unsigned integer */
typedef uint8_t uint_least8_t;

/** Minimum 16 bits signed integer */
typedef int16_t int_least16_t;

/** Minimum 16 bits unsigned integer */
typedef uint16_t uint_least16_t;

/** Minimum 32 bits signed integer */
typedef int32_t int_least32_t;

/** Minimum 32 bits unsigned integer */
typedef uint32_t uint_least32_t;

/** Minimum 64 bits signed integer */
typedef int64_t int_least64_t;

/** Minimum 64 bits unsigned integer */
typedef uint64_t uint_least64_t;


/*
 * Fastest minimum width types
 */
/** Fast 8 bits signed integer */
typedef int32_t int_fast8_t;

/** Fast 8 bits unsigned integer */
typedef uint32_t uint_fast8_t;

/** Fast 16 bits signed integer */
typedef int32_t int_fast16_t;

/** Fast 16 bits unsigned integer */
typedef uint32_t uint_fast16_t;

/** Fast 32 bits signed integer */
typedef int32_t int_fast32_t;

/** Fast 32 bits unsigned integer */
typedef uint32_t uint_fast32_t;

/** Fast 64 bits signed integer */
typedef int64_t int_fast64_t;

/** Fast 64 bits unsigned integer */
typedef uint64_t uint_fast64_t;


/*
 * Types capables of holding pointers
 */
/** Signed pointer integer type */
typedef int32_t intptr_t;

/** Unsigned pointer integer type */
typedef uint32_t uintptr_t;


/*
 * Greatest width types
 */
/** Maximum width signed type */
typedef int64_t intmax_t;

/** Maximum width unsigned type */
typedef uint64_t uintmax_t;


/*
 * Limits of fixed width types
 */
/** Minimum value of int8_t */
#define INT8_MIN (-128)

/** Maximum value of int8_t */
#define INT8_MAX (127)

/** Maximum value of uint8_t */
#define UINT8_MAX (255U)

/** Minimum value of int16_t */
#define INT16_MIN (-32768)

/** Maximum value of int16_t */
#define INT16_MAX (32767)

/** Maximum value of uint16_t */
#define UINT16_MAX (65535U)

/** Minimum value of int32_t */
#define INT32_MIN (-2147483648)

/** Maximum value of int32_t */
#define INT32_MAX (2147483647)

/** Maximum value of uint32_t */
#define UINT32_MAX (4294967295U)

/** Minimum value of int64_t */
#define INT64_MIN (-9223372036854775808LL)

/** Maximum value of int64_t */
#define INT64_MAX (9223372036854775807LL)

/** Maximum value of uint64_t */
#define UINT64_MAX (18446744073709551615ULL)


/*
 * Limits of minimum width types
 */
/** Minimum value of int_least8_t */
#define INT_LEAST8_MIN INT8_MIN

/** Maximum value of int_least8_t */
#define INT_LEAST8_MAX INT8_MAX

/** Maximum value of uint_least8_t */
#define UINT_LEAST8_MAX UINT8_MAX

/** Minimum value of int_least16_t */
#define INT_LEAST16_MIN INT16_MIN

/** Maximum value of int_least16_t */
#define INT_LEAST16_MAX INT16_MAX

/** Maximum value of uint_least16_t */
#define UINT_LEAST16_MAX UINT16_MAX

/** Minimum value of int_least32_t */
#define INT_LEAST32_MIN INT32_MIN

/** Maximum value of int_least32_t */
#define INT_LEAST32_MAX INT32_MAX

/** Maximum value of uint_least32_t */
#define UINT_LEAST32_MAX UINT32_MAX

/** Minimum value of int_least64_t */
#define INT_LEAST64_MIN INT64_MIN

/** Maximum value of int_least64_t */
#define INT_LEAST64_MAX INT64_MAX

/** Maximum value of uint_least64_t */
#define UINT_LEAST64_MAX UINT64_MAX


/*
 * Limits of fastest minimum width types
 */
/** Minimum value of int_fast8_t */
#define INT_FAST8_MIN INT32_MIN

/** Maximum value of int_fast8_t */
#define INT_FAST8_MAX INT32_MAX

/** Maximum value of uint_fast8_t */
#define UINT_FAST8_MAX UINT32_MAX

/** Minimum value of int_fast16_t */
#define INT_FAST16_MIN INT32_MIN

/** Maximum value of int_fast16_t */
#define INT_FAST16_MAX INT32_MAX

/** Maximum value of uint_fast16_t */
#define UINT_FAST16_MAX UINT32_MAX

/** Minimum value of int_fast32_t */
#define INT_FAST32_MIN INT32_MIN

/** Maximum value of int_fast32_t */
#define INT_FAST32_MAX INT32_MAX

/** Maximum value of uint_fast32_t */
#define UINT_FAST32_MAX UINT32_MAX

/** Minimum value of int_fast64_t */
#define INT_FAST64_MIN INT64_MIN

/** Maximum value of int_fast64_t */
#define INT_FAST64_MAX INT64_MAX

/** Maximum value of uint_fast64_t */
#define UINT_FAST64_MAX UINT64_MAX


/*
 * Limits of types holding pointer values
 */
/** Minimum value of intptr_t */
#define INTPTR_MIN INT32_MIN

/** Maximum value of intptr_t */
#define INTPTR_MAX INT32_MAX

/** Maximum value of uintptr_t */
#define UINTPTR_MAX UINT32_MAX


/*
 * Limits of greatest width types
 */
/** Minimum value of intmax_t */
#define INTMAX_MIN INT64_MIN

/** Maximum value of intmax_t */
#define INTMAX_MAX INT64_MAX

/** Maximum value of uintmax_t */
#define UINTMAX_MAX UINT64_MAX


/*
 * Limits of various types not defined in this header
 */
/** Minimum value of ptrdiff_t */
#define PTRDIFF_MIN INTPTR_MIN

/** Maximum value of ptrdiff_t */
#define PTRDIFF_MAX INTPTR_MAX

/** Maximum value of size_t */
#define SIZE_MAX UINTPTR_MAX


/*
 * Macros for building integer constants
 */
/** Macro for building a signed 8 bits integer constant */
#define INT8_C(x) (x)

/** Macro for building an unsigned 8 bits integer constant */
#define UINT8_C(x) (x ## U)

/** Macro for building a signed 16 bits integer constant */
#define INT16_C(x) (x)

/** Macro for building an unsigned 16 bits integer constant */
#define UINT16_C(x) (x ## U)

/** Macro for building a signed 32 bits integer constant */
#define INT32_C(x) (x)

/** Macro for building an unsigned 32 bits integer constant */
#define UINT32_C(x) (x ## U)

/** Macro for building a signed 64 bits integer constant */
#define INT64_C(x) (x ## LL)

/** Macro for building an unsigned 64 bits integer constant */
#define UINT64_C(x) (x ## ULL)

/** Macro for building a signed maximum width value */
#define INTMAX_C(x) INT64_C(x)

/** Macro for buiding an unsigned maximum width value */
#define UINTMAX_C(x) UINT64_C(x)

#endif
