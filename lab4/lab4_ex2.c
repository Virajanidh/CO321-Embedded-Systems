#include<avr/io.h>
#include<util/delay.h>

int main(void){
	DDRD |=(1<<6);  //configer portD pin6 to get output of 5V
	PORTD &= ~(1<<6); //initially set portD pin 6 to low
    
  	int value = 5;
    int bright =0;
    
    while(1){
  		fade(bright);
      	bright += value;
     	if(bright==0 || bright==255){
      		value = ~value;
     	 }
     	 _delay_ms(150);
  
    }
	
	
  
}
void fade(int brightness){

    OCR0A = brightness; //AS duty cycle is 50%
	TCNT0 = 0;  //initial counter value should be 0
  
	//TCCR0A |= (1<<WGM00) | (1<<WGM01)|(1<<COM0A1)
  //set fast PWM mode with non-inverted output
	//TCCR0A = 0X83;
    TCCR0A |= (1<<WGM01)|(1<<WGM00);
	TCCR0B |= (1<<WGM02); 
	TCCR0A |= (1<<COM0A1)|(1<<COM0A0); //non inverting mode
    
   //set prescalar to 64 to get 976.56Hz frequency
 	TCCR0B |= (1<<CS00) |(1<<CS01);
	//TCCR0B = 0X0B;
	
	while(1){}  //to run continuously

}