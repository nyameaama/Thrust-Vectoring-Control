// Dispatch to proper architecture-specific USB driver

#if STM32F1
#include "arch/stm32f1-usb.h"
#elif STM32F4
#include "arch/stm32f4-usb.h"
#else
#error no USB driver for this architecture
#endif
