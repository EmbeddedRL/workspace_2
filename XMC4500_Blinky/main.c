/*!
 * \brief Simple XMC Relax Kit demo program.
 * \author M. Horauer
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
  unsigned int i = 100000;
  unsigned int dir = 0; //down=0|up=1

  //PORT1->IOCR0 |= 0x8000; // P1.1 output, push pull
  //PORT1->IOCR0 |= 0x0080; // P1.0 output, push pull
  PORT1->IOCR0 |= 0x8080; // P1.0 & P1.1 output, push pull

  while(1) {
    PORT1->OUT = 0x2; // write 1 to P1.1 -> Port1.1 is low
    wait(i);
    PORT1->OUT = 0x1; // write 0 to P1.1 -> Port 1.1 is high
    wait(i);

    if(dir)
    {
    	i = i + 500;
    }
    else
    {
       	i = i - 500;
    }

    if(i<=0)
    {
    	dir = 1;
    }
    else if(i>=200000)
    {
        dir = 0;
    }
  }
}

void wait(unsigned long delay) {
  while(delay--) {
    __NOP();
  }
}
/*! EOF */
