
// changed lcd pin
// declared the global variable for a9 and a8
#include<EEPROM.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(45,46,47,21,20,19,18);  // 38,39,40,41     //   (38,35,47,48,49,50)               //  (29,28,26,27,38,39,40,41);                         

// Move Motor pin configurations
int Move_motor_Enable_A1 = 5;
int Move_motor_Enable_B1 = 11;
int Move_motor_Enable_C1 = 12;
int Move_motor_Enable_D1 = 13;

// slide motor pin config
int Move_motor_Enable_A2 = 14;
int Move_motor_Enable_B2 = 19;
int Move_motor_Enable_C2 = 20;
int Move_motor_Enable_D2 = 21;

//
//int sensorpin1= A9;
//int sensorpin2=A8;

// pump and solinoid pin config 
int EN_VACCUM = 3;
int EN_SOLE1 = 22 ;

// TOuch Sensor LED pin config
int LED_1 = 52;
int LED_2 = 53;
int LED_3 = 54;
int LED_4 = 55;
int LED_5 = 56;

// Buzzer 
int Buzzer = 30; 
int inByte; // Stores incoming command

int page_counter=0 ;       //To move beetwen pages
bool Buttonstate = HIGH;
int count1=0;   // Left and right button counter
int count=0;   
int t;
int val=0;

//-------mode selsction and reset button Pins-----//
int up = 47;                // mode selection...............................sw4
int down = 46;              //   go to back page.............................sw3


// ---- CURSOR up & down  PINS ---//
int switchUpPin = 49;                /// cursor down.............................sw6
int switchDownPin = 51;              ///  cursor up..............................sw8
int counter =0;                      // up & down button counter
int buttonUpState = 0;
int lastButtonUpState = 0;
int buttonDownState = 0;
int lastButtonDownState = 0;
int lasttouchvalue=0;  //
int touchvalue=0;  //



// manula mode button config
const int  Up_buttonPin   = 49;    // Manual Mode value up and down pins
const int  Down_buttonPin = 51;
const int  left_buttonPin   = 50;    // Manual Mode left and right pin 
const int  right_buttonPin = 48;

// Variables for manual modes

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonPushCounter1 = 0;   // counter for the number of button presses
int up_buttonState = 0;         // current state of the up button

int up_lastButtonState = 0;     // previous state of the up button

int counter1 =0;              // Manual mode left and right button counter
int counter2 =0;             // manual mode Transhold button counter
int leftbuttonState = 0;
int lastButtonUp = 0;
int rightbuttonState = 0;
int lastButtonDown = 0;

int l=0;
int down_buttonState = 0;         // current state of the up button
int down_lastButtonState = 0;     // previous state of the up button
bool bPress = false;


// for page change.................
int UpState= 0;
int lastUpState = 0;
int DownState = 0;

// Touch buton config
const int start_button = 44;    // Start button pin......................sw1 
const int stop_button = 45;     // stop button pin ......................sw2

bool Start_Buttonstate_1 = LOW;
bool Stop_Buttonstate_1 = LOW;
String digit = " ";
char input[50];
int i = 0;
int b=0;

long a=1000;
long c=0;
int m=0;

unsigned long time_delay = 0;
bool lastButton_start_pause_State = 0;
bool Button_start_pause_State = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.write(0,0);
  EEPROM.write(1,0);

// functions
  void stop_pausebutton_status(void);
  
  pinMode( Move_motor_Enable_A1, OUTPUT);
  pinMode( Move_motor_Enable_B1, OUTPUT);
  pinMode( Move_motor_Enable_C1, OUTPUT);
  pinMode( Move_motor_Enable_D1, OUTPUT);

  pinMode( Move_motor_Enable_A2, OUTPUT);
  pinMode( Move_motor_Enable_B2, OUTPUT);
  pinMode( Move_motor_Enable_C2, OUTPUT);
  pinMode( Move_motor_Enable_D2, OUTPUT);
  
  pinMode( EN_VACCUM, OUTPUT);
  pinMode( EN_SOLE1, OUTPUT);
  pinMode( LED_1, OUTPUT);
  pinMode( LED_2, OUTPUT);
  pinMode( LED_3, OUTPUT);
  pinMode( LED_4, OUTPUT);
  pinMode( LED_5, OUTPUT);


  pinMode( Buzzer, OUTPUT);
  pinMode( start_button, INPUT);
  pinMode( stop_button, INPUT);

// Value Increment and Diecresing buttons 
   pinMode( Up_buttonPin , INPUT_PULLUP);
   pinMode( Down_buttonPin , INPUT_PULLUP);
   pinMode(  left_buttonPin  , INPUT_PULLUP);
   pinMode(  right_buttonPin  , INPUT_PULLUP);
  
      lcd.begin(40,4);
  // Print a message to the LCD.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("          ---   WELCOME   ---       "); 
    delay(500);
    lcd.clear();
    lcd.setCursor(0,1);
     lcd.print("         -- INITIAL SETUP--   ");
     delay(5000);
