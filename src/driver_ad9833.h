/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ad9833.h
 * @brief     driver ad9833 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-04-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/04/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_AD9833_H
#define DRIVER_AD9833_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ad9833_driver ad9833 driver function
 * @brief    ad9833 driver modules
 * @{
 */

/**
 * @addtogroup ad9833_basic_driver
 * @{
 */

/**
 * @brief ad9833 bool enumeration definition
 */
typedef enum
{
    AD9833_BOOL_FALSE = 0x00,        /**< disable function */
    AD9833_BOOL_TRUE  = 0x01,        /**< enable function */
} ad9833_bool_t;

/**
 * @brief ad9833 number enumeration definition
 */
typedef enum
{
    AD9833_NUMBER_0 = 0x00,        /**< number 0 */
    AD9833_NUMBER_1 = 0x01,        /**< number 1 */
} ad9833_number_t;

/**
 * @brief ad9833 output mode enumeration definition
 */
typedef enum
{
    AD9833_OUTPUT_MODE_SIN      = 0x00,        /**< sinusoid */
    AD9833_OUTPUT_MODE_TRI      = 0x02,        /**< triangle */
    AD9833_OUTPUT_MODE_DAC_HALF = 0x04,        /**< dac half data */
    AD9833_OUTPUT_MODE_DAC      = 0x05,        /**< dac data */
} ad9833_output_mode_t;

/**
 * @brief ad9833 handle structure definition
 */
typedef struct ad9833_handle_s
{
    uint8_t (*spi_init)(void);                                   /**< point to an spi_init function address */
    uint8_t (*spi_deinit)(void);                                 /**< point to an spi_deinit function address */
    uint8_t (*spi_write_cmd)(uint8_t *buf, uint16_t len);        /**< point to an spi_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                               /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);             /**< point to a debug_print function address */
    uint8_t inited;                                              /**< inited flag */
    uint16_t conf;                                               /**< conf */
} ad9833_handle_t;

/**
 * @brief ad9833 information structure definition
 */
typedef struct ad9833_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ad9833_info_t;

/**
 * @}
 */

/**
 * @defgroup ad9833_link_driver ad9833 link driver function
 * @brief    ad9833 link driver modules
 * @ingroup  ad9833_driver
 * @{
 */

/**
 * @brief     initialize ad9833_handle_t structure
 * @param[in] HANDLE points to an ad9833 handle structure
 * @param[in] STRUCTURE is ad9833_handle_t
 * @note      none
 */
#define DRIVER_AD9833_LINK_INIT(HANDLE, STRUCTURE)       memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to an ad9833 handle structure
 * @param[in] FUC points to an spi_init function address
 * @note      none
 */
#define DRIVER_AD9833_LINK_SPI_INIT(HANDLE, FUC)        (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to an ad9833 handle structure
 * @param[in] FUC points to an spi_deinit function address
 * @note      none
 */
#define DRIVER_AD9833_LINK_SPI_DEINIT(HANDLE, FUC)      (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write_cmd function
 * @param[in] HANDLE points to an ad9833 handle structure
 * @param[in] FUC points to an spi_write_cmd function address
 * @note      none
 */
#define DRIVER_AD9833_LINK_SPI_WRITE_CMD(HANDLE, FUC)   (HANDLE)->spi_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an ad9833 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_AD9833_LINK_DELAY_MS(HANDLE, FUC)        (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an ad9833 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_AD9833_LINK_DEBUG_PRINT(HANDLE, FUC)     (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ad9833_basic_driver ad9833 basic driver function
 * @brief    ad9833 basic driver modules
 * @ingroup  ad9833_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an ad9833 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ad9833_info(ad9833_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an ad9833 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t ad9833_init(ad9833_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an ad9833 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t ad9833_deinit(ad9833_handle_t *handle);

/**
 * @brief     set the used frequency register
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] number is the used register number
 * @return    status code
 *            - 0 success
 *            - 1 set used frequency register failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ad9833_set_used_frequency_register(ad9833_handle_t *handle, ad9833_number_t number);

/**
 * @brief     set the used phase register
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] number is the used register number
 * @return    status code
 *            - 0 success
 *            - 1 set used phase register failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ad9833_set_used_phase_register(ad9833_handle_t *handle, ad9833_number_t number);

/**
 * @brief     set the frequency
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] number is the set register number
 * @param[in] freq is the set frequency
 * @return    status code
 *            - 0 success
 *            - 1 set frequency failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 freq > 0x0FFFFFFF
 * @note      none
 */
uint8_t ad9833_set_frequency(ad9833_handle_t *handle, ad9833_number_t number, uint32_t freq);

/**
 * @brief     set the frequency lsb
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] number is the set register number
 * @param[in] freq is the set frequency
 * @return    status code
 *            - 0 success
 *            - 1 set frequency lsb failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 freq > 0x3FFF
 * @note      none
 */
uint8_t ad9833_set_frequency_lsb(ad9833_handle_t *handle, ad9833_number_t number, uint16_t freq);

/**
 * @brief     set the frequency msb
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] number is the set register number
 * @param[in] freq is the set frequency
 * @return    status code
 *            - 0 success
 *            - 1 set frequency msb failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 freq > 0x3FFF
 * @note      none
 */
uint8_t ad9833_set_frequency_msb(ad9833_handle_t *handle, ad9833_number_t number, uint16_t freq);

/**
 * @brief      convert the frequency to the register raw data
 * @param[in]  *handle points to an ad9833 handle structure
 * @param[in]  hz is the freq in hz
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ad9833_frequency_convert_to_register(ad9833_handle_t *handle, double hz, uint32_t *reg);

/**
 * @brief      convert the register raw data to frequency
 * @param[in]  *handle points to an ad9833 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *hz points to a freq hz buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ad9833_frequency_convert_to_data(ad9833_handle_t *handle, uint32_t reg, double *hz);

/**
 * @brief     set the phase
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] number is the set register number
 * @param[in] phase is the set phase
 * @return    status code
 *            - 0 success
 *            - 1 set phase failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 phase > 0x0FFF
 * @note      none
 */
uint8_t ad9833_set_phase(ad9833_handle_t *handle, ad9833_number_t number, uint16_t phase);

/**
 * @brief      convert the phase to the register raw data
 * @param[in]  *handle points to an ad9833 handle structure
 * @param[in]  rad is the phase in rad
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ad9833_phase_convert_to_register(ad9833_handle_t *handle, double rad, uint16_t *reg);

/**
 * @brief      convert the register raw data to phase
 * @param[in]  *handle points to an ad9833 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *rad points to a phase rad buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ad9833_phase_convert_to_data(ad9833_handle_t *handle, uint16_t reg, double *rad);

/**
 * @brief     reset the chip
 * @param[in] *handle points to an ad9833 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ad9833_reset(ad9833_handle_t *handle);

/**
 * @brief     enable or disable dac power down
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dac power down failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ad9833_set_dac_power_down(ad9833_handle_t *handle, ad9833_bool_t enable);

/**
 * @brief     enable or disable internal clock disable
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set internal clock disable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ad9833_set_internal_clock_disable(ad9833_handle_t *handle, ad9833_bool_t enable);

/**
 * @brief     set output mode
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] mode is the output mode
 * @return    status code
 *            - 0 success
 *            - 1 set output mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ad9833_set_output_mode(ad9833_handle_t *handle, ad9833_output_mode_t mode);

/**
 * @}
 */

/**
 * @defgroup ad9833_extern_driver ad9833 extern driver function
 * @brief    ad9833 extern driver modules
 * @ingroup  ad9833_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] value is the set value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ad9833_set_reg(ad9833_handle_t *handle, uint16_t value);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
