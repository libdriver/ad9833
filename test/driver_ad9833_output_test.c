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
 * @file      driver_ad9833_output_test.c
 * @brief     driver ad9833 output test source file
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
 
#include "driver_ad9833_output_test.h"
#include <math.h>
#include <stdlib.h>

static ad9833_handle_t gs_handle;        /**< ad9833 handle */

/**
 * @brief     output test
 * @param[in] number is the register number
 * @param[in] ms is the test time in ms
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ad9833_output_test(ad9833_number_t number, uint32_t ms)
{
    uint8_t res;
    uint32_t reg32;
    uint16_t reg16;
    double hz;
    double rad;
    ad9833_info_t info;
    
    /* link function */
    DRIVER_AD9833_LINK_INIT(&gs_handle, ad9833_handle_t);
    DRIVER_AD9833_LINK_SPI_INIT(&gs_handle, ad9833_interface_spi_init);
    DRIVER_AD9833_LINK_SPI_DEINIT(&gs_handle, ad9833_interface_spi_deinit);
    DRIVER_AD9833_LINK_SPI_WRITE_CMD(&gs_handle, ad9833_interface_spi_write_cmd);
    DRIVER_AD9833_LINK_DELAY_MS(&gs_handle, ad9833_interface_delay_ms);
    DRIVER_AD9833_LINK_DEBUG_PRINT(&gs_handle, ad9833_interface_debug_print);
    
    /* get chip information */
    res = ad9833_info(&info);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        ad9833_interface_debug_print("ad9833: chip is %s.\n", info.chip_name);
        ad9833_interface_debug_print("ad9833: manufacturer is %s.\n", info.manufacturer_name);
        ad9833_interface_debug_print("ad9833: interface is %s.\n", info.interface);
        ad9833_interface_debug_print("ad9833: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ad9833_interface_debug_print("ad9833: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ad9833_interface_debug_print("ad9833: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ad9833_interface_debug_print("ad9833: max current is %0.2fmA.\n", info.max_current_ma);
        ad9833_interface_debug_print("ad9833: max temperature is %0.1fC.\n", info.temperature_max);
        ad9833_interface_debug_print("ad9833: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* ad9833 init */
    res = ad9833_init(&gs_handle);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: init failed.\n");
       
        return 1;
    }
    
    /* start output test */
    ad9833_interface_debug_print("ad9833: start output test.\n");
    
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
    
    /* output */
    ad9833_interface_debug_print("ad9833: use frequency register %d.\n", number == AD9833_NUMBER_0 ? 0 : 1);
    
    /* number */
    res = ad9833_set_used_frequency_register(&gs_handle, number);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set used frequency register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: use phase register %d.\n", number == AD9833_NUMBER_0 ? 0 : 1);
    
    /* number */
    res = ad9833_set_used_phase_register(&gs_handle, number);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set used phase register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to register */
    res = ad9833_frequency_convert_to_register(&gs_handle, 1000, &reg32);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: frequency convert to register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: set frequency 1000Hz.\n");
    
    /* set frequency */
    res = ad9833_set_frequency(&gs_handle, number, reg32);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set frequency failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to register */
    res = ad9833_phase_convert_to_register(&gs_handle, 0.0, &reg16);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: phase convert to register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set phase */
    res = ad9833_set_phase(&gs_handle, number, reg16);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set phase failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: set phase 0.\n");
    
    /* output sin */
    res = ad9833_set_output_mode(&gs_handle, AD9833_OUTPUT_MODE_SIN);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set output mode failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: output sin.\n");
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* output triangle */
    res = ad9833_set_output_mode(&gs_handle, AD9833_OUTPUT_MODE_TRI);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set output mode failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: output triangle.\n");
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* output dac half data */
    res = ad9833_set_output_mode(&gs_handle, AD9833_OUTPUT_MODE_DAC_HALF);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set output mode failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: output dac half data.\n");
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* output dac half data */
    res = ad9833_set_output_mode(&gs_handle, AD9833_OUTPUT_MODE_DAC);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set output mode failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: output dac data.\n");
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* output sin */
    res = ad9833_set_output_mode(&gs_handle, AD9833_OUTPUT_MODE_SIN);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set output mode failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to register */
    res = ad9833_frequency_convert_to_register(&gs_handle, 10000, &reg32);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: frequency convert to register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: set frequency 10KHz.\n");
    
    /* set frequency */
    res = ad9833_set_frequency(&gs_handle, number, reg32);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set frequency failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* convert to register */
    res = ad9833_frequency_convert_to_register(&gs_handle, 50000, &reg32);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: frequency convert to register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: set frequency 50KHz.\n");
    
    /* set frequency */
    res = ad9833_set_frequency(&gs_handle, number, reg32);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set frequency failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* convert to register */
    res = ad9833_phase_convert_to_register(&gs_handle, 3.14159265357 / 2.0, &reg16);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: phase convert to register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to data */
    res = ad9833_phase_convert_to_data(&gs_handle, reg16, &rad);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: phase convert to data failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: set phase %0.1fpi.\n", rad / 3.14159265357);
    
    /* set phase */
    res = ad9833_set_phase(&gs_handle, number, reg16);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set phase failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* convert to register */
    res = ad9833_frequency_convert_to_register(&gs_handle, 2000, &reg32);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: frequency convert to register failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* convert to data */
    res = ad9833_frequency_convert_to_data(&gs_handle, reg32, &hz);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: frequency convert to data failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    ad9833_interface_debug_print("ad9833: set frequency %0.0fHz.\n", hz);
    
    /* set frequency msb */
    res = ad9833_set_frequency_msb(&gs_handle, number, (reg32 >> 14) & 0x3FFF);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set frequency msb failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set frequency lsb */
    res = ad9833_set_frequency_lsb(&gs_handle, number, (reg32 >> 0) & 0x3FFF);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: set frequency lsb failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay */
    ad9833_interface_delay_ms(ms);
    
    /* reset */
    res = ad9833_reset(&gs_handle);
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: reset failed.\n");
        (void)ad9833_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish output test */
    ad9833_interface_debug_print("ad9833: finish output test.\n");
    (void)ad9833_deinit(&gs_handle);
    
    return 0;
}
