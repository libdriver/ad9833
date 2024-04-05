[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AD9833

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ad9833/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AD9833是一款低功耗可编程波形发生器，能够产生正弦波、三角波和方波输出，在各种类型的传感、驱动和时域反射计（TDR）应用中生成需要的波形。AD9833输出频率和相位可通过软件编程，可以实现轻松调谐，不需要外部组件。频率寄存器为28位宽：时钟频率为25 MHz，可实现0.1 Hz的分辨率；AD9833的时钟频率为1 MHz，可调谐到0.004 Hz的分辨率。AD9833通过3线串行接口写入。该串行接口以高达40MHz的时钟频率工作，并与DSP和微控制器标准兼容。该设备的电源电压为2.3 V至5.5 V。AD9833具有断电功能（SLEEP）。此功能允许设备未使用的部分断电，从而最大限度地减少部件的电流消耗。例如，当产生时钟输出时，DAC可以断电。

LibDriver AD9833是LibDriver推出的AD9833全功能驱动，该驱动提供直接数字频率合成(DDS)等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver AD9833的源文件。

/interface目录包含了LibDriver AD9833与平台无关的SPI总线模板。

/test目录包含了LibDriver AD9833驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver AD9833编程范例。

/doc目录包含了LibDriver AD9833离线文档。

/datasheet目录包含了AD9833数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/ad9833/index.html](https://www.libdriver.com/docs/ad9833/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。