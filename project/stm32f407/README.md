### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MOSI/CS  PA5/PA7/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AD9833

#### 3.1 Command Instruction

1. Show ad9833 chip and driver information.

   ```shell
   ad9833 (-i | --information)
   ```

2. Show ad9833 help.

   ```shell
   ad9833 (-h | --help)
   ```

3. Show ad9833 pin connections of the current board.

   ```shell
   ad9833 (-p | --port)
   ```

5. Run ad9833 output test, ms means test time.

   ```shell
   ad9833 (-t output | --test=output) [--number=<0 | 1>] [--time=<ms>]
   ```

6. Run ad9833 init function.

   ```shell
   ad9833 (-e init | --example=init)
   ```
6. Run ad9833 deinit function.

   ```shell
   ad9833 (-e deinit | --example=deinit)
   ```
   
7. Run ad9833 freq function, hz means output frequency in hz.

   ```shell
   ad9833 (-e freq | --example=freq) --freq=<hz> [--number=<0 | 1>]
   ```
7. Run ad9833 phase function, rad means output phase in rad.

   ```shell
   ad9833 (-e phase | --example=phase) --phase=<rad> [--number=<0 | 1>]
   ```
7. Run ad9833 mode function.

   ```shell
   ad9833 (-e mode | --example=mode) --mode=<SIN | TRI | DAC_HALF | DAC>
   ```
   
#### 3.2 Command Example

```shell
ad9833 -i

ad9833: chip is Analog Devices AD9833.
ad9833: manufacturer is Analog Devices.
ad9833: interface is SPI.
ad9833: driver version is 1.0.
ad9833: min supply voltage is 2.3V.
ad9833: max supply voltage is 5.5V.
ad9833: max current is 5.50mA.
ad9833: max temperature is 85.0C.
ad9833: min temperature is -40.0C.
```

```shell
ad9833 -p

ad9833: SCK connected to GPIOA PIN5.
ad9833: MOSI connected to GPIOA PIN7.
ad9833: CS connected to GPIOA PIN4.
```

```shell
ad9833 -t output --number=0 --time=10000

ad9833: chip is Analog Devices AD9833.
ad9833: manufacturer is Analog Devices.
ad9833: interface is SPI.
ad9833: driver version is 1.0.
ad9833: min supply voltage is 2.3V.
ad9833: max supply voltage is 5.5V.
ad9833: max current is 5.50mA.
ad9833: max temperature is 85.0C.
ad9833: min temperature is -40.0C.
ad9833: start output test.
ad9833: use frequency register 0.
ad9833: use phase register 0.
ad9833: set frequency 1000Hz.
ad9833: set phase 0.
ad9833: output sin.
ad9833: output triangle.
ad9833: output dac half data.
ad9833: output dac data.
ad9833: set frequency 10KHz.
ad9833: set frequency 50KHz.
ad9833: set phase 0.5pi.
ad9833: set frequency 2000Hz.
ad9833: finish output test.
```

```shell
ad9833 -e init

init.
```

```shell
ad9833 -e deinit

deinit.
```

```shell
ad9833 -e freq --freq=50000 --number=0

number0 output freq 50000.0000Hz.
```
```shell
ad9833 -e phase --phase=1.570796 --number=0

number0 output phase 0.5000pi.
```
```shell
ad9833 -e mode --mode=SIN

output mode sinusoid.
```

```shell
ad9833 -h

Usage:
  ad9833 (-i | --information)
  ad9833 (-h | --help)
  ad9833 (-p | --port)
  ad9833 (-t output | --test=output) [--number=<0 | 1>] [--time=<ms>]
  ad9833 (-e init | --example=init)
  ad9833 (-e deinit | --example=deinit)
  ad9833 (-e freq | --example=freq) --freq=<hz> [--number=<0 | 1>]
  ad9833 (-e phase | --example=phase) --phase=<rad> [--number=<0 | 1>]
  ad9833 (-e mode | --example=mode) --mode=<SIN | TRI | DAC_HALF | DAC>

Options:
  -e <init | deinit | freq | phase | mode>, --example=<init | deinit | freq | phase | mode>
                                 Run the driver example.
      --freq=<hz>                Set the output frequency in hz.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
      --mode=<SIN | TRI | DAC_HALF | DAC>
                                 Set the output mode.
      --number=<0 | 1>           Set the used register number.([default: 0])
      --phase=<rad>              Set the ouput phase in rad.
  -t <output>, --test=<output>   Run the driver test.
      --time=<ms>                Set the running time in ms.([default: 10000])
```

