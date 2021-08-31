#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int main(){
  
	DDRD = 0xFF; /* configure PORTD for output*/
    DDRB |=(1<<0)|(1<<1);
  
    // Use ADC1 pin of the microcontroller for the input
    DDRC = DDRC &~(1<<1) ; 
    
    //Turn on the ADC module of the AVR
    ADCSRA = ADCSRA|(1<<ADEN); 
  
    // Select the conversion speed.prescalar is 128.
    //As  f(osc) is 16MHz and 
    //ADC requires an input clock frequency less than 200 kHz
    ADCSRA |=(1 << ADPS0);
    ADCSRA |=(1 << ADPS1);
    ADCSRA |=(1 << ADPS2);

    //ADCSRA = 0x87;	
    //Select input channel ADC1 
    ADMUX |= (1<< MUX0) ;
  
    // Select voltage reference as AVCC
    ADMUX |= (1<<REFS0);
    ADMUX |= (0<<REFS1);
  
    //the result will be left-justified
    ADMUX |= (1<<ADLAR);
  
    unsigned char low, high =0,bulbs=0;
    while(1){
      
		// Activate the start conversion bit
		ADCSRA |=(1<<ADSC);
   
		/* Wait for the conversion to be completed 
		by polling the ADIF bit in the ADCSRA register*/
		while(!(ADCSRA&(1<<ADIF)));
      
		//clear the ADIF bit
		ADCSRA |=(1<<ADIF);
      
		//get the output to the variable reading in ADCH
		
         //divide to 8 voltage levels
        //get the level according to the voltage
        bulbs = round((ADCH/255.0)*8); 
        if(bulbs>0){
        	PORTD = pow(2,bulbs);
        }
        _delay_ms(100);
  
     
    } 
     
    return 0;

}

//stepsize = 5v/(2^10) =0.0048828125
//Vin=3.3v -> Vout = 3.3/0.0048828125 = 675.84 ->675
//Vin=5v   -> Vout = 5/0.0048828125   = 1024
//Vin=GND  -> Vout = 0