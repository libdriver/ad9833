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
 * @file      driver_ad9833_basic.h
 * @brief     driver ad9833 basic header file
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

#ifndef DRIVER_AD9833_BASIC_H
#define DRIVER_AD9833_BASIC_H

#include "driver_ad9833_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ad9833_example_driver ad9833 example driver function
 * @brief    ad9833 example driver modules
 * @ingroup  ad9833_driver
 * @{
 */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ad9833_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ad9833_basic_deinit(void);

/**
 * @brief     basic example set used register
 * @param[in] number is the used register
 * @return    status code
 *            - 0 success
 *            - 1 set used register failed
 * @note      none
 */
uint8_t ad9833_basic_set_used_register(ad9833_number_t number);

/**
 * @brief     basic example set frequency
 * @param[in] number is the set register
 * @param[in] hz is the set freq in hz
 * @return    status code
 *            - 0 success
 *            - 1 set frequency failed
 * @note      none
 */
uint8_t ad9833_basic_set_frequency(ad9833_number_t number, double hz);

/**
 * @brief     basic example set phase
 * @param[in] number is the set register
 * @param[in] rad is the set rad
 * @return    status code
 *            - 0 success
 *            - 1 set phase failed
 * @note      none
 */
uint8_t ad9833_basic_set_phase(ad9833_number_t number, double rad);

/**
 * @brief     basic example set output mode
 * @param[in] mode is the set output mode
 * @return    status code
 *            - 0 success
 *            - 1 set output mode failed
 * @note      none
 */
uint8_t ad9833_basic_set_output_mode(ad9833_output_mode_t mode);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
