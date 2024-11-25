# GR533x Series SoC

## 1. Introduction

- The Goodix GR533x series is a Bluetooth Low Energy (Bluetooth LE) 5.3 System-on-Chip (SoC) designed for various applications such as smart home, health care, smart trackers, and IoT modules, supporting Bluetooth Mesh networking protocols.

- Based on Arm® Cortex®-M4F CPU core running at 64 MHz, the GR533x integrates a 2.4 GHz RF transceiver, Bluetooth LE 5.3 protocol stack, 512 KB on-chip Flash memory, 96 KB system SRAM, and a rich set of peripherals. It provides excellent RF performance, with a maximum of +15 dBm TX power, -99 dBm RX sensitivity, and a maximum of 114 dB link budget in Bluetooth LE 1 Mbps mode.

- With two main power supply schemes (DC-DC and SYS_LDO), the GR533x offers flexible options to achieve a balance between low power consumption and economical BOM.



## 2. Key Features

- Bluetooth Low Energy 5.3 transceiver integrating Controller and Host layers
  - Supported data rates: 1 Mbps, 2 Mbps, Long Range (500 kbps, 125 kbps)
  - TX power:
    - GR5331: up to 6 dBm
    - GR5332: up to 15 dBm
  - RX sensitivity:
    - GR5331: -97.5 dBm @ 1 Mbps
    - GR5332: -99 dBm @ 1 Mbps
  - Power consumption at 3.3 V VBAT input on GR5331:
    - TX current: 3.8 mA @ 0 dBm output power (DC-DC supply, 16 MHz system clock)
    - RX current: 4.7 mA @ 1 Mbps (DC-DC supply, 16 MHz system clock)
  - Power consumption at 3.3 V VBAT input on GR5332:
    - TX current: 5.9 mA @ 0 dBm output power (DC-DC supply, 16 MHz system clock)
    - TX current: 86.3 mA @ 15 dBm output power (SYS_LDO supply, 64 MHz system clock)
    - RX current: 4.9 mA @ 1 Mbps (DC-DC supply, 16 MHz system clock)
- Arm® Cortex®-M4F 32-bit micro-processor with floating point support
  - Up to 64 MHz clock frequency
  - Built-in Memory Protection Unit (MPU) supporting eight programmable regions
  - Hardware Floating Point Unit (FPU)
  - Built-in Nested Vectored Interrupt Controller (NVIC)
  - Non-maskable Interrupt (NMI) input
  - Serial Wire Debug (SWD) with 16 breakpoints, two watchpoints, and a debug timestamp counter
  - 32 µA/MHz CoreMark running from Flash @ 3.3 V, 64 MHz
- On-chip memory
  - 96 KB RAM data memory with retention capabilities
  - 8 KB cache RAM instruction memory with retention capabilities
  - ROM for boot and partial Bluetooth LE Protocol Stack code
  - 512 KB internal Flash
- Digital peripheral
  - One general-purpose DMA engine with five channels and up to 16 programmable request/trigger sources
- Analog peripherals
  - One 13-bit Sense ADC with a sampling rate of 1 Msps. It supports up to eight external I/O channels and three internal signal channels
  - Built-in die temperature and voltage sensors
  - Low-power comparator, supporting wakeup from sleep mode

- Flexible serial peripherals
  - Two UART modules up to 2 Mbps with flow control and IrDA features
  - Two I2C modules for peripheral communication, up to 1 MHz
  - One 8-bit/16-bit/32-bit SPI master interface and one SPI slave interface for host communication
- Security
  - Complete secure computing engine
    - AES 128-bit security module (ECB, CBC)
    - True random number generator (TRNG)
- I/O peripherals
  - Up to 32 multiplexed I/O pins in total
    - Up to 14 general-purpose I/O (GPIO) pins with configurable pull-up/pull-down resistors
    - Up to eight always-on I/O (AON I/O) pins, supporting wakeup from sleep mode
    - Up to 10 mixed signal I/O (MSIO) pins, configurable to be digital/analog signal interfaces
- Timers
  - Two general-purpose, 32-bit timer modules
  - One dual timer module composed of two programmable 32-bit or 16-bit down counters
  - One sleep timer for waking the device up from sleep mode
  - Two 3-channel PWM modules with edge alignment mode and center alignment mode
  - One real-time counter (RTC)
- Power management
  - On-chip DC-DC/SYS_LDO to provide RF analog voltage and supply CORE_LDO
  - On-chip I/O LDO to provide I/O voltage and supply external components
  - Programmable thresholds for brownout detector (BOD)
  - Supply voltage: 2.0 V – 3.63 V
  - I/O voltage: 1.8 V – 3.6 V
- Low-power consumption
  - Sleep mode: 2.6 µA (Typical) at 3.3 V VBAT input, with 48 KB SRAM retention on, wakeup sources from AON I/Os, and LFXO_32K running
  - Ultra deep sleep mode: 1.9 µA (Typical), with no memory data in retention and wakeup sources from SLP Timer or AON I/Os
  - OFF mode: 200 nA (Typical), with system in reset mode
- Packages
  - QFN32: 4.0 mm * 4.0 mm * 0.75 mm, 0.4 mm pitch
  - QFN48: 6.0 mm * 6.0 mm * 0.75 mm, 0.4 mm pitch
- Operating temperature range
  - GR5331: –40°C ～ 85°C
  - GR5332: –40°C ～ 105°C



## 3. Product Details

