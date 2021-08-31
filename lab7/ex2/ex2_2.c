#include<avr/io.h>
 

char recieved_byte;

void usart_init(){

	UCSR0B |= (1<<RXEN0)  | (1<<TXEN0);		// Turn on the transmission and reception circuitry
	
    //UCSR0s are 8-bit control registers used for
    //controlling serial communication in the AVR.
    // UCSR0A,UCSR0B, and UCSR0C are three state registers
  

  //set 8 bit data frame
	UCSR0C |= (1<<UCSZ01);
	UCSR0C |= (1<<UCSZ00);
	UCSR0B &= ~(1<<UCSZ02);
  
    //frequency of oscillator =16Mhz
  	//Desired baud Rate =9600
    //X = (16000000/9600)-1=103

	UBRR0 = 103;
	
}


void usart_send(char c){
  
	//UCSR0B |= (1<<TXEN0);//Transmitter enable
	
	while(!(UCSR0A & (1<<UDRE0))){
      
		// wait until UDRE0 high .then it is empty.leave the loop
     	//empty means all the data is send.So leave the loop
	}
  
    //The character byte to be transmitted serially is written 
    //into the UDR0 register.
  
	UDR0=c; 
	
}
//recieving data
unsigned char usart_receive (void){ 
  
    /* Waiting for data */
    while ( !(UCSR0A & (1<<RXC0)) );
  
    // wait until RXC0 high .then it is empty.leave the loop
    //empty means all the data is send.So leave the loop
  
    /* return received data*/
    return UDR0;
}

char EEPROMread(unsigned int address){

	// wait for completion of previous write
	while (EECR & (1<<EEPE));

	// set up address
	EEAR = address;

	// start eeprom read
	EECR |= (1<<EERE);

	return EEDR;
	
}
void EEPROMwrite(unsigned int address, char data){
	//wait for completion of previous write
	while(EECR &(1<<EEPE));
	
	//set up address and data regs
	EEAR =address;
	EEDR = data;
	
	//write logical 1 to EEMPE
	EECR |= (1<<EEMPE);
	
	//start eeprom write
	EECR |= (1<<EEPE);
}

int main(void){
	
	char c,c2;
	unsigned int i;

	usart_init();  
	
	for (i = 0; i < 1024; i++){

		c = EEPROMread(i);
		usart_send(c);
		
		//c2 = usart_receive();

		//EEPROMwrite(j++, c2);
		
	}

    return 0;   /* never reached */
}