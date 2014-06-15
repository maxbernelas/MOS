/**
 * \file stdarg.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * This header provides support for variadic functions
 */
#ifndef H_STDARG
#define H_STDARG

/** Variable argument list type */
typedef __builtin_va_list va_list;

/** Start iterating on a va_list */
#define va_start(list, param) __builtin_va_start(list, param)

/** Retrieve the next argument of a va_list */
#define va_arg(list, type) __builtin_va_arg(list, type)

/** Free a va_list */
#define va_end(list) __builtin_va_end(list)

/** Copy a va_list to another */
#define va_copy(list1, list2) __builtin_va_copy(list1, list2)

#endif
