#include<util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define BLINK_DELAY_MS 1000


int main(void){
	DDRB=DDRB |0b00111110;  /* configure PORTB bit 4,1,2,3,5 for output*/
	TCNT1 =49911;  // timer to have only 15625 increments for overflow
    TCCR1A=0x00;
    TCCR1B = 0X05;  //SET prescalar to 1:1024
    TIMSK1 = (1<< TOIE1); //enable timer overflow interrupt(TOIE1)
    sei();  //enable global interrupts
	while(1){
       	unsigned char i,j;
      //ABCD pattern
     	for(i=4;i>=1;i--){
         	PORTB = PORTB | (1<<i); //set high corresponding pin in portB
            _delay_ms(BLINK_DELAY_MS);
       	    PORTB = PORTB &~ (1<<i);//set low corresponding pin in portB
            _delay_ms(BLINK_DELAY_MS);
      	} 
      //CB pattern
      	for(j=2;j<4;j++){
          	PORTB = PORTB | (1<<j);//set high corresponding pin in portB
            _delay_ms(BLINK_DELAY_MS);
        	PORTB = PORTB &~ (1<<j); //set low corresponding pin in portB
       	    _delay_ms(BLINK_DELAY_MS);
      	}
  	}
  	return 0;
}

ISR(TIMER1_OVF_vect){ //TIMER1 ISR
	PORTB ^=(1<<5);
	TCNT1 = 49911; //for 1 second at 16MHz

}