/**
   @mainpage XMC Barebone Template

   @section Usage

   This project is intended to be used along with Eclipse or from the CMD-Line
   using a Makefile. The latter provides the following commands:

   @verbatim
   make                        # build the project
   make debug                  # build the project and start the debugger
   make flash                  # flash the application
   make doc                    # generate the documentation
   make clean                  # delete intermediate files
   @endverbatim

   @section Folders

   The code is organized in various folders - checkout the comments below:

   @verbatim
   Makefile          # top level Makefile used for the command-line variant
   doxygen           # doxygen configuration file
   inc/              # the place for your header files
   src/              # the place for your source files
   bin/              # output folder - here you will find listings and binaries
   Debug/            # this fiolder is only used by Eclipse
   doc/              # here the generated documentation is found
   system/           # CMSIS library, Infineon header files, linker script, etc.
   xmclib/           # low-level XMC library
   @endverbatim

   @file main.c
   @date 08 Sep, 2015
   @version 1.0.0

   @brief XMC4500 Relax kit GPIO toggle example

   GPIO toggle example flashes the leds of the board with a periodic rate.
   LED1 is connected to P1.1
   LED2 is connected to P1.0

   History <br>

   Version 1.0.0 Initial <br>
 */

#include <debug_lib.h>
#include <stdio.h>
#include <xmc_gpio.h>
#include "test_uart.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define LED1 P1_1
#define LED2 P1_0

#define RX_BUFFER_SIZE 64

void SysTick_Handler(void) {
	static uint32_t ticks = 0;
	static int32_t cnt = 0;

	ticks++;
	if (ticks == TICKS_WAIT) {
		XMC_GPIO_ToggleOutput(LED1);
		XMC_GPIO_ToggleOutput(LED2);
		printf("Testing... %d\n", (int)cnt++);

		ticks = 0;
	}
}


int main(void) {
	XMC_GPIO_CONFIG_t config;
	char rx_buff[RX_BUFFER_SIZE] = {0};

	initRetargetSwo();

	config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
	config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

	XMC_GPIO_Init(LED1, &config);

	config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
	XMC_GPIO_Init(LED2, &config);

	_initUART0_CH0();

	/* System timer configuration */
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	/* Available UART functions */
	_uart_send_char('X');
	_uart_send_string("Testing...\n");
	_uart_printf("Magic Number = %d\n",42);

	_uart_get_string (rx_buff);
	_uart_printf("RX string = %s\n", rx_buff);

	while(1) {
	}
}

/* EOF */
