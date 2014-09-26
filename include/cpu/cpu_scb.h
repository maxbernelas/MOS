/**
 * \file cpu_scb.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * System control block interface
 */
#ifndef H_CPU_SCB
#define H_CPU_SCB

#include <kernel/stdint.h>

/** CPU identification */
typedef struct
{
	unsigned char implementer;     /**< Implementer code */
	unsigned char variant;         /**< Variant number */
	unsigned short part;           /**< Part number */
	unsigned char revision;        /**< Revision number */
} cpuid_t;

/** ARM implementer code */
#define CPUID_IMPLEMENTER_ARM (0x41)

/** Cortex-M3 part number */
#define CPUID_PART_CORTEX_M3 (0xC23)

/**
 * Get the CPUID information
 * \param[out] cpuid Set to the CPUID information on output
 * \retval 0 Success
 */
int scb_get_cpuid(cpuid_t *cpuid);

/**
 * Set PendSV interrupt pending bit
 * \retval 0 Success
 */
int scb_set_pendSV(void);

/**
 * Clear PendSV interrupt pending bit
 * \retval 0 Success
 */
int scb_clear_pendSV(void);

/**
 * Clear Systick interrupt pending bit
 * \retval 0 Success
 */
int scb_clear_systick(void);

/**
 * Request a system reset
 * \retval 0 Success
 */
int scb_request_reset(void);

/**
 * Enable or disable deep sleep
 * \param[in] status Set to 1 do enable deep sleep, 0 to disable deep sleep
 * \retval 0 Success
 */
int scb_set_deep_sleep(int status);

/**
 * Enable or disable trap on division by zero
 * \param[in] status Set to 1 to enable division by zero trap, 0 to disable
 * \retval 0 Success
 */
int scb_set_trap_on_div_by_zero(int status);

/** Causes of faults */
typedef enum
{
	FAULT_CAUSE_UNKKNOW,               /**< Unknown cause */
	FAULT_CAUSE_UF_DIV_BY_ZERO,        /**< Division by zero */
	FAULT_CAUSE_UF_ACCESS,             /**< Unaligned access */
	FAULT_CAUSE_UF_NOCP,               /**< No coprocessor */
	FAULT_CAUSE_UF_INVALID_PC,         /**< Invalid PC */
	FAULT_CAUSE_UF_INVALID_STATE,      /**< Invalid state */
	FAULT_CAUSE_UF_UNDEF_INSTR,        /**< Undefined instruction */
	FAULT_CAUSE_BF_STACKING_ERROR,     /**< Stacking error on exception entry */
	FAULT_CAUSE_BF_UNSTACKING_ERROR,   /**< Unstacking error on exception return */
	FAULT_CAUSE_BF_IBUSERR,            /**< Instruction bus error */
	FAULT_CAUSE_MM_STACKING_ERROR,     /**< Memory management fault on stacking for exception entry */
	FAULT_CAUSE_MM_UNSTACKING_ERROR,   /**< Memory management fault on unstacking for exception return */
	FAULT_CAUSE_MM_DATA_ACCESS,        /**< Data access violation */
	FAULT_CAUSE_MM_INSTR_ACCESS        /**< Instruction access violation */
} fault_cause_t;

/** Fault information */
typedef struct
{
	fault_cause_t cause;           /**< Cause of the fault */
	void *instruction;             /**< Address of the faulting instruction, NULL if unknown */
	void *address;                 /**< Faulting requested address, NULL if unknown or not applicable */
} fault_info_t;

/**
 * Gather information about a usage fault that just occurred
 * \param[in] stacked_pc The PC that was stacked on exception entry
 * \param[out] info Will be filled with information about the fault
 * \retval 0 Success
 */
int scb_get_usage_fault_information(void *stacked_pc, fault_info_t *info);

/**
 * Gather information about a bus fault that just occurred
 * \param[in] stacked_pc The PC that was stacked on exception entry
 * \param[out] info Will be filled with information about the fault
 * \retval 0 Success
 */
int scb_get_bus_fault_information(void *stacked_pc, fault_info_t *info);

/**
 * Gather information about a memory management fault that just occurred
 * \param[in] stacked_pc The PC that was stacked on exception entry
 * \param[out] info Will be filled with information about the fault
 * \retval 0 Success
 */
int scb_get_mem_manage_fault_information(void *stacked_pc, fault_info_t *info);
#endif
