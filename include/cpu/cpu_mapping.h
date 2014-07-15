/**
 * \file cpu_mapping.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Cortex-M3 CPU memory mapping
 */
#ifndef H_CPU_MAPPING
#define H_CPU_MAPPING

/*
 * Main memory sections
 */
/** ROM code start address */
#define CPU_ROM_START (0x00000000)

/** ROM code end address */
#define CPU_ROM_END (0x1FFFFFFF)

/** SRAM start address */
#define CPU_SRAM_START (0x20000000)

/** SRAM bit-band region start address */
#define CPU_SRAM_BITBAND_REG_START (CPU_SRAM_START)

/** SRAM bit-band region end address */
#define CPU_SRAM_BITBAND_REG_END (0x20100000)

/** SRAM bit-band alias start address */
#define CPU_SRAM_BITBAND_ALIAS_START (0x22000000)

/** SRAM bit-band alias end address */
#define CPU_SRAM_BITBAND_ALIAS_END (0x23FFFFFF)

/** SRAM end address */
#define CPU_SRAM_END (0x3FFFFFFF)

/** Peripheral start address */
#define CPU_PERIPH_START (0x40000000)

/** Peripheral bit-band region start address */
#define CPU_PERIPH_BITBAND_REG_START (CPU_PERIPH_START)

/** Peripheral bit-band region end address */
#define CPU_PERIPH_BITBAND_REG_END (0x40100000)

/** Peripheral bit-band alias start address */
#define CPU_PERIPH_BITBAND_ALIAS_START (0x42000000)

/** Peripheral bit-band alias end address */
#define CPU_PERIPH_BITBAND_ALIAS_END (0x43FFFFFF)

/** Peripheral end address */
#define CPU_PERIPH_END (0x5FFFFFFF)

/** External RAM start address */
#define CPU_EXT_RAM_START (0x60000000)

/** External RAM end address */
#define CPU_EXT_RAM_END (0x9FFFFFFF)

/** External device start address */
#define CPU_EXT_DEV_START (0xA0000000)

/** External device end address */
#define CPU_EXT_DEV_END (0xDFFFFFFF)

/** Private peripheral bus (internal) start address */
#define CPU_PPB_INT_START (0xE0000000)

/** Private peripheral bus (internal) end address */
#define CPU_PPB_INT_END (0xE003FFFF)

/** Private peripheral bus (external) start address */
#define CPU_PPB_EXT_START (0xE0040000)

/** Private peripheral bus (external) end address */
#define CPU_PPB_EXT_END (0xE00FFFFF)

/** Vendor-specific area start address */
#define CPU_VENDOR_START (0xE0100000)

/** Vendor-specific area end address */
#define CPU_VENDOR_END (0xFFFFFFFF)

/*
 * Core peripherals
 */
/** System timer base address */
#define CPU_SYSTMR_BASE (CPU_PPB_INT_START + 0xE010)

/** NVIC base address */
#define CPU_NVIC_BASE (CPU_PPB_INT_START + 0xE100)

/** System control block base address */
#define CPU_SCB_BASE (CPU_PPB_INT_START + 0xED00)

/** MPU type register address */
#define CPU_MPU_TYPE_REG ((unsigned int *)(CPU_PPB_INT_START + 0xED90))

#endif
