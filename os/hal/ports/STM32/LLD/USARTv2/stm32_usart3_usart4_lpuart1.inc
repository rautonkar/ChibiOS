/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    USARTv2/stm32_usart3_usart4_lpuart1.inc
 * @brief   Shared USART3, USART4, LPUART1 handler.
 *
 * @addtogroup STM32_USART3_USART4_LPUART1_HANDLER
 * @{
 */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Registry checks for robustness.*/
#if !defined(STM32_HAS_USART3)
#error "STM32_HAS_USART3 not defined in registry"
#endif

#if !defined(STM32_HAS_UART4)
#error "STM32_HAS_UART4 not defined in registry"
#endif

#if !defined(STM32_HAS_LPUART1)
#error "STM32_HAS_LPUART1 not defined in registry"
#endif

#if STM32_HAS_USART3 == FALSE
#error "USART3 not present"
#endif

#if STM32_HAS_UART4 == FALSE
#error "USART4 not present"
#endif

#if STM32_HAS_LPUART1 == FALSE
#error "LPUART1 not present"
#endif

/* Priority settings checks.*/
#if !defined(STM32_IRQ_USART3_USART4_LPUART1_PRIORITY)
#error "STM32_IRQ_USART3_USART4_LPUART1_PRIORITY not defined in mcuconf.h"
#endif

#if !OSAL_IRQ_IS_VALID_PRIORITY(STM32_IRQ_USART3_USART4_LPUART1_PRIORITY)
#error "Invalid IRQ priority assigned to STM32_IRQ_USART3_USART4_LPUART1_PRIORITY"
#endif

/* Other checks.*/
#if (HAL_USE_SERIAL && STM32_SERIAL_USE_USART3) &&                          \
    (HAL_USE_UART && STM32_UART_USE_USART3)
#error "USART3 used by multiple drivers"
#endif

#if (HAL_USE_SERIAL && STM32_SERIAL_USE_UART4) &&                           \
    (HAL_USE_UART && STM32_UART_USE_UART4)
#error "USART4 used by multiple drivers"
#endif

#if (HAL_USE_SERIAL && STM32_SERIAL_USE_USART3) ||                          \
    (HAL_USE_UART && STM32_UART_USE_USART3)
#define STM32_USART3_IS_USED         TRUE
#else
#define STM32_USART3_IS_USED         FALSE
#endif

#if (HAL_USE_SERIAL && STM32_SERIAL_USE_UART4) ||                           \
    (HAL_USE_UART && STM32_UART_USE_UART4)
#define STM32_USART4_IS_USED         TRUE
#else
#define STM32_USART4_IS_USED         FALSE
#endif

#if (HAL_USE_SERIAL && STM32_SERIAL_USE_LPUART1)
#define STM32_LPUART1_IS_USED       TRUE
#else
#define STM32_LPUART1_IS_USED       FALSE
#endif

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static inline void usart3_usart4_lpuart1_irq_init(void) {
#if STM32_USART3_IS_USED
  nvicEnableVector(STM32_USART3_NUMBER, STM32_IRQ_USART3_PRIORITY);
#endif
#if STM32_USART4_IS_USED
  nvicEnableVector(STM32_USART4_NUMBER, STM32_IRQ_USART4_PRIORITY);
#endif
#if STM32_LPUART1_IS_USED
  nvicEnableVector(STM32_LPUART1_NUMBER, STM32_IRQ_LPUART1_PRIORITY);
#endif
}

static inline void usart3_usart4_lpuart1_irq_deinit(void) {
#if STM32_USART3_IS_USED
  nvicDisableVector(STM32_USART3_NUMBER);
#endif
#if STM32_USART4_IS_USED
  nvicDisableVector(STM32_USART4_NUMBER);
#endif
#if STM32_LPUART1_IS_USED
  nvicDisableVector(STM32_LPUART1_NUMBER);
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_USART3_IS_USED  || STM32_USART4_IS_USED ||                         \
    STM32_LPUART1_IS_USED || defined(__DOXYGEN__)
/**
 * @brief   USART4, USART5, LPUART1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(STM32_USART3_4_LP1_HANDLER) {

  OSAL_IRQ_PROLOGUE();

#if HAL_USE_SERIAL
#if STM32_SERIAL_USE_UART3
  sd_lld_serve_interrupt(&SD3);
#endif
#if STM32_SERIAL_USE_UART4
  sd_lld_serve_interrupt(&SD4);
#endif
#if STM32_SERIAL_USE_LPUART1
  sd_lld_serve_interrupt(&LPSD1);
#endif
#endif
#if HAL_USE_UART
#if STM32_UART_USE_UART3
  uart_lld_serve_interrupt(&UARTD3);
#endif
#if STM32_UART_USE_UART4
  uart_lld_serve_interrupt(&UARTD4);
#endif
#endif

  OSAL_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/** @} */
