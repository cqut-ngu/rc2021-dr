/**
 * *****************************************************************************
 * @file         bsp_gpio.h
 * @brief        gpio of boards
 * @author       NGU
 * @date         20210101
 * @version      1
 * @copyright    Copyright (C) 2021 NGU
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "main.h"

#include <stdint.h>

#undef __BEGIN_DECLS
#undef __END_DECLS

#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

__BEGIN_DECLS

__END_DECLS

static inline void gpio_pin_write(GPIO_TypeDef *gpio,
                                  uint16_t pin,
                                  FlagStatus state)
{
    if (state == SET)
    {
        gpio->BSRR = pin;
    }
    else
    {
        gpio->BSRR = (uint32_t)pin << 16U;
    }
}

static inline void gpio_pin_set(GPIO_TypeDef *gpio,
                                uint16_t pin)
{
    gpio->BSRR = pin;
}

static inline void gpio_pin_reset(GPIO_TypeDef *gpio,
                                  uint16_t pin)
{
    gpio->BSRR = (uint32_t)pin << 16U;
}

static inline FlagStatus gpio_pin_read(GPIO_TypeDef *gpio,
                                       uint16_t pin)
{
    if (gpio->IDR & pin)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

static inline void gpio_pin_toggle(GPIO_TypeDef *gpio,
                                   uint16_t pin)
{
    if ((gpio->ODR & pin) == pin)
    {
        gpio->BSRR = (uint32_t)pin << 16U;
    }
    else
    {
        gpio->BSRR = pin;
    }
}

static inline void gpio_pin_lock(GPIO_TypeDef *gpio,
                                 uint16_t pin)
{
    /* Apply lock key write sequence */
    __IO uint32_t tmp = GPIO_LCKR_LCKK | pin;
    /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
    gpio->LCKR = tmp;
    /* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
    gpio->LCKR = pin;
    /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
    gpio->LCKR = tmp;
    /* Read LCKR register. This read is mandatory to complete key lock sequence */
    tmp = gpio->LCKR;
}

/* Enddef to prevent recursive inclusion ------------------------------------ */
#endif /* __BSP_GPIO_H__ */

/************************ (C) COPYRIGHT NGU ********************END OF FILE****/
