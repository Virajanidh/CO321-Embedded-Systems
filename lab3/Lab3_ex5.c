#include<avr/interrupt.h>

unsigned char count = 0;  //create a global varable to get count

ISR(TIMER0_OVF_vect){
  
	TCNT0 = 131;  //reset the timer counter
	count++;   //increment the count
  
	if(count == 50){ // 50x125 will give the real increment needed
		PORTB ^= (1<<0) ; // toggle the PB0 
		count = 0; // set the count to zero;
	}
  
}


int main(){
  
	DDRB |= (1<<0);  // assign pin PB0 as output 
  
	TCCR0A = 0x00; 
	TCCR0B = 0x04; // set TCCR0B prescaler 1:256
	sei(); // enable gloable interrupts
	TCNT0 = 131; // set the timer to overflow after 125 increaments
  
	TIMSK0 = 0x01; // enable timer overflow interrupts
  
	while(1){  // to run the loop infinitly
  
	}  
	return 0;
}