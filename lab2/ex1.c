#include <avr/io.h>
#include <util/delay.h>


int main(){
	DDRD &= ~(1<<7);  //PD7 (INT0) is input
  	//PB0,PB1,PB2,PB3,PB4,PB5 is output
  	DDRB |=0x3F; 

  	unsigned char count=0;
 	while(1){ //make the loop infinite
		if(PIND &(1<<7)){//check whether push button pressed
  	 		count +=1; //count increment
     		PORTB = count; //display count
  	 		
 		  
     		while(PIND &(1<<7)){ 
     		}
        }
     }
  
  	return 0;
}
