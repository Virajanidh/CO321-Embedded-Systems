#include <avr/io.h>
#include <util/delay.h>

void usart_init(){
  
  //UCSR0s are 8-bit control registers used for
  //controlling serial communication in the AVR.
  // UCSR0A,UCSR0B, and UCSR0C are three state registers
  
  //Select asynchronous mode. 
  //We will use 8-bit data frame, no parity, and one stop bit.
  
	UCSR0C &= ~(1<<UMSEL01 | 1<<UMSEL00);//asunchronous
	UCSR0C &= ~(1<<UPM01 | 1<<UPM00);//No parity
	UCSR0C &= ~(1<<USBS0);//1 stop bit

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
  
	UCSR0B |= (1<<TXEN0);//Transmitter enable
	
	while(!(UCSR0A & (1<<UDRE0))){
      
		// wait until UDRE0 high .then it is empty.leave the loop
     	//empty means all the data is send.So leave the loop
	}
  
  //The character byte to be transmitted serially is written 
  //into the UDR0 register.
  
	UDR0=c; 
	
}



void sendLine(char array[]){
  
	unsigned char i=0;

  //send bit wise until passed string ends
	while((array[i]))
    {
		usart_send(array[i]); 
		i++;
	}
	usart_send('\0');
  
}

int main(){
	usart_init();
  
   //For the serial data communication to work, 
  //the byte of data must be converted to serial bits 
  //using a parallel-in-serial-out shift register.
  //then it can be transmitted over a single data line
  
	sendLine("Virajani E/16/086");
	sendLine("Chanika E/16/156");
	sendLine("Tharushini E/16/223");


	return 0;
}
