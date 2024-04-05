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
 * @file      main.c
 * @brief     main source file
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
#include "driver_ad9833_basic.h"
#include "shell.h"
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                              /**< uart buffer */
volatile uint16_t g_len;                         /**< uart buffer length */
static int gs_listen_fd;                         /**< network handle */
static int gs_conn_fd;                           /**< network handle */
static struct sockaddr_in gs_server_addr;        /**< server address */

/**
 * @brief     ad9833 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ad9833(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"freq", required_argument, NULL, 1},
        {"mode", required_argument, NULL, 2},
        {"number", required_argument, NULL, 3},
        {"phase", required_argument, NULL, 4},
        {"time", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t ms = 10 * 1000;
    double freq = 0.0;
    uint8_t freq_flag = 0;
    double phase = 0.0;
    uint8_t phase_flag = 0;
    ad9833_output_mode_t mode = AD9833_OUTPUT_MODE_SIN;
    uint8_t mode_flag = 0;
    ad9833_number_t number = AD9833_NUMBER_0;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* freq */
            case 1 :
            {
                /* set the freq*/
                freq = atof(optarg);
                freq_flag = 1;

                break;
            }

            /* mode */
            case 2 :
            {
                /* set output mode */
                if (strcmp("SIN", optarg) == 0)
                {
                    mode = AD9833_OUTPUT_MODE_SIN;
                    mode_flag = 1;
                }
                else if (strcmp("TRI", optarg) == 0)
                {
                    mode = AD9833_OUTPUT_MODE_TRI;
                    mode_flag = 1;
                }
                else if (strcmp("DAC_HALF", optarg) == 0)
                {
                    mode = AD9833_OUTPUT_MODE_DAC_HALF;
                    mode_flag = 1;
                }
                else if (strcmp("DAC", optarg) == 0)
                {
                    mode = AD9833_OUTPUT_MODE_DAC;
                    mode_flag = 1;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* number */
            case 3 :
            {
                /* set number */
                if (strcmp("0", optarg) == 0)
                {
                    number = AD9833_NUMBER_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    number = AD9833_NUMBER_1;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* phase */
            case 4 :
            {
                /* set the phase */
                phase = atof(optarg);
                phase_flag = 1;

                break;
            }

            /* time */
            case 5 :
            {
                /* set the time */
                ms = atoi(optarg);

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_output", type) == 0)
    {
        uint8_t res;

        /* run output test */
        res = ad9833_output_test(number, ms);
        if (res != 0)
        {
            return 1;
        }

        return 0;
    }
    else if (strcmp("e_init", type) == 0)
    {
        uint8_t res;

        /* init */
        res = ad9833_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* output */
        ad9833_interface_debug_print("init.\n");

        return 0;
    }
    else if (strcmp("e_deinit", type) == 0)
    {
        uint8_t res;

        /* deinit */
        res = ad9833_basic_deinit();
        if (res != 0)
        {
            return 1;
        }

        /* output */
        ad9833_interface_debug_print("deinit.\n");

        return 0;
    }
    else if (strcmp("e_freq", type) == 0)
    {
        uint8_t res;

        if (freq_flag == 0)
        {
            /* output */
            ad9833_interface_debug_print("no --freq.\n");

            return 0;
        }

        /* output */
        ad9833_interface_debug_print("number%d output freq %0.4fHz.\n", number, freq);

        /* set number */
        res = ad9833_basic_set_used_register(number);
        if (res != 0)
        {
            return 1;
        }

        /* set freq */
        res = ad9833_basic_set_frequency(number, freq);
        if (res != 0)
        {
            return 1;
        }

        return 0;
    }
    else if (strcmp("e_phase", type) == 0)
    {
        uint8_t res;

        if (phase_flag == 0)
        {
            /* output */
            ad9833_interface_debug_print("no --phase.\n");

            return 0;
        }

        /* output */
        ad9833_interface_debug_print("number%d output phase %0.4fpi.\n", number, phase / 3.14159265357);

        /* set number */
        res = ad9833_basic_set_used_register(number);
        if (res != 0)
        {
            return 1;
        }

        /* set phase */
        res = ad9833_basic_set_phase(number, phase);
        if (res != 0)
        {
            return 1;
        }

        return 0;
    }
    else if (strcmp("e_mode", type) == 0)
    {
        const char name[][16] = {"sinusoid", "" ,"triangle",
                                 "", "dac half data", "dac data"};
        uint8_t res;

        if (mode_flag == 0)
        {
            /* output */
            ad9833_interface_debug_print("no --mode.\n");

            return 0;
        }

        /* output */
        ad9833_interface_debug_print("output mode %s.\n", name[mode], phase / 3.14159265357);

        /* set output mode */
        res = ad9833_basic_set_output_mode(mode);
        if (res != 0)
        {
            return 1;
        }

        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ad9833_interface_debug_print("Usage:\n");
        ad9833_interface_debug_print("  ad9833 (-i | --information)\n");
        ad9833_interface_debug_print("  ad9833 (-h | --help)\n");
        ad9833_interface_debug_print("  ad9833 (-p | --port)\n");
        ad9833_interface_debug_print("  ad9833 (-t output | --test=output) [--number=<0 | 1>] [--time=<ms>]\n");
        ad9833_interface_debug_print("  ad9833 (-e init | --example=init)\n");
        ad9833_interface_debug_print("  ad9833 (-e deinit | --example=deinit)\n");
        ad9833_interface_debug_print("  ad9833 (-e freq | --example=freq) --freq=<hz> [--number=<0 | 1>]\n");
        ad9833_interface_debug_print("  ad9833 (-e phase | --example=phase) --phase=<rad> [--number=<0 | 1>]\n");
        ad9833_interface_debug_print("  ad9833 (-e mode | --example=mode) --mode=<SIN | TRI | DAC_HALF | DAC>\n");
        ad9833_interface_debug_print("\n");
        ad9833_interface_debug_print("Options:\n");
        ad9833_interface_debug_print("  -e <init | deinit | freq | phase | mode>, --example=<init | deinit | freq | phase | mode>\n");
        ad9833_interface_debug_print("                                 Run the driver example.\n");
        ad9833_interface_debug_print("      --freq=<hz>                Set the output frequency in hz.\n");
        ad9833_interface_debug_print("  -h, --help                     Show the help.\n");
        ad9833_interface_debug_print("  -i, --information              Show the chip information.\n");
        ad9833_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        ad9833_interface_debug_print("      --mode=<SIN | TRI | DAC_HALF | DAC>\n");
        ad9833_interface_debug_print("                                 Set the output mode.\n");
        ad9833_interface_debug_print("      --number=<0 | 1>           Set the used register number.([default: 0])\n");
        ad9833_interface_debug_print("      --phase=<rad>              Set the ouput phase in rad.\n");
        ad9833_interface_debug_print("  -t <output>, --test=<output>   Run the driver test.\n");
        ad9833_interface_debug_print("      --time=<ms>                Set the running time in ms.([default: 10000])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ad9833_info_t info;

        /* print ad9833 info */
        ad9833_info(&info);
        ad9833_interface_debug_print("ad9833: chip is %s.\n", info.chip_name);
        ad9833_interface_debug_print("ad9833: manufacturer is %s.\n", info.manufacturer_name);
        ad9833_interface_debug_print("ad9833: interface is %s.\n", info.interface);
        ad9833_interface_debug_print("ad9833: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ad9833_interface_debug_print("ad9833: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ad9833_interface_debug_print("ad9833: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ad9833_interface_debug_print("ad9833: max current is %0.2fmA.\n", info.max_current_ma);
        ad9833_interface_debug_print("ad9833: max temperature is %0.1fC.\n", info.temperature_max);
        ad9833_interface_debug_print("ad9833: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ad9833_interface_debug_print("ad9833: SPI interface SCK connected to GPIO11(BCM).\n");
        ad9833_interface_debug_print("ad9833: SPI interface MOMI connected to GPIO10(BCM).\n");
        ad9833_interface_debug_print("ad9833: SPI interface CS connected to GPIO8(BCM).\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief  socket init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
static uint8_t a_socket_init(void)
{
    int optval;
    
    /* creat a socket */
    gs_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (gs_listen_fd < 0) 
    {
        ad9833_interface_debug_print("ad9833: create socket failed.\n");
        
        return 1;
    }
    
    /* set the server port */
    memset(&gs_server_addr, 0, sizeof(gs_server_addr));
    gs_server_addr.sin_family = AF_INET;
    gs_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    gs_server_addr.sin_port = htons(6666);
    
    /* enable same port binding */
    optval = 1;
    if (setsockopt(gs_listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) < 0)
    {
        ad9833_interface_debug_print("ad9833: create socket failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* bind the port */
    if (bind(gs_listen_fd, (struct sockaddr*)&gs_server_addr, sizeof(gs_server_addr)) < 0) 
    {
        ad9833_interface_debug_print("ad9833: bind failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    }
    
    /* listen the port */
    if (listen(gs_listen_fd, 10) < 0) 
    {
        ad9833_interface_debug_print("ad9833: listen failed.\n");
        (void)close(gs_listen_fd);
        
        return 1;
    } 
    
    return 0;
}

/**
 * @brief     socket read
 * @param[in] *buf points to a buffer address
 * @param[in] len is the buffer length
 * @return    status code
 *             - 0 success
 *             - 1 read failed
 * @note      none
 */
static uint16_t a_socket_read(uint8_t *buf, uint16_t len)
{
    int n;
    
    /* wait data */
    gs_conn_fd = accept(gs_listen_fd, (struct sockaddr *)NULL, NULL);
    if (gs_conn_fd < 0) 
    {
        ad9833_interface_debug_print("ad9833: accept failed.\n");
        (void)close(gs_conn_fd);

        return 1;
    }
    
    /* read data */
    n = recv(gs_conn_fd, buf, len, 0);
    
    /* close the socket */
    (void)close(gs_conn_fd);
    
    return n;
}

/**
 * @brief     signal handler
 * @param[in] signum is the signal number
 * @note      none
 */
static void a_sig_handler(int signum)
{
    if (SIGINT == signum)
    {
        ad9833_interface_debug_print("ad9833: close the server.\n");
        (void)close(gs_listen_fd);
        exit(0);
    }
    
    return;
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* socket init*/
    res = a_socket_init();
    if (res != 0)
    {
        ad9833_interface_debug_print("ad9833: socket init failed.\n");
        
        return 1;
    }
    
    /* shell init && register ad9833 function */
    shell_init();
    shell_register("ad9833", ad9833);
    ad9833_interface_debug_print("ad9833: welcome to libdriver ad9833.\n");
    
    /* set the signal */
    signal(SIGINT, a_sig_handler);
    
    while (1)
    {
        /* read uart */
        g_len = a_socket_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                ad9833_interface_debug_print("ad9833: run failed.\n");
            }
            else if (res == 2)
            {
                ad9833_interface_debug_print("ad9833: unknown command.\n");
            }
            else if (res == 3)
            {
                ad9833_interface_debug_print("ad9833: length is too long.\n");
            }
            else if (res == 4)
            {
                ad9833_interface_debug_print("ad9833: pretreat failed.\n");
            }
            else if (res == 5)
            {
                ad9833_interface_debug_print("ad9833: param is invalid.\n");
            }
            else
            {
                ad9833_interface_debug_print("ad9833: unknown status code.\n");
            }
        }
    }
}
