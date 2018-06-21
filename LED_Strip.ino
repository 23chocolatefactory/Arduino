#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
  #include <avr/power.h>
#endif


int wait;
volatile int RightGo;
volatile int LeftGo;

volatile int rightState = digitalRead(3);
volatile int leftState  = digitalRead(2);

int dataPinRight  = 5;
int clockPinRight = 6;
LPD8806 ledRight  = LPD8806(24, dataPinRight, clockPinRight);

int dataPinLeft   = 8;
int clockPinLeft  = 9;
LPD8806 ledLeft   = LPD8806(24, dataPinLeft, clockPinLeft);



void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(2,INPUT_PULLUP); // Left Button
  pinMode(3,INPUT_PULLUP); // Right Button
  
  wait = 30;

  RightGo = false;
  LeftGo  = false;
  
  // If using Trinket, uncomment this:
  // #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  //  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  // #endif

  
 ledRight.begin(); // Starts the right LED strip
 ledRight.show();  // The *.show() method sends the updated info to the LED strip

 ledLeft.begin(); // Starts the left LED strip
 ledLeft.show();  

 // Interrupt for always montioring the buttons when pressed, even during delays: 
 
   // Left Button
   attachInterrupt(digitalPinToInterrupt(2), leftButton, CHANGE);
   // Right Button
   attachInterrupt(digitalPinToInterrupt(3), rightButton, CHANGE);
   
}

void loop() {
  uint32_t clr = ledRight.Color(255, 157, 0);
  leftState  = digitalRead(2);
  rightState  = digitalRead(3);
  
  // Right Light Strip Activation
  if(RightGo == true){
    
    // Start by turning all pixels off:
      int i;
      for(i=0;i<ledRight.numPixels();i++){ ledRight.setPixelColor(i,0); ledRight.show();}
    
    // Show Pixels:
      for(i=0;i<ledRight.numPixels();i++){
        ledRight.setPixelColor(i, clr); // Sets the current pixel to the color stored in `clr`
        ledRight.show();
        delay(wait);
      }
  
    // Hide Pixels:
      for(i=0;i<ledRight.numPixels();i++){
        ledRight.setPixelColor(i, 0); // Sets the current pixel to the 0, which is interpreted as off
        ledRight.show();
        delay(wait);
      }
  }

  // Left Light Strip Activation
  if(LeftGo == true){
    
    // Start by turning all pixels off:
      int i;
      for(i=0;i<ledLeft.numPixels();i++){ ledLeft.setPixelColor(i,0); ledLeft.show();}
    
    // Show Pixels:
      for(i=0;i<ledLeft.numPixels();i++){
        ledLeft.setPixelColor(i, clr); // Sets the current pixel to the color stored in `clr`
        ledLeft.show();
        delay(wait);
      }
  
    // Hide Pixels:
      for(i=0;i<ledLeft.numPixels();i++){
        ledLeft.setPixelColor(i, 0); // Sets the current pixel to the 0, which is interpreted as off
        ledLeft.show();
        delay(wait);
      }
  }

  
} 


//============== Left Button Interrupt
void leftButton(){
  leftState  = digitalRead(2);
  rightState  = digitalRead(3);
  
  if(leftState == HIGH){if(LeftGo == false){LeftGo  = true;}else{LeftGo  = false;}}
}


//============== Right Button Interrupt
void rightButton(){
  leftState  = digitalRead(2);
  rightState  = digitalRead(3);
  
  if(rightState == HIGH){if(RightGo == false){RightGo = true;}else{RightGo = false;}}
}
