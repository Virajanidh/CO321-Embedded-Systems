#include<avr/io.h>
#include<util/delay.h>

int main(void){
	DDRD |=(1<<6);  //configer portD pin6 to get output of 5V
	PORTD &= ~(1<<6); //initially set portD pin 6 to low

    
    while(1){
		int freq[4]={64,127,191,255};  //equaly divide the  interval for 255 
		int i =0 ;
		while(i<4){
			fade(freq[i]);
			_delay_ms(1000);
          i++;
		}
  
    }
	
	
  
}
void fade(int frequency){

    OCR0A = frequency; //AS duty cycle is 50%
	TCNT0 = 0;  //initial counter value should be 0
    
   //set prescalar to 64 to get 976.56Hz frequency
   TCCR0B |= (1<<CS00) |(1<<CS01);
	//TCCR0A |= (1<<WGM00) | (1<<WGM01)|(1<<COM0A1)
   //set fast PWM mode with non-inverted output
	TCCR0A = 0X83;


	
	//while(1){}  //to run continuously

}