slide_out();
bottom_top();
buzzer();
//MODE SELECTION PART:
    
     lcd.clear(); 
     lcd.setCursor(0,0);
     lcd.noCursor();
     delay(500);// Turn on the cursor:
     lcd.cursor();
     delay(500);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 1. Gynecologic sample preparation");
     lcd.setCursor(0,1);
     lcd.print(" 2. Fine Needle Aspirates");
     lcd.setCursor(0,2);
     lcd.print(" 3. Muciod specimens");
     lcd.setCursor(0,3);
     lcd.print(" 4. Body Fluid ");
     lcd.setCursor(0,0);
     lcd.noCursor();
    
    delay(500);// Turn on the cursor:
    lcd.cursor();
    delay(500);


  
}


   //---- De-bouncing function for all buttons----//
boolean debounce(boolean last, int pin)
{
boolean current = digitalRead(pin);
if (last != current)
{
delay(5);
current = digitalRead(pin);
}
return current;
}

void loop() {
   
  
label:

// Function for Manual Mode Value Changes
  
   checkUp();    // Value Increase Function

   checkDown();  // Value Decrease Function

if(l == 1){

     checkUp();

   checkDown();

   if( bPress)
   {
       bPress = false;
       lcd.setCursor(3,2);
      lcd.print(buttonPushCounter);
      int val = buttonPushCounter;
      Serial.println(val);
         buzzer(); 
   }

}
if(l == 2){

     checkUp();   // Value Increase Function
     checkDown();  // Value Decrease Function


   if( bPress)
   {
       bPress = false;
      lcd.setCursor(9,2);
      lcd.print(buttonPushCounter);
      buzzer();
   }

}
if(l == 3){
   
     checkUp();   // Value Increase Function
     checkDown();  // Value Decrease Function

   if( bPress)
   {
       bPress = false;
      lcd.setCursor(16,2);
      lcd.print(buttonPushCounter);
      buzzer();
   }

}
if(l == 4){
   
     checkUp();   // Value Increase Function
     checkDown();  // Value Decrease Function

   if( bPress)
   {
       bPress = false;
      lcd.setCursor(23,2);
      lcd.print(counter2);
      int val_1 = counter2;
      Serial.println(val_1);
      buzzer();
   }

}
if(l == 5){
  
     checkUp();   // Value Increase Function
     checkDown();  // Value Decrease Function

   if( bPress)
   {
       bPress = false;
      lcd.setCursor(34,2);
      lcd.print(buttonPushCounter);
      buzzer();
   }

}

// Manual Mode cursor Left & Right Movement

  leftbuttonState = digitalRead(left_buttonPin);  //to increment .......   Manual Mode Cursor Left movement
  rightbuttonState = digitalRead(right_buttonPin); //to decrement.......   Manual Mode Cursor Right Movement

  if (leftbuttonState != lastButtonUp) 
  {
      if (leftbuttonState == HIGH && m==7) 
        {
    
            //Reset the counter to -1
            if(counter1 ==4) // 2
              {       
                goto label;
              }
        //Increase the counter by 1
     
                counter1++;
      //Print the counter to the console and calling the function
                Serial.println(counter1);
      
      //Delaying by 250 ms
                 delay(50);
  if(counter1>=4 && counter1<7)
      {
         Serial.println("left");
          changeNumber1(counter1);
      }
         changeNumber1(counter1);   
     }
   
   delay(50);
   
   while(digitalRead(left_buttonPin)==HIGH);
  }

   //Do this for the button down
  if (rightbuttonState != lastButtonDown) 
  {
    if (rightbuttonState == HIGH && m==7 ) 
    {
     
      if(counter1 == 0)
      {
       goto label;
       
       // counter =-1;
        delay(50);
      }
      //Decreases the counter by 1
      counter1--;
      ////Print the counter to the console and calling the function
      Serial.println(counter1);
      
      if(counter1>3)
         changeNumber1(counter1);
      //Delaying by 250 ms
      delay(50);
    }
     if(counter1<=3 && counter1>0)
      {
        
        
       //   pagechange(8);
          changeNumber1(counter1);
      }
    //Delay to avoid button bouncing
   delay(50);
    changeNumber1(counter1); 

   }
    
 // Cursor Up and Down Function 

   buttonUpState = digitalRead(switchUpPin);  //Cursor increment .......
  buttonDownState = digitalRead(switchDownPin); //Cursor decrement....
  UpState = digitalRead(up);    //for mode button
  DownState = digitalRead(down);  //for reset butto  //Detecting button press and getting the button status
 
   //....end of touch senor
  if( UpState==HIGH)
      {
       
           pagechange(counter);
           count=0;
          
      }
      while(digitalRead(up)==HIGH);
  if(counter<4) //4
      {
         if( DownState==HIGH)
         {
           pagechange(8);
           lcd.setCursor(0,counter);
           lcd.noCursor();
           delay(500);
      //Turn on the cursor:
           lcd.cursor();
           delay(500);
        }
          while(digitalRead(down)==HIGH);
      }
  if(counter>=4 && counter<7)
      {
        
         if( DownState==HIGH)
            {
              pagechange(7);
              counter=0;
       
   // Manual Mode Reset Function
            buzzer(); 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" 1. Gynecologic sample preparation");
            lcd.setCursor(0,1);
            lcd.print(" 2. Fine Needle Aspirates");
            lcd.setCursor(0,2);
            lcd.print(" 3. Muciod specimens");
            lcd.setCursor(0,3);
            lcd.print(" 4. Body Fluid ");
            lcd.setCursor(0,0);
            lcd.noCursor();
            counter2=0;
            buttonPushCounter=0;
            delay(500);
            lcd.cursor();
            delay(500);
            m=0;
                  
        goto label;
          
        }
         while(digitalRead(down)==HIGH);
      } 

   // UP AND DOWN BUTTON FUNCTION    
   
  if (buttonUpState != lastButtonUpState) 
  {
    if (buttonUpState == HIGH && m<7) 
    {
    
      //Reset the counter to -1
      if(counter ==7) // 2
      {       
        
        goto label;
      }
       
      //Increase the counter by 1
     
         counter++;
      //Print the counter to the console and calling the function
      Serial.println(counter);
      
      //Delaying by 250 ms
      delay(50);
      if(counter>=4 && counter<7)
      {
        
        Serial.println("down");
          pagechange(7);
         // changeNumber(counter);
          b=1;
      }
     changeNumber(counter);
    
    }
   
   delay(50);
   
   while(digitalRead(switchUpPin)==HIGH);
  }

  //Do this for the button down
  if (buttonDownState != lastButtonDownState) 
  {
    if (buttonDownState == HIGH && m<7) 
    {
     
       //Set the counter to 10
      if(counter == -1)
      {
        goto label;
       
       // counter =-1;
        delay(50);
      }
      //Decreases the counter by 1
      counter--;
      ////Print the counter to the console and calling the function
      Serial.println(counter);
      
      if(counter>3)
       //  changeNumber(counter);
      //Delaying by 250 ms
      delay(50);
    }
     if(counter<=3 && counter>0)
      {
       
        
          pagechange(8);
         // changeNumber(counter);
      }
      
    //Delay to avoid button bouncing
   delay(50);
    changeNumber(counter);
  }
    count=0;
    count1=t;
            