|                       |                    | GR5515IGND                                | GR5515I0NDA                               | GR5515IENDU                               | GR5515GGBD                                | GR5515RGBD                                | GR5513BENDU                               |
| --------------------- | ------------------ | ----------------------------------------- | ----------------------------------------- | ----------------------------------------- | ----------------------------------------- | ----------------------------------------- | ----------------------------------------- |
| Status                |                    | Active                                    | Active                                    | Active                                    | Active                                    | Active                                    | Active                                    |
| Protocol              | Bluetooth LE [1]   | 5.1                                       | 5.1                                       | 5.1                                       | 5.1                                       | 5.1                                       | 5.1                                       |
|                       | Bluetooth Mesh     | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
| Core System           | CPU                | Cortex®-M4F                               | Cortex®-M4F                               | Cortex®-M4F                               | Cortex®-M4F                               | Cortex®-M4F                               | Cortex®-M4F                               |
|                       | Clocks             | 64 MHz / 32K Hz                           | 64 MHz / 32   KHz                         | 64 MHz / 32   KHz                         | 64 MHz / 32   KHz                         | 64 MHz / 32   KHz                         | 64 MHz / 32   KHz                         |
|                       | Cache              | 8 KB                                      | 8 KB                                      | 8 KB                                      | 8 KB                                      | 8 KB                                      | 8 KB                                      |
|                       | RAM                | 256 KB                                    | 256 KB                                    | 256 KB                                    | 256 KB                                    | 256 KB                                    | 128 KB                                    |
|                       | OTP                |                                           |                                           |                                           |                                           |                                           |                                           |
|                       | Flash              | 1 MB                                      | External   Flash                          | 512 KB                                    | 1 MB                                      | 1 MB                                      | 512 KB                                    |
| Security              | Root of Trust      | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
|                       | Secure Key Store   | 4                                         | 4                                         | 4                                         | 4                                         | 4                                         | 4                                         |
|                       | PKC                | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
|                       | RSA                | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
|                       | AES                | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
|                       | ECC                | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
|                       | TRNG               | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
| Radio                 | Frequency          | 2.4 GHz                                   | 2.4 GHz                                   | 2.4 GHz                                   | 2.4 GHz                                   | 2.4 GHz                                   | 2.4 GHz                                   |
|                       | Maximum Tx Power   | 7 dBm                                     | 7 dBm                                     | 7 dBm                                     | 7 dBm                                     | 7 dBm                                     | 7 dBm                                     |
|                       | Rx Sensitivity     | -96 dBm(@1Mbps)                           | -96   dBm(@1Mbps)                         | -96   dBm(@1Mbps)                         | -96   dBm(@1Mbps)                         | -96   dBm(@1Mbps)                         | -96   dBm(@1Mbps)                         |
| Peripheral            | UART               | 2                                         | 2                                         | 2                                         | 2                                         | 2                                         | 2                                         |
|                       | SPI                | 1 * SPIM / 1 * SPIS                       | 1 * SPIM / 1   * SPIS                     | 1 * SPIM / 1   * SPIS                     | 1 * SPIM / 1   * SPIS                     | 1 * SPIM / 1   * SPIS                     | 1 * SPIM / 1   * SPIS                     |
|                       | I2C                | 2                                         | 2                                         | 2                                         | 2                                         | 2                                         | 2                                         |
|                       | QSPI               | 2                                         | 2                                         | 2                                         | 0                                         | 2                                         | 1                                         |
|                       | Timers             | 4                                         | 4                                         | 4                                         | 4                                         | 4                                         | 4                                         |
|                       | PWM                | 2                                         | 2                                         | 2                                         | 2                                         | 2                                         | 2                                         |
|                       | RTC                | 1                                         | 1                                         | 1                                         | 1                                         | 1                                         | 1                                         |
|                       | I2S                | 1 * I2SM / 1 * I2SS                       | 1 * I2SM / 1   * I2SS                     | 1 * I2SM / 1   * I2SS                     | 1 * I2SM / 1   * I2SS                     | 1 * I2SM / 1   * I2SS                     | 1 * I2SM / 1   * I2SS                     |
|                       | ADC                | 13-bit                                    | 13-bit                                    | 13-bit                                    | 13-bit                                    | 13-bit                                    | 13-bit                                    |
|                       | Comparator         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
|                       | Temperature Sensor | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         | ●                                         |
|                       | GPIO               | 39                                        | 39                                        | 39                                        | 29                                        | 39                                        | 22                                        |
| Packages              | Type               | QFN56                                     | QFN56                                     | QFN56                                     | BGA55                                     | BGA68                                     | QFN40                                     |
|                       | Dimensions         | 7.0   * 7.0 mm                            | 7.0   * 7.0 mm                            | 7.0   * 7.0 mm                            | 3.5   *3.5 mm                             | 5.3   * 5.3 mm                            | 5.0   * 5.0 mm                            |
| Certification         |                    | PSA Level 1        SIG BQB (QDID: 119449) | PSA Level 1        SIG BQB (QDID: 119449) | PSA Level 1        SIG BQB (QDID: 119449) | PSA Level 1        SIG BQB (QDID: 119449) | PSA Level 1        SIG BQB (QDID: 119449) | PSA Level 1        SIG BQB (QDID: 119449) |
| Operating Temperature |                    | -40℃ - 85℃                                | -40℃ - 85℃                                | -40℃ - 85℃                                | -40℃ - 85℃                                | -40℃ - 85℃                                | -40℃ - 85℃                                |
| Supply Voltage Range  |                    | 2.2 V - 3.8 V                             | 2.2 V - 3.8 V                             | 2.2 V - 3.8 V                             | 2.2 V - 3.8 V                             | 2.2 V - 3.8 V                             | 2.2 V - 3.8 V                             |
| Development Kits      |                    | GR5515 Starter Kit                        | GR5515   Starter Kit                      | GR5515   Starter Kit                      | GR5515   Starter Kit                      | GR5515   Starter Kit                      | GR5515   Starter Kit                      |



## 4. Change Log

- Click to view the [change log](../../wiki)

