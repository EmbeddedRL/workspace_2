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
   src/              # the place for your source files
   bin/              # output folder - here you will find listings and binaries
   Debug/            # this fiolder is only used by Eclipse
   doc/              # here the generated documentation is found
   system/           # CMSIS library, Infineon header files, linker script, etc.
   @endverbatim

   @file main.c
   @date 04.10.2017
   @version 1.0.0

   @brief XMC4500 Relax kit IO Task
   @creator Lukas Reibenwein

   History <br>

   Version 1.0.0 Initial <br>
 */


/*---------- Includes ----------*/
#include <stdio.h>
#include <XMC4500.h>

/*---------- Defines ----------*/
#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 200

#define cb_SIZE 64	//Number of elements in the ringbuffer

/*---------- Globale Variablen ----------*/
char cb[cb_SIZE] = {0};		//Creates Ringbuffer
int inix;					//Element of the Ringbuffer in which the next element will be put
int outix;					//Element of the Ringbuffer that will be read next
int full, empty;			//Indicates a full / empty ringbuffer

int mode=0; 				//LED-Mode
int control=1;				//Control-Bit
int update_LED=0;			//Gets set to one when the LED-mode gets changed


/*---------- Prototypes ----------*/
void SysTick_Handler(void);

void LED_control(void);
void read_Buttons(void);

void cb_init(void);
int cb_put(unsigned char item);
int cb_get(unsigned char *pitem);

void init_Ports(void);

/*---------- Code ----------*/

void SysTick_Handler(void)
{

	static int ticks=0;

	read_Buttons();		//Reads Button Status
	ticks++;

	if(ticks==TICKS_WAIT)
	{
		if(update_LED)	//If the Mode was changed the LEDs are set/reset according to the mode selected
		{
			PORT1->OMR |= 0x00030000;		//Resets LED1 & LED2 before Run mode
			if(mode==3)
			{
				PORT1->OMR |= 0x00000001;	//Sets LED1 for Alternating Toggle mode
			}
			update_LED=0;
		}
		LED_control();	//Controls the LEDs
		ticks=0;
	}

}

void LED_control(void)
{
	if(control==0)		//Run-Mode LED driver
	{
		if(mode==0)
		{
			PORT1->OMR |= 0x00010001;	//Toggle LED1
		}
		else if(mode==1)
		{
			PORT1->OMR |= 0x00020002;	//Toggle LED2
		}
		else if(mode==2)
		{
			PORT1->OMR |= 0x00030003;	//Toggle LED1 & LED2
		}
		else if(mode==3)
		{
			PORT1->OMR |= 0x00030003;	//Toggle LED1 & LED2
		}
	}
	else if(control==1)		//Control-Mode LED driver
	{
		if(mode==0)
		{
			PORT1->OMR |= 0x00030000;	//Reset LED1 & LED2
		}
		else if(mode==1)
		{
			PORT1->OMR |= 0x00010002;	//Set LED2 & Reset LED1
		}
		else if(mode==2)
		{
			PORT1->OMR |= 0x00020001;	//Set LED1 & Reset LED2
		}
		else if(mode==3)
		{
			PORT1->OMR |= 0x00000003;	//Set LED1 & LED2
		}

	}
}

void read_Buttons(void)
{
	static int b1=0,b2=0;

	//Checks 3 times if the button is still pressed, button is disabled during run-mode
	if(((PORT1->IN & 0x00004000) == 0) && (b1 == 0) && (control == 1))
	{
		b1++;
	}
	else if (((PORT1->IN & 0x00004000) == 0) && (b1 == 1) && (control == 1))
	{
		b1++;
	}
	else if (((PORT1->IN & 0x00004000) == 0) && (b1 == 2) && (control == 1))
	{
		if(cb_put('0')==0)	//Sends data to ringbuffer and waits for button to be released
		{
			b1=0;
			update_LED=1;
			while((PORT1->IN & 0x00004000) == 0);
		}

	}

	//Checks 3 times if the button is still pressed
	if(((PORT1->IN & 0x00008000) == 0) && (b2 == 0))
		{
			b2++;
		}
		else if (((PORT1->IN & 0x00008000) == 0) && (b2 == 1))
		{
			b2++;
		}
		else if (((PORT1->IN & 0x00008000) == 0) && (b2 == 2))
		{
			if(cb_put('1')==0)	//Sends data to ringbuffer and waits for button to be released
			{
				b2=0;
				update_LED=1;
				while((PORT1->IN & 0x00008000) == 0);
			}
		}

}

void cb_init(void)
{
	inix = 0;
	outix = 0;
	full = 0;
	empty = 1;
}

int cb_put(unsigned char item)
{
	if (full)						//Returns -1 if the buffer is full
		return -1;

	inix = (inix + 1) % cb_SIZE;	//Writes new element into the buffer
	cb[inix] = item;

	if (inix == outix)				//Checks if the buffer is full after adding the element
		full = 1;

	empty = 0;
	return 0;
}

int cb_get(unsigned char *pitem)
{
	if (empty)						//Returns -1 if the buffer is empty
		return -1;

	outix = (outix + 1) % cb_SIZE;	//Reads one element from the buffer
	*pitem = cb[outix];

	if (outix == inix)				//Checks if the buffer is empty after reading the element
		empty = 1;

	full = 0;
	return 0;
}

void init_Ports(void)
{
	PORT1->IOCR12 = 0x00000000;	//Initialize Button1 & Button2
	PORT1->IOCR0 |= 0x8080;		//Initialize LED1 & LED2

	PORT1->OMR |= 0x00000003;	//LED1 & LED2 set
	PORT1->OMR |= 0x00030000;	//LED1 & LED2 reset
	PORT1->OMR |= 0x00030003;	//LED1 & LED2 toggle
	PORT1->OMR |= 0x00030003;	//LED1 & LED2 toggle
}

int main(void) {

	unsigned char rec;

	cb_init();
	init_Ports();

	/* System timer configuration */
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	while(1) {

		if(empty!=1)
		{
			cb_get(&rec);	//Read data when it is available

			if(rec=='0' && control==1)
			{
				//Switch trough modes
				mode++;
				if(mode==4)
				{
					mode=0;
				}
			}
			else if(rec=='1' && control==1)
			{
				//Switch between control- / run-mode
				control=0;
			}
			else if(rec=='1' && control==0)
			{
				//Switch between control- / run-mode
				control=1;
			}

		}
	}
}

/* EOF */