while(digitalRead(switchDownPin)==HIGH);


//  Gyneclogic Sample Prepartion Staring process

 Start_Buttonstate_1 = digitalRead(start_button);
 
 if ( Start_Buttonstate_1==  HIGH  && m==1)
      {
        buzzer(); 
       stop_pausebutton_status();
       vacuum_pump_1();
       top_bottom();
       delay(500);
       slide_in();
       delay(500);
       bottom_middle();
       delay(5000);
       top_bottom();
       delay(500);
       slide_out();
       delay(500);
       bottom_top();
       
   // Reset Functions
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" 1. Gynecologic sample preparation");
      lcd.setCursor(0,1);
      lcd.print(" 2. Fine Needle Aspirates");
      lcd.setCursor(0,2);
      lcd.print(" 3. Muciod specimens");
      lcd.setCursor(0,3);
      lcd.print(" 4. Body Fluid ");
      lcd.setCursor(0,0);
      lcd.noCursor();
      counter =0;
      delay(500);// Turn on the cursor:
      lcd.cursor();
      delay(500);
      buzzer();
      }

// Fine Needle Aspirates Functions
      
else if ( Start_Buttonstate_1 ==  HIGH  && m==2)
      {
         buzzer();
        vacuum_pump_2();
        top_bottom();
        delay(500);
        slide_in();
        delay(500);
        bottom_middle();
        delay(5000);
        top_bottom();
        delay(500);
        slide_out();
        delay(500);
        bottom_top();
        
    // Reset Functions     
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print(" 1. Gynecologic sample preparation");
       lcd.setCursor(0,1);
       lcd.print(" 2. Fine Needle Aspirates");
       lcd.setCursor(0,2);
       lcd.print(" 3. Muciod specimens");
       lcd.setCursor(0,3);
       lcd.print(" 4. Body Fluid ");
       lcd.setCursor(0,0);
       lcd.noCursor();
       counter =0;   
       delay(500);// Turn on the cursor:
       lcd.cursor();
       delay(500);
       buzzer();
    }
