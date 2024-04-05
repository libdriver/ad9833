### 1. Board

#### 1.1 Board Info

Chip Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOSI/CS GPIO11/GPIO10/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ad9833 REQUIRED)
```

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

#### 3.2 How to run

```shell
# open one terminal and run the server
./ad9833_server 
```
```shell
# open another terminal and sent the command
./ad9833 xxx xxx xxx ...
```

#### 3.3 Command Example

```shell
./ad9833 -i

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
./ad9833 -p

ad9833: SPI interface SCK connected to GPIO11(BCM).
ad9833: SPI interface MOMI connected to GPIO10(BCM).
ad9833: SPI interface CS connected to GPIO8(BCM).
```

```shell
./ad9833 -t output --number=0 --time=10000

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
./ad9833 -e init

init.
```

```shell
./ad9833 -e deinit

deinit.
```

```shell
./ad9833 -e freq --freq=50000 --number=0

number0 output freq 50000.0000Hz.
```
```shell
./ad9833 -e phase --phase=1.570796 --number=0

number0 output phase 0.5000pi.
```
```shell
./ad9833 -e mode --mode=SIN

output mode sinusoid.
```

```shell
./ad9833 -h

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

