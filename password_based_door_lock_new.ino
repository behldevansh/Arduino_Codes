

#include <Keypad.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

#define Solenoid 3 
#define Solenoid1 4           
#define O_Button 5             
#define buzzer 6 

#define En_pin 13

#define Rs_pin 12
#define D4_pin 11
#define D5_pin 10
#define D6_pin 9
#define D7_pin 8

const byte numRows= 4;          
const byte numCols= 4;          

char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

char keypressed;                 
char code[]= {'0','0','0','0'};  

char code_buff1[sizeof(code)];  
char code_buff2[sizeof(code)];  

short a=0,i=0,s=0,j=0;          

byte rowPins[numRows] = {A3,A4,A5,7}; 
byte colPins[numCols]= {A0,A1,A2,2}; 

LiquidCrystal lcd(13,12,11,10,9,8);
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
         {
          lcd.begin (16,2);
          
          Serial.begin(9600);
          
            lcd.print("  Home Security  "); 
            lcd.setCursor(0,1); 
            lcd.print("  System  ");       
          
          pinMode(Solenoid,OUTPUT);
          pinMode(Solenoid1,OUTPUT);
            pinMode(buzzer,OUTPUT);
          pinMode(O_Button,INPUT_PULLUP);
                      
            

         }


void loop()
{
  digitalWrite(Solenoid,HIGH);
       digitalWrite(Solenoid1,HIGH);
Serial.print(keypressed);
delay(100);
  keypressed = myKeypad.getKey();              
    if(keypressed == '*'){                      
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Enter code");            
            GetCode();                          
                  if(a==sizeof(code))           
                  OpenDoor();                  
                  else
                  {
                  lcd.clear();               
                  lcd.print("");          
                  }
            delay(2000);
            lcd.clear();
            lcd.print("  Digital Code  "); 
            lcd.setCursor(0,1); 
            lcd.print("  Lock System  "); 
            digitalWrite(Solenoid,HIGH);
       digitalWrite(Solenoid1,HIGH);          
        }

     if(keypressed == '#'){                  
      ChangeCode();
      lcd.clear();
       lcd.print("  Digital Code  "); 
            lcd.setCursor(0,1); 
            lcd.print("  Lock System  ");                 
     }

     if(digitalRead(O_Button)==LOW)
     {      
       digitalWrite(buzzer,HIGH);
       
      }
      else
      {
   digitalWrite(buzzer,LOW);      
 }
}

void GetCode(){                  
       i=0;                      
       a=0;
       j=0; 
                                     
     while(keypressed != 'A'){                                     
           keypressed = myKeypad.getKey();                         
             if(keypressed != NO_KEY && keypressed != 'A' ){       
              lcd.setCursor(j,1);                                  
              lcd.print("*");
              j++;
            if(keypressed == code[i]&& i<sizeof(code)){            
                 a++;                                              
                 }
            else
                a--;                                               
            }
            }
    keypressed = NO_KEY;

}

void ChangeCode(){                      //Change code sequence
      lcd.clear();
      lcd.print("Changing code");
      delay(1000);
      lcd.clear();
      lcd.print("Enter old code");
      GetCode();                      //verify the old code first so you can change it
      
            if(a==sizeof(code)){      //again verifying the a value
            lcd.clear();
            lcd.print("Changing code");
            GetNewCode1();            
            GetNewCode2();            
            s=0;
              for(i=0 ; i<sizeof(code) ; i++){     
              if(code_buff1[i]==code_buff2[i])
              s++;                                
              }
                  if(s==sizeof(code)){            
                  
                   for(i=0 ; i<sizeof(code) ; i++){
                  code[i]=code_buff2[i];         
                  EEPROM.put(i, code[i]);        
                  
                  }
                  lcd.clear();
                  lcd.print("Code Changed");
                  delay(2000);
                  }
                  else{                         
                  lcd.clear();
                  lcd.print("Codes are not");
                  lcd.setCursor(0,1);
                  lcd.print("matching !!");
                  delay(2000);
                  }
            
          }
          
          else{                     
          lcd.clear();
          lcd.print("Password Wrong");
          delay(2000);
          }
}

void GetNewCode1(){                      
  i=0;
  j=0;
  lcd.clear();
  lcd.print("Enter new code");   
  lcd.setCursor(0,1);
  lcd.print("and press A");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("and press A");     
             
         while(keypressed != 'A'){            
             keypressed = myKeypad.getKey();
               if(keypressed != NO_KEY && keypressed != 'A' ){
                lcd.setCursor(j,0);
                lcd.print("*");               
                code_buff1[i]=keypressed;    
                i++;
                j++;                    
                }
                }
keypressed = NO_KEY;
}

void GetNewCode2(){                         
  i=0;
  j=0;
  
  lcd.clear();
  lcd.print("Confirm code");
  lcd.setCursor(0,1);
  lcd.print("and press A");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("and press A");

         while(keypressed != 'A'){
             keypressed = myKeypad.getKey();
               if(keypressed != NO_KEY && keypressed != 'A' ){
                lcd.setCursor(j,0);
                lcd.print("*");
                code_buff2[i]=keypressed;
                i++;
                j++;                    
                }
                }
keypressed = NO_KEY;
}

void OpenDoor(){             
  lcd.clear();
  lcd.print("   Welcome  "); 
  delay(1000);
   
            lcd.setCursor(0,1); 
            lcd.print(" Door Are Open "); 
           delay(500);       
       digitalWrite(Solenoid,HIGH);
       digitalWrite(Solenoid1,LOW);
       delay(500);                        
       digitalWrite(Solenoid,HIGH);
       digitalWrite(Solenoid1,HIGH);
       delay(1000);
       lcd.clear();
  lcd.print("   Welcome  "); 
  delay(1000);
   
            lcd.setCursor(0,1); 
            lcd.print(" Door Are Closed ");
            delay(500);
       digitalWrite(Solenoid,LOW);
       digitalWrite(Solenoid1,HIGH);
       delay(500);
       digitalWrite(Solenoid,HIGH);
       digitalWrite(Solenoid1,HIGH);
       delay(1000);  
}
