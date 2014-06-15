/**
 * \file stdbool.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Standard boolean related definitions
 */
#ifndef H_STDBOOL
#define H_STDBOOL

/** Boolean type alias */
#define bool _Bool

/** False value */
#define false (0)

/** True value */
#define true (1)

/** This just indicates that boolean values are defined by this header */
#define __bool_true_false_are_defined (1)

#endif
