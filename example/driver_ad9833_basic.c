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
 * @file      driver_ad9833_basic.c
 * @brief     driver ad9833 basic source file
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

#include "driver_ad9833_basic.h"

static ad9833_handle_t gs_handle;        /**< ad9833 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ad9833_basic_init(void)
{
    uint8_t res;

    /* link function */
    DRIVER_AD9833_LINK_INIT(&gs_handle, ad9833_handle_t);
    DRIVER_AD9833_LINK_SPI_INIT(&gs_handle, ad9833_interface_spi_init);
    DRIVER_AD9833_LINK_SPI_DEINIT(&gs_handle, ad9833_interface_spi_deinit);
    DRIVER_AD9833_LINK_SPI_WRITE_CMD(&gs_handle, ad9833_interface_spi_write_cmd);
    DRIVER_AD9833_LINK_DELAY_MS(&gs_handle, ad9833_interface_delay_ms);
    DRIVER_AD9833_LINK_DEBUG_PRINT(&gs_handle, ad9833_interface_debug_print);

    /* ad9833 init */
    res = ad9833_init(&gs_handle);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: init failed.\n");

        return 1;
    }

    /* disable dac power down */
    res = ad9833_set_dac_power_down(&gs_handle, AD9833_BOOL_FALSE);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set dac power down failed.\n");
        (void)ad9833_deinit(&gs_handle);

        return 1;
    }

    /* enable internal clock */
    res = ad9833_set_internal_clock_disable(&gs_handle, AD9833_BOOL_FALSE);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set internal clock disable failed.\n");
        (void)ad9833_deinit(&gs_handle);

        return 1;
    }

    return 0;
}

/**
 * @brief     basic example set used register
 * @param[in] number is the used register
 * @return    status code
 *            - 0 success
 *            - 1 set used register failed
 * @note      none
 */
uint8_t ad9833_basic_set_used_register(ad9833_number_t number)
{
    uint8_t res;

    /* number */
    res = ad9833_set_used_frequency_register(&gs_handle, number);
    if (res != 0)
    {
        return 1;
    }

    /* number */
    res = ad9833_set_used_phase_register(&gs_handle, number);
    if (res != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief     basic example set frequency
 * @param[in] number is the set register
 * @param[in] hz is the set freq in hz
 * @return    status code
 *            - 0 success
 *            - 1 set frequency failed
 * @note      none
 */
uint8_t ad9833_basic_set_frequency(ad9833_number_t number, double hz)
{
    uint8_t res;
    uint32_t reg32;

    /* convert to register */
    res = ad9833_frequency_convert_to_register(&gs_handle, hz, &reg32);
    if (res != 0)
    {
        return 1;
    }

    /* set frequency */
    res = ad9833_set_frequency(&gs_handle, number, reg32);
    if (res != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief     basic example set phase
 * @param[in] number is the set register
 * @param[in] rad is the set rad
 * @return    status code
 *            - 0 success
 *            - 1 set phase failed
 * @note      none
 */
uint8_t ad9833_basic_set_phase(ad9833_number_t number, double rad)
{
    uint8_t res;
    uint16_t reg16;

    /* convert to register */
    res = ad9833_phase_convert_to_register(&gs_handle, rad, &reg16);
    if (res != 0)
    {
        return 1;
    }

    /* set phase */
    res = ad9833_set_phase(&gs_handle, number, reg16);
    if (res != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief     basic example set output mode
 * @param[in] mode is the set output mode
 * @return    status code
 *            - 0 success
 *            - 1 set output mode failed
 * @note      none
 */
uint8_t ad9833_basic_set_output_mode(ad9833_output_mode_t mode)
{
    uint8_t res;

    /* set output mode */
    res = ad9833_set_output_mode(&gs_handle, mode);
    if (res != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ad9833_basic_deinit(void)
{
    /* deinit */
    if (ad9833_deinit(&gs_handle) != 0)
    {
        return 1;
    }

    return 0;
}
