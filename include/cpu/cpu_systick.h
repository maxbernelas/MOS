/**
 * \file cpu_systick.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * SysTick interface
 */
#ifndef H_CPU_SYSTICK
#define H_CPU_SYSTICK

/**
 * Configure the SysTick timer
 * \param[in] freq Desired timer interrupt frequency
 * \param[in] ahb_freq AHB frequency
 * \retval 0 Success
 * \retval #EINVAL Unable to set the required frequency
 */
int systick_setup(unsigned int freq, unsigned int ahb_freq);

/**
 * Start the SysTick timer
 * \retval 0 Success
 */
int systick_enable(void);

/**
 * Stop the SysTick timer
 * \retval 0 Success
 */
int systick_disable(void);

/**
 * Get the configured SysTick interrupt frequency
 * \return The currently configured SysTick interrupt frequency
 */
unsigned int systick_get_freq(void);

#endif