// Muciod Specimens Functions

  else if ( Start_Buttonstate_1 ==  HIGH  && m==3)
     {
         buzzer();
        vacuum_pump_2();
        top_bottom();
        delay(500);
        slide_in();
        delay(500);
        bottom_middle();
        delay(5000);
        top_bottom();
        delay(500);
        slide_out();
        delay(500);
        bottom_top();
           
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" 1. Gynecologic sample preparation");
        lcd.setCursor(0,1);
        lcd.print(" 2. Fine Needle Aspirates");
        lcd.setCursor(0,2);
        lcd.print(" 3. Muciod specimens");
        lcd.setCursor(0,3);
        lcd.print(" 4. Body Fluid ");
        lcd.setCursor(0,0);
        lcd.noCursor();
        counter =0;
        delay(500);// Turn on the cursor:
        lcd.cursor();
         delay(500);
         buzzer();
     }

// Body Fluid Functions 

  else if ( Start_Buttonstate_1 ==  HIGH  && m==4)
      {
           buzzer();
          vacuum_pump_2();
          top_bottom();
          delay(500);
          slide_in();
          delay(500);
          bottom_middle();
          delay(5000);
          top_bottom();
          delay(500);
          slide_out();
          delay(500);
          bottom_top();
           
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" 1. Gynecologic sample preparation");
          lcd.setCursor(0,1);
          lcd.print(" 2. Fine Needle Aspirates");
          lcd.setCursor(0,2);
          lcd.print(" 3. Muciod specimens");
          lcd.setCursor(0,3);
          lcd.print(" 4. Body Fluid ");
          lcd.setCursor(0,0);
          lcd.noCursor();
          counter =0;
          delay(500);// Turn on the cursor:
          lcd.cursor();
          delay(500);
          buzzer();
      }
 // Superficial Bruhings Function
 
  else if ( Start_Buttonstate_1 ==  HIGH  && m==5)
      {
            buzzer();
            vacuum_pump_2();
            top_bottom();
            delay(500);
            slide_in();
            delay(500);
            bottom_middle();
            delay(5000);
            top_bottom();
            delay(500);
            slide_out();
            delay(500);
            bottom_top();
           // delay(500);      
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print(" 1. Gynecologic sample preparation");
           lcd.setCursor(0,1);
           lcd.print(" 2. Fine Needle Aspirates");
           lcd.setCursor(0,2);
           lcd.print(" 3. Muciod specimens");
           lcd.setCursor(0,3);
           lcd.print(" 4. Body Fluid ");
           lcd.setCursor(0,0);
          lcd.noCursor();
          counter =0;
          delay(500);// Turn on the cursor:
          lcd.cursor();
          delay(500);
          buzzer();
      }

 // ETC Function
      
  else if ( Start_Buttonstate_1 ==  HIGH  && m==6)
      {
           buzzer();
          vacuum_pump_2();
          top_bottom();
          delay(500);
          slide_in();
          delay(500);
          bottom_middle();
          delay(5000);
          top_bottom();
          delay(500);
          slide_out();
          delay(500);
          bottom_top();
          buzzer();
           
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print(" 1. Gynecologic sample preparation");
         lcd.setCursor(0,1);
         lcd.print(" 2. Fine Needle Aspirates");
         lcd.setCursor(0,2);
         lcd.print(" 3. Muciod specimens");
         lcd.setCursor(0,3);
         lcd.print(" 4. Body Fluid ");
         lcd.setCursor(0,0);
         lcd.noCursor();
         counter =0;
         delay(500);// Turn on the cursor:
         lcd.cursor();
         delay(500);
         m=0;                                                                                                                                                                                          
    }
 // Manual Mode Functions     
 
 else if ( Start_Buttonstate_1 ==  HIGH  && m==7)
      {
          buzzer();
         digitalWrite( EN_VACCUM, HIGH);
         digitalWrite( EN_SOLE1, HIGH);
         lcd.setCursor(0,3);
         lcd.print(" Vaccum Motor Action .......");
         int val = buttonPushCounter;
         Serial.println(val);
         c= (a * val);
      
        Serial.println(c);
        delay(c);

        Serial.println("Solenoid 1 on ");
        digitalWrite( EN_VACCUM, LOW);
        digitalWrite( EN_SOLE1, LOW);
    
        top_bottom();
        delay(500);
        slide_in();
        delay(500);
        bottom_middle();
        int val_1 = counter2;
        c= (a * val_1);
        Serial.println(c);
        delay(c);
        top_bottom();
        delay(500);
        slide_out();
        delay(500);
        bottom_top();
     // delay(500);      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" 1. Gynecologic sample preparation");
        lcd.setCursor(0,1);
        lcd.print(" 2. Fine Needle Aspirates");
        lcd.setCursor(0,2);
        lcd.print(" 3. Muciod specimens");
        lcd.setCursor(0,3);
        lcd.print(" 4. Body Fluid ");
        lcd.setCursor(0,0);
        lcd.noCursor();
        counter =0;
        delay(500);// Turn on the cursor:
        lcd.cursor();
        delay(500);
        m=0;         
        counter2=0;
        buttonPushCounter=0;   
        buzzer();                                                                                                                                                              
    }

    
 if(Serial.available() > 0) {  // A byte is ready to receive
 inByte = Serial.read();
 
   if(inByte == 'A'){   // Move motor forward (FROM LOW,MIDDLE TO TOP)

    while(1){
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
     int MOVE_M = analogRead(10);
    float voltage = MOVE_M* (5.0 / 1023.0);
    Serial.println(voltage);
  // slide motor runing
    digitalWrite( Move_motor_Enable_A1, HIGH);
    digitalWrite( Move_motor_Enable_D1, HIGH);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(500);
    if (voltage < 0.2)
   {
    digitalWrite( LED_1, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
     digitalWrite( LED_1, LOW);
     Serial.println("MOVE_M");
     break;
   }
    } 
   }  

    if(inByte == 'B'){   // Move motor reverse ( FROM TOP TO MIDDLE)

    while(1){             
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
     int MOVE_L = analogRead(A9);
    float voltage_1 = MOVE_L* (5.0 / 1023.0);
    Serial.println(voltage_1);
  // slide motor runing
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, HIGH);
    digitalWrite( Move_motor_Enable_C1, HIGH);
    delay(500);
    if (voltage_1 < 0.2)
   {
    digitalWrite( LED_2, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
    digitalWrite( LED_2, LOW);
     Serial.println("MOVE_L");
     break;
   }
    } 
   }

     if(inByte == 'C'){ // FORWARD ACTICON FROM (A,B TO C)

    while(1){
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
     int MOVE_H = analogRead(A8);
    float voltage_2 = MOVE_H* (5.0 / 1023.0);
    Serial.println(voltage_2);
  // slide motor runing
  
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, HIGH);
    digitalWrite( Move_motor_Enable_C1, HIGH);
    delay(500);
 
    if (voltage_2 < 0.2)
   {
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
    digitalWrite( LED_3, LOW);
     Serial.println("MOVE_H");
     break;
   }
    } 
   }  
   if(inByte == 'D'){ // FORWARD ACTICON FROM (C TO B)

    while(1){
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
      int MOVE_L = analogRead(A9);
    float voltage_1 = MOVE_L* (5.0 / 1023.0);
    Serial.println(voltage_1);
  // slide motor runing
  
    digitalWrite( Move_motor_Enable_A1, HIGH);
    digitalWrite( Move_motor_Enable_D1, HIGH);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(500);
 
    if (voltage_1 < 0.2)
   {
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
    digitalWrite( LED_3, LOW);
     Serial.println("MOVE_H");
     break;
   }
    }
   }   
 if(inByte == 'E'){  // slide motor OUT action
    while(1){
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    
     int SLIDE_OP = analogRead(A12);
    float voltage_3 = SLIDE_OP* (5.0 / 1023.0);
    Serial.println(voltage_3);
   
  // slide motor runing
  
    digitalWrite( Move_motor_Enable_A2, HIGH);
    digitalWrite( Move_motor_Enable_D2, HIGH);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    delay(100);
 
    if (voltage_3 < 0.1)
   {
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    delay(100);
   digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, HIGH);
    digitalWrite( Move_motor_Enable_C2, HIGH);
    delay(10);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    
    digitalWrite( LED_3, LOW);
     Serial.println("SLIDE_OP");
     break;
   }
 }
 }
 if(inByte == 'F'){   // slide motor reverse action 
    while(1){
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
     int SLIDE_CL = analogRead(A11);
    float voltage_4 = SLIDE_CL* (5.0 / 1023.0);
    Serial.println(voltage_4);
    
  // slide motor runing
  
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, HIGH);
    digitalWrite( Move_motor_Enable_C2, HIGH);
    delay(10);
 
    if (voltage_4 < 0.1)
   {
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    delay(50);
    /*digitalWrite( Move_motor_Enable_A2, HIGH);
    digitalWrite( Move_motor_Enable_D2, HIGH);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    
    delay(50);
     digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);*/
    digitalWrite( LED_3, LOW);
     Serial.println("SLIDE_OP1");
     break;
   }
    }
 }  
 
 if(inByte == 'c'){
  
    int SLIDE_CL = analogRead(A11);
    float voltage_4 = SLIDE_CL* (5.0 / 1023.0);
    Serial.println(voltage_4);
    delay(100);
 }

 

 }
} // LOOP END

