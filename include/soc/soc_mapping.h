/**
 * \file soc_mapping.h
 * \author Maxime Bernelas <maxime@bernelas.fr>
 * Memory mapping for the STM32F103 microcontroller
 */
#ifndef H_SOC_MAPPING
#define H_SOC_MAPPING

#include <cpu/cpu_mapping.h>

/*
 * Flash memory sections
 */
/** Code memory mapping address */
#define SOC_CODE_START (CPU_ROM_START)

/** User flash start address */
#define SOC_FLASH_START (CPU_ROM_START + 0x08000000)

/** BootROM start address */
#define SOC_BOOT_ROM_START (CPU_ROM_START + 0x1FFFF000)

/** Option bytes start address */
#define SOC_OPT_BYTES_START (CPU_ROM_START + 0x1FFFF800)

/*
 * SRAM sections
 */
/** SRAM start address */
#define SOC_SRAM_START (CPU_SRAM_START)

/*
 * Peripherals sections
 */
/** Timer 2 base address */
#define SOC_TIM2_BASE (CPU_PERIPH_START)

/** Timer 3 base address */
#define SOC_TIM3_BASE (CPU_PERIPH_START + 0x400)

/** Timer 4 base address */
#define SOC_TIM3_BASE (CPU_PERIPH_START + 0x800)

/** RTC base address */
#define SOC_RTC_BASE (CPU_PERIPH_START + 0x2800)

/** Window watchdog base address */
#define SOC_WWDG_START (CPU_PERIPH_START + 0x2C00)

/** Independant watchdog base address */
#define SOC_IWDG_BASE (CPU_PERIPH_START + 0x3000)

/** SPI 2 base address */
#define SOC_SPI2_BASE (CPU_PERIPH_START + 0x3800)

/** USART2 base address */
#define SOC_USART2_BASE (CPU_PERIPH_START + 0x4400)

/** USART3 base address */
#define SOC_USART3_BASE (CPU_PERIPH_START + 0x4800)

/** I2C 1 base address */
#define SOC_I2C1_BASE (CPU_PERIPH_START + 0x5400)

/** I2C 2 base address */
#define SOC_I2C2_BASE (CPU_PERIPH_START + 0x5800)

/** USB registers base address */
#define SOC_USB_REGS_BASE (CPU_PERIPH_START + 0x5C00)

/** USB/CAN SRAM base address */
#define SOC_USB_CAN_SRAM_BASE (CPU_PERIPH_START + 0x6000)

/** CAN base address */
#define SOC_CAN_BASE (CPU_PERIPH_START + 0x6400)

/** Backup registers base address */
#define SOC_BKP_BASE (CPU_PERIPH_START + 0x6C00)

/** Power management base address */
#define SOC_PWR_BASE (CPU_PERIPH_START + 0x7400)

/** Alternate function I/Os registers base address */
#define SOC_AFIO_BASE (CPU_PERIPH_START + 0x10000)

/** External interrupt controller base address */
#define SOC_EXTI_BASE (CPU_PERIPH_START + 0x10400)

/** Port A base address */
#define SOC_PORTA_BASE (CPU_PERIPH_START + 0x10800)

/** Port B base address */
#define SOC_PORTB_BASE (CPU_PERIPH_START + 0x10C00)

/** Port C base address */
#define SOC_PORTC_BASE (CPU_PERIPH_START + 0x11000)

/** Port D base address */
#define SOC_PORTD_BASE (CPU_PERIPH_START + 0x11400)

/** Port E base address */
#define SOC_PORTE_BASE (CPU_PERIPH_START + 0x11800)

/** ADC 1 base address */
#define SOC_ADC1_BASE (CPU_PERIPH_START + 0x12400)

/** ADC 2 base address */
#define SOC_ADC2_BASE (CPU_PERIPH_START + 0x12800)

/** Timer 1 base address */
#define SOC_TIM1_BASE (CPU_PERIPH_START + 0x12C00)

/** SPI 1 base address */
#define SOC_SPI1_BASE (CPU_PERIPH_START + 0x13000)

/** USART 1 base address */
#define SOC_USART1_BASE (CPU_PERIPH_START + 0x13800)

/** DMA base address */
#define SOC_DMA_BASE (CPU_PERIPH_START + 0x20000)

/** Reset/Clock controller base address */
#define SOC_RCC_BASE (CPU_PERIPH_START + 0x21000)

/** Flash interface controller base address */
#define SOC_FLITF_BASE (CPU_PERIPH_START + 0x22000)

/** CRC base address */
#define SOC_CRC_BASE (CPU_PERIPH_START + 0x23000)

#endif
