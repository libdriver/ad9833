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
 * @file      driver_ad9833.c
 * @brief     driver ad9833 source file
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

#include "driver_ad9833.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Analog Devices AD9833"        /**< chip name */
#define MANUFACTURER_NAME         "Analog Devices"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.3f                           /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                           /**< chip max supply voltage */
#define MAX_CURRENT               5.5f                           /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                         /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                          /**< chip max operating temperature */
#define DRIVER_VERSION            1000                           /**< driver version */

/**
 * @brief     spi write
 * @param[in] *handle points to an ad9833 handle structure
 * @param[in] reg is the set reg
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_ad9833_spi_write(ad9833_handle_t *handle, uint16_t reg)
{
    uint8_t buf[2];
    
    buf[0] = (reg >> 8) & 0xFF;                    /* set msb */
    buf[1] = (reg >> 0) & 0xFF;                    /* set lsb */
    if (handle->spi_write_cmd(buf, 2) != 0)        /* write command */
    {
        return 1;                                  /* return error */
    }
    
    return 0;                                      /* success return 0 */
}

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
uint8_t ad9833_init(ad9833_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->debug_print == NULL)                                    /* check debug_print */
    {
        return 3;                                                       /* return error */
    }
    if (handle->spi_init == NULL)                                       /* check spi_init */
    {
        handle->debug_print("ad9833: spi_init is null.\n");             /* spi_init is null */
       
        return 3;                                                       /* return error */
    }
    if (handle->spi_deinit == NULL)                                     /* check spi_init */
    {
        handle->debug_print("ad9833: spi_deinit is null.\n");           /* spi_deinit is null */
       
        return 3;                                                       /* return error */
    }
    if (handle->spi_write_cmd == NULL)                                  /* check spi_write_cmd */
    {
        handle->debug_print("ad9833: spi_write_cmd is null.\n");        /* spi_write_cmd is null */
       
        return 3;                                                       /* return error */
    }
    if (handle->delay_ms == NULL)                                       /* check delay_ms */
    {
        handle->debug_print("ad9833: delay_ms is null.\n");             /* delay_ms is null */
       
        return 3;                                                       /* return error */
    }
    
    if (handle->spi_init() != 0)                                        /* spi init */
    { 
        handle->debug_print("ad9833: spi init failed.\n");              /* spi init failed */
       
        return 3;                                                       /* return error */
    }
    handle->conf = 0;                                                   /* init 0 */
    conf = handle->conf;                                                /* get config */
    conf &= ~(1 << 8);                                                  /* clear reset */
    conf |= 1 << 8;                                                     /* set reset */
    res = a_ad9833_spi_write(handle, conf);                             /* write config */
    if (res != 0)                                                       /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");          /* write config failed */
        
        return 4;                                                       /* return error */
    }
    handle->delay_ms(10);                                               /* delay 10ms */
    conf &= ~(1 << 8);                                                  /* clear reset */
    res = a_ad9833_spi_write(handle, conf);                             /* write config */
    if (res != 0)                                                       /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");          /* write config failed */
        
        return 4;                                                       /* return error */
    }
    handle->inited = 1;                                                 /* flag initialization */

    return 0;                                                           /* success return 0 */
}

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
uint8_t ad9833_deinit(ad9833_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    handle->conf &= ~(1 << 7);                                        /* clear settings */
    handle->conf |= 1 << 7;                                           /* set enable */
    handle->conf &= ~(1 << 6);                                        /* clear settings */
    handle->conf |= 1 << 6;                                           /* set enable */
    conf = handle->conf;                                              /* get config */
    conf &= ~(3 << 14);                                               /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
        
        return 4;                                                     /* return error */
    }
    if (handle->spi_deinit() != 0)                                    /* spi deinit */
    {
        handle->debug_print("ad9833: spi deinit failed.\n");          /* spi deinit failed */
        
        return 1;                                                     /* return error */
    }         
    handle->inited = 0;                                               /* flag close */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ad9833_set_used_frequency_register(ad9833_handle_t *handle, ad9833_number_t number)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    handle->conf &= ~(1 << 11);                                       /* clear settings */
    handle->conf |= (number << 11);                                   /* set number */
    conf = handle->conf;                                              /* get config */
    conf &= ~(3 << 14);                                               /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    } 
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ad9833_set_used_phase_register(ad9833_handle_t *handle, ad9833_number_t number)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    handle->conf &= ~(1 << 10);                                       /* clear settings */
    handle->conf |= (number << 10);                                   /* set number */
    conf = handle->conf;                                              /* get config */
    conf &= ~(3 << 14);                                               /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    } 
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ad9833_set_frequency(ad9833_handle_t *handle, ad9833_number_t number, uint32_t freq)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    if (freq > 0x0FFFFFFF)                                                /* check freq */
    {
        handle->debug_print("ad9833: freq > 0x0FFFFFFF.\n");              /* freq > 0x0FFFFFFF */
        
        return 4;                                                         /* return error */
    }
    
    conf = handle->conf;                                                  /* get config */
    conf |= 1 << 13;                                                      /* set b28 */
    conf &= ~(3 << 14);                                                   /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                               /* write config */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    if (number == AD9833_NUMBER_0)                                        /* number 0 */
    {
        conf = 1 << 14;                                                   /* set freq number0 */
        conf |= freq & 0x3FFF;                                            /* set lsb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
        conf = 1 << 14;                                                   /* set freq number0 */
        conf |= (freq >> 14) & 0x3FFF;                                    /* set msb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    else                                                                  /* number 1 */
    {
        conf = 1 << 15;                                                   /* set freq number1 */
        conf |= freq & 0x3FFF;                                            /* set lsb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
        conf = 1 << 15;                                                   /* set freq number1 */
        conf |= (freq >> 14) & 0x3FFF;                                    /* set msb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ad9833_set_frequency_lsb(ad9833_handle_t *handle, ad9833_number_t number, uint16_t freq)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    if (freq > 0x3FFF)                                                    /* check freq */
    {
        handle->debug_print("ad9833: freq > 0x3FFF.\n");                  /* freq > 0x3FFF */
        
        return 4;                                                         /* return error */
    }
    
    conf = handle->conf;                                                  /* get config */
    conf &= ~(1 << 13);                                                   /* clear b28 */
    conf &= ~(1 << 12);                                                   /* set lsb */
    conf &= ~(3 << 14);                                                   /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                               /* write config */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    if (number == AD9833_NUMBER_0)                                        /* number 0 */
    {
        conf = 1 << 14;                                                   /* set freq number0 */
        conf |= freq;                                                     /* set lsb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    else                                                                  /* number 1 */
    {
        conf = 1 << 15;                                                   /* set freq number1 */
        conf |= freq;                                                     /* set lsb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ad9833_set_frequency_msb(ad9833_handle_t *handle, ad9833_number_t number, uint16_t freq)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    if (freq > 0x3FFF)                                                    /* check freq */
    {
        handle->debug_print("ad9833: freq > 0x3FFF.\n");                  /* freq > 0x3FFF */
        
        return 4;                                                         /* return error */
    }
    
    conf = handle->conf;                                                  /* get config */
    conf &= ~(1 << 13);                                                   /* clear b28 */
    conf |= 1 << 12;                                                      /* set msb */
    conf &= ~(3 << 14);                                                   /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                               /* write config */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");            /* write config failed */
        
        return 1;                                                         /* return error */
    }
    if (number == AD9833_NUMBER_0)                                        /* number 0 */
    {
        conf = 1 << 14;                                                   /* set freq number0 */
        conf |= freq;                                                     /* set lsb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    else                                                                  /* number 1 */
    {
        conf = 1 << 15;                                                   /* set freq number1 */
        conf |= freq;                                                     /* set lsb */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ad9833_set_phase(ad9833_handle_t *handle, ad9833_number_t number, uint16_t phase)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    if (phase > 0x0FFF)                                                   /* check phase */
    {
        handle->debug_print("ad9833: phase > 0x0FFF.\n");                 /* phase > 0x0FFF */
         
        return 4;                                                         /* return error */
    }
    
    if (number == AD9833_NUMBER_0)                                        /* number 0 */
    {
        conf = 3 << 14;                                                   /* set phase */
        conf &= ~(1 << 13);                                               /* set number 0 */
        conf |= phase & 0x0FFF;                                           /* set phase */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    else                                                                  /* number 1 */
    {
        conf = 3 << 14;                                                   /* set phase */
        conf |= 1 << 13;                                                  /* set number 1 */
        conf |= phase & 0x0FFF;                                           /* set phase */
        res = a_ad9833_spi_write(handle, conf);                           /* write config */
        if (res != 0)                                                     /* check result */
        {
            handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
            
            return 1;                                                     /* return error */
        }
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ad9833_reset(ad9833_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    conf = handle->conf;                                                 /* get config */
    conf &= ~(1 << 8);                                                   /* clear reset */
    conf |= 1 << 8;                                                      /* set reset */
    res = a_ad9833_spi_write(handle, conf);                              /* write config */
    if (res != 0)                                                        /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");           /* write config failed */
        
        return 1;                                                        /* return error */
    }
    handle->delay_ms(10);                                                /* delay 10ms */
    conf &= ~(1 << 8);                                                   /* clear reset */
    res = a_ad9833_spi_write(handle, conf);                              /* write config */
    if (res != 0)                                                        /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");           /* write config failed */
        
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t ad9833_set_dac_power_down(ad9833_handle_t *handle, ad9833_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    handle->conf &= ~(1 << 6);                                        /* clear settings */
    handle->conf |= enable << 6;                                      /* set enable */
    conf = handle->conf;                                              /* get config */
    conf &= ~(3 << 14);                                               /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ad9833_set_internal_clock_disable(ad9833_handle_t *handle, ad9833_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    handle->conf &= ~(1 << 7);                                        /* clear settings */
    handle->conf |= enable << 7;                                      /* set enable */
    conf = handle->conf;                                              /* get config */
    conf &= ~(3 << 14);                                               /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ad9833_set_output_mode(ad9833_handle_t *handle, ad9833_output_mode_t mode)
{
    uint8_t res;
    uint8_t c;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    handle->conf &= ~(1 << 5);                                        /* clear opbiten */
    handle->conf &= ~(1 << 3);                                        /* clear div2 */
    handle->conf &= ~(1 << 1);                                        /* clear mode */
    c = mode;                                                         /* copy mode */
    handle->conf |= (((c >> 2) & 0x1) << 5);                          /* set opbiten */
    handle->conf |= (((c >> 0) & 0x1) << 3);                          /* set div2 */
    handle->conf |= (((c >> 1) & 0x1) << 1);                          /* set mode */
    conf = handle->conf;                                              /* get config */
    conf &= ~(3 << 14);                                               /* clear bit14 and bit15 */
    res = a_ad9833_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ad9833_frequency_convert_to_register(ad9833_handle_t *handle, double hz, uint32_t *reg)
{
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    if (handle->inited != 1)                                  /* check handle initialization */
    {
        return 3;                                             /* return error */
    }
    
    *reg = (uint32_t)(hz / (25000000.0 / pow(2, 28)));        /* convert real data to register data */
    
    return 0;                                                 /* success return 0 */
}

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
uint8_t ad9833_frequency_convert_to_data(ad9833_handle_t *handle, uint32_t reg, double *hz)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }
    
    *hz = (double)reg * (25000000.0 / pow(2, 28));        /* convert real data to register data */
    
    return 0;                                             /* success return 0 */
}

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
uint8_t ad9833_phase_convert_to_register(ad9833_handle_t *handle, double rad, uint16_t *reg)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    *reg = (uint32_t)(rad / ((2.0 * 3.14159265357) / 4096.0));        /* convert real data to register data */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ad9833_phase_convert_to_data(ad9833_handle_t *handle, uint16_t reg, double *rad)
{
    if (handle == NULL)                                           /* check handle */
    {
        return 2;                                                 /* return error */
    }
    if (handle->inited != 1)                                      /* check handle initialization */
    {
        return 3;                                                 /* return error */
    }
    
    *rad = (double)reg * ((2.0 * 3.14159265357) / 4096.0);        /* convert real data to register data */
    
    return 0;                                                     /* success return 0 */
}

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
uint8_t ad9833_set_reg(ad9833_handle_t *handle, uint16_t value)
{
    uint8_t res;

    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ad9833_spi_write(handle, value);                          /* write config */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("ad9833: write config failed.\n");        /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an ad9833 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ad9833_info(ad9833_info_t *info)
{
    if (info == NULL)                                             /* check handle */
    {
        return 2;                                                 /* return error */
    }
    
    memset(info, 0, sizeof(ad9833_info_t));                       /* initialize ad9833 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                      /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);      /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                           /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;              /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;              /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                           /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                      /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                      /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                        /* set driver version */
    
    return 0;                                                     /* success return 0 */
}