// Function for Cursor Up & Down 
void changeNumber(int buttonPress)
{
  switch (buttonPress)
  {
    case 0:
     lcd.setCursor(0,0);
     lcd.noCursor();
     delay(500);
     lcd.cursor();
     //delay(500); 
     buzzer();
     break;

     case 1:
     if (counter == 1){
     lcd.setCursor(0,1);
     lcd.noCursor();
     delay(500);
     lcd.cursor();
     //delay(500);
     buzzer();
      }
     break;
     
     case 2:
     if (counter == 2){
     lcd.setCursor(0,2);
     lcd.noCursor();
     delay(500);
     lcd.cursor();
     //delay(500);
     buzzer();
     }
     break;
     
     case 3:
     if (counter == 3){
     lcd.setCursor(0,3);
     lcd.noCursor();
     delay(500);
     lcd.cursor();
     //delay(500);
     buzzer();
     }
     break;
     case 4:
    if (counter == 4){
     lcd.setCursor(0,0);
     lcd.noCursor();
     delay(500);
     lcd.cursor();
     //delay(500);
     buzzer();
    }
     break;
     case 5:
     if (counter ==5){
     lcd.setCursor(0,1);
     lcd.noCursor();
     delay(500);
     lcd.cursor();
     buzzer();
     }
     delay(500);
     break;
     case 6:
     if (counter == 6 && b==1){
     lcd.setCursor(0,2);
     lcd.noCursor();
     delay(500);
     lcd.cursor();
     //delay(500);
     buzzer();
     }
     break; 

  }

}

