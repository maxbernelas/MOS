/**
 * \file sched.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Task scheduler API
 */
#ifndef H_SCHED
#define H_SCHED

#include <kernel/stddef.h>

/** Opaque task descriptor type */
typedef struct _task task_t;

/**
 * Create a new task
 * \param[in] f Task routine
 * \param[in] arg Task argument
 * \param[in] stack_size Size of task's stack in bytes
 * \param[in] priv True if task must be privileged, false otherwise
 * \return The new task handler, NULL on failure
 */
task_t *sched_create_task(void (*f)(void *), void *arg, size_t stack_size,
                          unsigned char priv);

/** Put task to sleep waiting for an event */
void sched_sleep(void);

/** Relinquish processor without putting task to sleep (task becomes ready) */
void sched_yield(void);

/**
 * Initialize scheduler (creates idle task)
 * \return 0 on success, 1 on failure
 */
int sched_init(void);

/** Run scheduler and switch task if necessary */
void schedule(void);

#endif
