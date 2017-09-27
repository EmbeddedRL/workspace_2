/*!
 * \brief Simple USIC-UART Example
 * \author Reibenwein Lukas
 * \version 0.1
 */
#include "xmc4500.h"

#define STACK_TOP 0x2000FFFF

//! Function Prototypes
int main(void);
void wait(unsigned long);

//! Vector table
unsigned int *myvectors[2]
__attribute__ ((section("vectors"))) = {
    (unsigned int *) STACK_TOP,
    (unsigned int *) main,
};

//! \brief Main routine that toggles are port with
int main(void)
{
	USIC0_CH0->CCR |= 0x0002;	//Configure USIC as UART/ASC
	USIC0_CH0->FDR |= 0x8052;	//Configure USIC in fractional divider mode to generate 9600 Baudrate

	USIC0_CH0->DX0CR |= 0x0001;	//Configure Input DX0B P1.4 Rx / Output P1.5 Tx
	PORT1->IOCR4 |= 0x0000;		//Configure P1.4 as Input
	PORT1->HWSEL |= 0x0400;		//Enable HW0 for P1.5

	USIC0_CH0->SCTR |= 0x0002;	//Set passive level to 1
	USIC0_CH0->KSCFG |= 0x0003;	//Enable USIC clock
	while(((USIC0_CH0->KSCFG) && 0x01)!=0x01); //Check if clock is enabled

	while(1) 
	{
		wait(1000);
		USIC0_CH0->TBUF[0] = 0x10101010;	//Sends one Bit of Data on the Tx line
	}
}

void wait(unsigned long delay) {
  while(delay--) {
    __NOP();
  }
}
/*! EOF */