// Function for pagechanges

  void pagechange(int page_counter )
  {
  switch (page_counter) 
  {
    case 0: { //Design of page 2
     m=1; 
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 1. Gynecologic sample preparation ");
     lcd.setCursor(0,1);
     lcd.print(" VCTIME VCPE1 VCPE2 TRANSHOLD TRANSPOWER");
     lcd.setCursor(0,2);
     lcd.print("   12    40     40     05         30 ");
     lcd.setCursor(3,2);
     buzzer();
    lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     break;
    
    }
    break;

    case 1: { //Design of page 2
      m=2; 
       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 2. Fine Needle Aspirates");
     lcd.setCursor(0,1);
     lcd.print(" VCTIME VCPE1 VCPE2 TRANSHOLD TRANSPOWER");
     lcd.setCursor(0,2);
     lcd.print("   03    40     40     05         30 "); 
     lcd.setCursor(3,2);
     buzzer();
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     break;
     
     }
    break;
    case 2: {   //Design of page 3
      m=3; 
       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 3. Muciod specimens");
     lcd.setCursor(0,1);
     lcd.print(" VCTIME VCPE1 VCPE2 TRANSHOLD TRANSPOWER");
     lcd.setCursor(0,2);
     lcd.print("   03    40     40     05         30 ");
     lcd.setCursor(3,2);
     buzzer();
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     break;
     }
    break;

    case 3: {   //Design of page 3 
      m=4;
       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 4. Body Fluid");
     lcd.setCursor(0,1);
     lcd.print(" VCTIME VCPE1 VCPE2 TRANSHOLD TRANSPOWER");
     lcd.setCursor(0,2);
     lcd.print("   03    40     40     05         30 ");
     lcd.setCursor(3,2);
     buzzer();
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     break;
     }
    break;
    case 4: {   //Design of page 3 
       m=5;
       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 5.Superficial Brushings and srapings");
     lcd.setCursor(0,1);
     lcd.print(" VCTIME VCPE1 VCPE2 TRANSHOLD TRANSPOWER");
     lcd.setCursor(0,2);
     lcd.print("   03    70     70     05         05 ");
     lcd.setCursor(3,2);
     buzzer();
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     break;
     }
    break;
    case 5: {   //-Design of page 3 
       m=6;
       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 6. ETC");
     lcd.setCursor(0,1);
     lcd.print(" VCTIME VCPE1 VCPE2 TRANSHOLD TRANSPOWER");
     lcd.setCursor(0,2);
     lcd.print("   03    70     70     05         05 ");
     lcd.setCursor(3,2);
     buzzer();
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     break;
     }
    break;
    case 6: {   //Design of page 3 
    m=7;
    buzzer();
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 7.Manual");
     lcd.setCursor(0,1);
     lcd.print(" VCTIME VCPE1 VCPE2 TRANSHOLD TRANSPOWER");
     lcd.setCursor(0,2);
     lcd.print("   3     70     70     5          05 ");
     lcd.setCursor(0,0);
     lcd.noCursor();
     delay(500);
      //Turn on the cursor:
     lcd.cursor();
     delay(500);
   
     break;
     }
      m=0;
    break;
  
    case 7:
    {  
      
      lcd.clear();
          lcd.setCursor(0,0);
     lcd.print(" 5. Superficial Brushings and srapings ");
     lcd.setCursor(0,1);
     lcd.print(" 6. ETC ");
     lcd.setCursor(0,2);
     lcd.print(" 7. Manual ");
     
  }
      break;
 case 8:{
      buzzer(); 
      lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(" 1. Gynecologic sample preparation");
     lcd.setCursor(0,1);
     lcd.print(" 2. Fine Needle Aspirates");
     lcd.setCursor(0,2);
    lcd.print(" 3. Muciod specimens");
    lcd.setCursor(0,3);
    lcd.print(" 4. Body Fluid ");
   }
 break; 
 
}
  }

  // Function for Cursor chenages on manual mode 
