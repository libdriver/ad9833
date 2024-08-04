[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AD9833

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ad9833/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The AD9833 is a low power, programmable waveform generator capable of producing sine, triangular, and square wave outputs. Waveform generation is required in various types of sensing, actuation, and time domain reflectometry (TDR) applications. The output frequency and phase are software programmable, allowing easy tuning. No external components are needed. The frequency registers are 28 bits wide: with a 25 MHz clock rate, resolution of 0.1 Hz can be achieved; with a 1 MHz clock rate, the AD9833 can be tuned to 0.004 Hz resolution. The AD9833 is written to via a 3-wire serial interface. This serial interface operates at clock rates up to 40 MHz and is compatible with DSP and microcontroller standards. The device operates with a power supply from 2.3 V to 5.5 V. The AD9833 has a power-down function (SLEEP). This function allows sections of the device that are not being used to be powered down, thus minimizing the current consumption of the part. For example, the DAC can be powered down when a clock output is being generated.

LibDriver AD9833 is the full function driver of AD9833 launched by LibDriver.It provides the function of direct digital frequency synthesis(DDS) output and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver AD9833 source files.

/interface includes LibDriver AD9833 SPI platform independent template.

/test includes LibDriver AD9833 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver AD9833 sample code.

/doc includes LibDriver AD9833 offline document.

/datasheet includes AD9833 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_ad9833_basic.h"

uint8_t res;

/* init */
res = ad9833_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* set number */
res = ad9833_basic_set_used_register(AD9833_NUMBER_0);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

/* set freq */
res = ad9833_basic_set_frequency(AD9833_NUMBER_0, 10 * 1000);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

...
    
/* set phase */
res = ad9833_basic_set_phase(number, 3.14159265357 / 2);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

...
    
/* set output mode */
res = ad9833_basic_set_output_mode(AD9833_OUTPUT_MODE_SIN);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

...

/* deinit */
(void)ad9833_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/ad9833/index.html](https://www.libdriver.com/docs/ad9833/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.