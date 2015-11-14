/**
 * \file cpu_task.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * CPU-specific task handling interface
 */
#ifndef H_CPU_TASK
#define H_CPU_TASK

/**
 * Create a new task context
 * \param[in] sp Task stack pointer
 * \param[in] func Task entry point
 * \param[in] arg Task function parameter
 * \param[in] stop_func Function to call when task terminates
 * \return The new stack pointer
 */
void * cpu_task_create_context(void *sp, void *func, void *arg, void *stop_func);

/**
 * Save task context on PSP
 */
void cpu_task_save_context(void);

/**
 * Restore task context from PSP
 */
void cpu_task_restore_context(void);

/**
 * Return to user mode
 */
#define CPU_RET_TO_USER() asm volatile("mov lr, #0xFFFFFFFD\n\t"               \
                                       "bx lr")

#endif
