/*
In this exercise we develop an encryption system using the Caesar cipher.
For this we have to use the LCD, keypad. When the program running it ask from user
 that whether he want to encrypt or change the secret key.
*/


#include <stdlib.h>
#include <avr/io.h>
#include "Keypad.h"
#include "lcd.h"



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


//function to apply Caesar Cipher to a character
char encrypt(char ch , char secretKey){
	
	unsigned char c;
		
  	//if Upper case
  		  
	if (ch < 91 && ch > 64){
		c = (((ch - 'A') + secretKey)%26) + 'A';
	}
  
  	//if Lowercase case
		
	else{ 
		c = (((ch - 'a') + secretKey)%26) + 'a';
	}	
		
	return c;
	
}

int main(void)
{   
	KP_Setup();  //Setup for keypad. 
	lcd_init(LCD_DISP_ON); //initializing the LCD
    lcd_clrscr();  //  clear the display          
    
	
	uint8_t input = 1; //input defines the current state of the circuit
	char key = Key_None; //if nothing pressed.key used to get the input of the keypad
	
	while(1){
		
		/*if input =1 it gives the initial description about the system.
		This is the initial state in the circuit 
		input==A ---> enter the new key
		input==B ---> enter the massege to be encrypted*/
		
		if(input == 1){
			
			lcd_clrscr(); // clear the display  
			lcd_puts("Change key : A\n");
			lcd_gotoxy(0,1);  //set to the next line
			lcd_puts("Encrypt msg : B\n");
			//input=0;
			
		}
		
		key = KP_GetKey(); //get the presssed key
		
		if(key == 'A'){
			
			lcd_clrscr(); // clear the display
			lcd_puts("Enter New Key\n");  //prompt user to enter a new key
    	    lcd_gotoxy(0,1);  //go to next line
			_delay_ms(200); 
			
			while(1){
				key = KP_GetKey(); //getting the new key
				if(key != Key_None){  //waiting to press the key
					lcd_putc(key);
					
					/* the key should be stored in EEPROM
					subtracting by 48 translates the char values '0'..'9' to the int values 0..9 
					to write in EEPROM*/
					EEPROMwrite( 0 , (key-48) ); //saving data to 0 address
					_delay_ms(500);
					
					break;
				}
			}
			
			lcd_clrscr(); //clear the display
    	    lcd_puts("Key Changed\n");
			input = 1;  //back to the initial state
			_delay_ms(500);
		
		}
		else if(key=='B'){
			
			char data_buf[10] = "";  //initialize a buffer  to store data taken from keypad
		    unsigned int j =0;
			
            lcd_clrscr(); //clear the display
		    lcd_puts("Enter your text\n");  // prompt user to enter the text to be encrypted
		    lcd_gotoxy(0,1);  // set to next line
		    _delay_ms(500);  
		   
		    while(1){
			   
			    if( j>9 ){   //only 9 charactors can be added
					break;
				}
				key = KP_GetKey();
				if(key != Key_None){ //wait unitl key is pressed.
				
					lcd_putc(key);  //display the plaintext that entered by user
					data_buf[j]=key; //store  the data
					j++;
					_delay_ms(200);
					
				}
		    } 
		   
		    _delay_ms(200);
		    lcd_clrscr();  //clear the display
		    lcd_puts("Your Cipher Text\n");
		    lcd_gotoxy(0,1); // set to next line
		    _delay_ms(200);
			
		    char secret_key =EEPROMread(0);  //read the secret key
		    unsigned int i=0;
			
			 // encrypt the text charactor by charactor
		    while(i<10){
				
			    lcd_putc(encrypt(data_buf[i],secret_key)); 
			    i++;
			   
		    }
			
		    input=1;  //set to initial state
		    _delay_ms(2000);
			
		}
	}
	
	return 0;
	
}