void changeNumber1(int buttonPress)
{
  switch (buttonPress)
  {
    //number 0
    case 0:
     lcd.setCursor(3,2);
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500); 
     l=1;
     b=0;
     break;

      case 1:

     lcd.setCursor(9,2);
     lcd.noCursor();
     delay(500);
      //Turn on the cursor:
     lcd.cursor();
     delay(500);
     l=2;
     b=0;    
     break;
     
     case 2:
     lcd.setCursor(16 ,2);
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     l=3;
     b=0;
     break;
     
     case 3:
     lcd.setCursor(23,2);
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     l=4;
     b=0;
     break;
    case 4:
    
     lcd.setCursor(34,2);
     lcd.noCursor();
     delay(500);
     // Turn on the cursor:
     lcd.cursor();
     delay(500);
     l=5;
     b=0;
     break;
  
  }
}

   void bottom_top()
           
    {
    while(1){
    stop_pausebutton_status();
      
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
     int MOVE_M = analogRead(10);
    float voltage = MOVE_M* (5.0 / 1023.0);
    Serial.println(voltage);
  // slide motor runing
     lcd.setCursor(0,3);
     lcd.print(" Move Motor Up Action .......");
    digitalWrite( Move_motor_Enable_A1, HIGH);
    digitalWrite( Move_motor_Enable_D1, HIGH);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(100);
    if (voltage < 0.01)
   {
    digitalWrite( LED_1, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
     digitalWrite( LED_1, LOW);
     Serial.println("MOVE_M");
     break;
   }
    } 
   }  
  void middle_bottom(){
    
    while(1){             
     stop_pausebutton_status();
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    int MOVE_L = analogRead(A9); //this line is in "//"
    float voltage_1 = MOVE_L* (5.0 / 1023.0);
    Serial.println(voltage_1);
  // slide motor runing
    lcd.setCursor(0,3);
     lcd.print(" Move Motor Down Action .......");
    
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, HIGH);
    digitalWrite( Move_motor_Enable_C1, HIGH);
    delay(50);
    if (voltage_1 < 0.01)
   {
    digitalWrite( LED_2, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
    digitalWrite( LED_2, LOW);
     Serial.println("MOVE_L");
     break;
   }
    } 
   }

void top_bottom()
{
    while(1){
      stop_pausebutton_status();
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
     int MOVE_H = analogRead(A8);
    float voltage_2 = MOVE_H* (5.0 / 1023.0);
    Serial.println(voltage_2);
  // slide motor runing
  lcd.setCursor(0,3);
     lcd.print(" Move Motor Down Action .......");
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, HIGH);
    digitalWrite( Move_motor_Enable_C1, HIGH);
    delay(200);
 
    if (voltage_2 < 0.01)
   {
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
    digitalWrite( LED_3, LOW);
     Serial.println("MOVE_H");
     break;
   }
    } 
   }  
  void bottom_middle(){ // FORWARD ACTICON FROM (C TO B)

    //while(1){
    stop_pausebutton_status();
   /* digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
      int MOVE_L = analogRead(A9);
    float voltage_1 = MOVE_L* (5.0 / 1023.0);
    Serial.println(voltage_1);
  // slide motor runing*/
  lcd.setCursor(0,3);
     lcd.print(" Move Motor Paint Action .......");
    digitalWrite( Move_motor_Enable_A1, HIGH);
    digitalWrite( Move_motor_Enable_D1, HIGH);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(2000);
 
    //if (voltage_1 < 0.2)
   //{
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    delay(200);
    digitalWrite( LED_3, LOW);
     Serial.println("MOVE_H");
     //break;
   //}
    //}
   }
      
    void slide_out(){  // slide motor OUT action  ( E ACTION)
    while(1){
      stop_pausebutton_status();
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
     int SLIDE_OP = analogRead(A12);
    float voltage_3 = SLIDE_OP* (5.0 / 1023.0);
   Serial.println(voltage_3);
  // slide motor runing
  lcd.setCursor(0,3);
     lcd.print(" Slide Motor Out Action .......");
    digitalWrite( Move_motor_Enable_A2, HIGH);
    digitalWrite( Move_motor_Enable_D2, HIGH);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    delay(50);
 
    if (voltage_3 < 0.01)
   {
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    delay(100);
    /*digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, HIGH);
    digitalWrite( Move_motor_Enable_C2, HIGH);
    delay(50);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);*/
     digitalWrite( LED_3, LOW);
     Serial.println("SLIDE_OUT");
     break;
   }
 }
 }
    void slide_in(){   // slide motor reverse action  ( F ACTION)  
    while(1){
      stop_pausebutton_status();
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
     int SLIDE_CL = analogRead(A11);
    float voltage_4 = SLIDE_CL* (5.0 / 1023.0);
    Serial.println(voltage_4);
  // slide motor runing
  lcd.setCursor(0,3);
     lcd.print(" Slide Motor In Action .......");
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, HIGH);
    digitalWrite( Move_motor_Enable_C2, HIGH);
    delay(10);
 
    if (voltage_4 < 0.01)
   {
     digitalWrite( LED_3, HIGH);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    delay(100);
    /*digitalWrite( Move_motor_Enable_A2, HIGH);
    digitalWrite( Move_motor_Enable_D2, HIGH);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    delay(50);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);*/
   
    digitalWrite( LED_3, LOW);
     Serial.println("SLIDE_IN");
     break;
   }
    }
 }

