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
#include <stdio.h>
#include "GPIO.h"

/*---------- Defines ----------*/
#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500

#define cb_SIZE 64	//Number of elements in the ringbuffer

/*---------- Globale Variablen ----------*/
char cb[cb_SIZE] = {0};	//Creates Ringbuffer
int inix;	//Element of the Ringbuffer in which the next element will be put
int outix;	//Element of the Ringbuffer that will be read next
int full, empty;	//Indicates a full / empty ringbuffer

static int mode=0; 		//LED-Mode
static int control=1;	//Control-Bit

void SysTick_Handler(void);

void LED_control(void);
void read_Buttons(void);

void cb_init(void);
int cb_put(unsigned char item);
int cb_get(unsigned char *pitem);

void SysTick_Handler(void) {
	LED_control();
	read_Buttons();
}

void LED_control(void)
{
	if(control==0)		//Run-Mode LED driver
	{
		if(mode==0)
		{
			P1_1_reset();
			P1_0_reset();

			P1_1_toggle();	//LED 1 toggles
		}
		else if(mode==1)
		{
			P1_1_reset();
			P1_0_reset();

			P1_0_toggle();	//LED 2 toggles
		}
		else if(mode==2)
		{
			P1_1_reset();
			P1_0_reset();

			P1_1_toggle();	//LED 1 & LED 2 toggle
			P1_0_toggle();
		}
		else if(mode==3)
		{
			P1_1_set();
			P1_0_reset();

			P1_1_toggle();	//LED 1 & LED 2 toggle alternating
			P1_0_toggle();
		}
	}
	else if(control==1)		//Control-Mode LED driver
	{
		if(mode==0)
		{
			P1_1_reset();
			P1_0_reset();	//00b = 0D
		}
		else if(mode==1)
		{
			P1_1_set();
			P1_0_reset();	//01b = 1D
		}
		else if(mode==2)
		{
			P1_1_reset();
			P1_0_set();		//10b = 2D
		}
		else if(mode==3)
		{
			P1_1_set();
			P1_0_set();		//11b = 3D
		}

	}
}

void read_Buttons(void)
{
	static int b1=0,b2=0;

	if((P1_14_read() == 1) && (b1 == 0))
	{
		b1++;
	}
	else if ((P1_14_read() == 1) && (b1 == 1))
	{
		b1++;
	}
	else if ((P1_14_read() == 1) && (b1 == 2))
	{
		if(cb_put('1')!=0)
		{
			b1=0;
		}
	}

	if((P1_15_read() == 1) && (b2 == 0))
		{
			b2++;
		}
		else if ((P1_15_read() == 1) && (b2 == 1))
		{
			b2++;
		}
		else if ((P1_15_read() == 1) && (b2 == 2))
		{
			if(cb_put('2')!=0)
			{
				b2=0;
			}
		}

}

void cb_init(void) {
  inix = 0;
  outix = 0;
  full = 0;
  empty = 1;
}

int cb_put(unsigned char item) {
  if (full)
    return -1;
  inix = (inix + 1) % cb_SIZE;
  cb[inix] = item;
  if (inix == outix)
    full = 1;
  empty = 0;
  return 0;
}

int cb_get(unsigned char *pitem) {
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

	unsigned char rec;
	cb_init();
	P1_14_set_mode(INPUT_INV);	//Button 1 Mode
	P1_15_set_mode(INPUT_INV);	//Button 2 Mode

	P1_1_set_mode(OUTPUT_PP_GP);	//LED 1 Mode
	P1_0_set_mode(OUTPUT_PP_GP);	//LED 2 Mode

	P1_1_reset();
	P1_0_reset();

	/* System timer configuration */
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	while(1) {

		if(empty!=0)
		{
			cb_get(&rec);
			if(rec=='1' && control==1)
			{
				mode++;
				if(mode==4)
				{
					mode=0;
				}
			}
			if(rec=='2' && control=='1')
			{
				control=0;
			}
			else if(rec=='2' && control=='0')
			{
				control=1;
			}

		}
	}
}

/* EOF */
