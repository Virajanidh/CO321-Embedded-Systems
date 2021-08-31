#include <avr/io.h>

int main(){
  
	DDRD |=(1<<7); /* configure PORTD pin7 for output*/
  
    // Use ADC1 pin of the microcontroller for the input
    DDRC = DDRC &~(1<<1) ; 
    
    //Turn on the ADC module of the AVR
    ADCSRA = ADCSRA |(1<<ADEN); 
  
    // Select the conversion speed.prescalar is 128.
    //As  f(osc) is 16MHz and 
    //ADC requires an input clock frequency less than 200 kHz
    ADCSRA |=(1 << ADPS0);
    ADCSRA |=(1 << ADPS1);
    ADCSRA |=(1 << ADPS2);

    //ADCSRA = 0x87;	
    //Select input channel ADC1 
    ADMUX |= (1<< MUX0) ;
  
    // Select voltage reference as AREF
    ADMUX |= (0<<REFS0);
    ADMUX |= (0<<REFS1);
  
    //the result will be left-justified
    ADMUX |= (1<<ADLAR);
  
    unsigned char low, high =0;
    while(1){
      
		// Activate the start conversion bit
		ADCSRA |=(1<<ADSC);
   
		/* Wait for the conversion to be completed 
		by polling the ADIF bit in the ADCSRA register*/
		while(!(ADCSRA&(1<<ADIF)));
      
		//clear the ADIF bit by writing 1 to it.
		ADCSRA |=(1<<ADIF);
      
		//get the output to the variable reading in ADCL
		// most signnificat 8 bits of the result at ADCH
		high = ADCH;
		high = high>>7;
      
	    //turn on the LEDS
        //In ldr when light intensity is increase resistance decrease
		if(high>=1){
			PORTD |=(1<<7);
		}else{
			PORTD = PORTD &~(1<<7);
		}
    } 
}

//stepsize = 5v/(2^10) =0.0048828125