void vacuum_pump_1(){   // vaccum pump running 12 sec 
  stop_pausebutton_status();
digitalWrite( EN_VACCUM, HIGH);
digitalWrite( EN_SOLE1, HIGH);
lcd.setCursor(0,3);
     lcd.print(" Vaccum Motor Action .......");
delay(12000);
Serial.println("Solenoid 1 on ");
digitalWrite( EN_VACCUM, LOW);
digitalWrite( EN_SOLE1, LOW);
 }

void vacuum_pump_2(){  // vaccum pump running 3 sec  
 stop_pausebutton_status(); 
digitalWrite( EN_VACCUM, HIGH);
digitalWrite( EN_SOLE1, HIGH);
lcd.setCursor(0,3);lcd.print(" Vaccum Motor Action .......");
delay(3000);
Serial.println("Solenoid 1 on ");
digitalWrite( EN_VACCUM, LOW);
digitalWrite( EN_SOLE1, LOW);
 }

void solinoid(){  //solinoid opening & closing
digitalWrite( EN_SOLE1, HIGH);
delay(12000);
Serial.println("Solenoid 1 on ");
digitalWrite( EN_SOLE1, LOW);
}
 //*****checking wether start button is ativated **///
void stop_pausebutton_status(void)
{
      Button_start_pause_State = digitalRead(stop_button);
       if (Button_start_pause_State != lastButton_start_pause_State)      //Checking  for Start or pause button pressed 
        {
          if (Button_start_pause_State == HIGH) 
          {
            Serial.println("stopbutton pressed");
                       //EEPROM.write(6,1);  // indicating present at Pause state
             All_motors_deactivation();
             //digitalWrite(SSR_for_cooker_power_control, LOW);
                 while(digitalRead(stop_button) == HIGH);
                    while(1)
                    {
                    
                            Button_start_pause_State = digitalRead(stop_button);
                            if (Button_start_pause_State != lastButton_start_pause_State)      //Checking  for Start or pause button pressed 
                            {
                                  if (Button_start_pause_State == HIGH) 
                                  {
                                   while(digitalRead(stop_button) == HIGH); 
                                    buzzer(); 
                                      delay(250);
                                      //EEPROM.write(6,0);  // indicating present at ready state
                                      return;
                                
                                  }              
                            }
            
                    }
      
          }
        }
}


///******  ALL Motors deactivation *****////
void All_motors_deactivation ()
{
    digitalWrite( Move_motor_Enable_A1, LOW);
    digitalWrite( Move_motor_Enable_D1, LOW);
    digitalWrite( Move_motor_Enable_B1, LOW);
    digitalWrite( Move_motor_Enable_C1, LOW);
    digitalWrite( Move_motor_Enable_A2, LOW);
    digitalWrite( Move_motor_Enable_D2, LOW);
    digitalWrite( Move_motor_Enable_B2, LOW);
    digitalWrite( Move_motor_Enable_C2, LOW);
    digitalWrite( EN_VACCUM, LOW);
    digitalWrite( EN_SOLE1, LOW);
    buzzer();
  //       return 0;
}

// Maanual count increment function 

void checkUp()

{

  up_buttonState = digitalRead(Up_buttonPin);

  if (up_buttonState != up_lastButtonState) {

       if (up_buttonState == LOW && counter == 6 ) {

        bPress = true;
    
      if (counter1 ==0){
          buttonPushCounter++;
          Serial.println("increase");

        }
      if (counter1 == 3){
          counter2++;
          Serial.println("increase2");
       }
    } 

    
  }

  // save the current state as the last state, for next time through the loop

  up_lastButtonState = up_buttonState;

}

void checkDown()

{
  down_buttonState = digitalRead(Down_buttonPin);
 
  if (down_buttonState != down_lastButtonState) {

    if (down_buttonState == LOW && counter == 6 ) {

       
        bPress = true;

    if (counter1 ==0){
      buttonPushCounter--;
      Serial.println("deicrease");
      }
     if (counter1 == 3){
      counter2--;
       Serial.println("deicrease1");
     }
     
    
       Serial.println(counter);
    } 

  }

  // save the current state as the last state, for next time through the loop

  down_lastButtonState = down_buttonState;

}

void buzzer()
{
  digitalWrite( Buzzer, HIGH);
  delay(150);
  digitalWrite( Buzzer, LOW);
}
