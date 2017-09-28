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

/*---------- Includes ----------*/
#include <debug_lib.h>
#include <stdio.h>
#include <xmc_gpio.h>

/*---------- Defines ----------*/
#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define cb_SIZE 64	//Number of elements in the ringbuffer

/*---------- Globale Variablen ----------*/
char cb[cb_SIZE] = {0};	//Creates Ringbuffer
int inix;	//Element of the Ringbuffer in which the next element will be put
int outix;	//Element of the Ringbuffer that will be read next
int full, empty;	//Indicates a full / empty ringbuffer

/*---------- Systick_INT Handler ----------*/
void SysTick_Handler(void) {
	static uint32_t ticks = 0;
	static int32_t cnt = 0;

	ticks++;
	if (ticks == TICKS_WAIT) {

	}
}

/*---------- Ringbuffer functions ----------*/
void cb_init (void) {
  inix = 0;		//Input-Pointer
  outix = 0;	//Output-Pointer
  full = 0;		//Indicates that the ringbuffer is full
  empty = 1;	//Indicates that the ringbuffer is empty
}

int cb_put (unsigned char item) {
  if (full)
    return -1;
  inix = (inix + 1) % cb_SIZE;
  cb[inix] = item;
  if (inix == outix)
    full = 1;
  empty = 0;
  return 0;
}

int cb_get (unsigned char *pitem) {
  if (empty)
    return -1;
  outix = (outix + 1) % cb_SIZE;
  *pitem = cb[outix];
  if (outix == inix)
    empty = 1;
  full = 0;
  return 0;
}

int main(void) {
	initRetargetSwo();

	PORT1->IOCR0 |= 0x8080; // P1.0 & P1.1 output, push pull
	PORT1->OUT = 0x3;
	wait(300);
	PORT1->OUT = 0x0;
	wait(300);

	cb_init();


	/* System timer configuration */
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);


	while(1) {
	}
}


void wait(unsigned long delay) {
  while(delay--) {
    __NOP();
  }
}

/* EOF */
