#include <avr/io.h>
#include <util/delay.h>

void usart_init(){
	UCSR0C &= ~(1<<UMSEL01 | 1<<UMSEL00);//asunchronous
	UCSR0C &= ~(1<<UPM01 | 1<<UPM00);//No parity
	UCSR0C &= ~(1<<USBS0);//1 stop bit

	UCSR0C |= (1<<UCSZ01);//8 bit
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
	UDR0=c;  //data register
	
}


char usart_receive(){
	char c;
	//Enable the USART receive
	UCSR0B |= (1<<RXEN0);
	while(!(UCSR0A& (1<<RXC0))){
		//wait until UDRE0 high .then it is empty.
		//The RXC0 flag bit of the UCSR0A register is monitored
		//for a HIGH to see if and entire character has been received yet
		//leave the loop
	}
	//UDR0 register recieve data
	c=UDR0;
	
	return c;
}

int main(){
	


	return 0;
}