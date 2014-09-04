#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

volatile unsigned long time0;
volatile unsigned long deltat;
volatile int measured;
volatile int stopped;
volatile int started;
volatile float v0;
float mbb=0.20E-3;
volatile float E0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16,4);
 
  lcd.noAutoscroll();
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("****************");
  lcd.setCursor(0,1);
  lcd.print("* DL6TA Chrono *");
  lcd.setCursor(0,2);
  lcd.print("*     V0.1     *");
  lcd.setCursor(0,3);
  lcd.print("****************");
  
  delay(1000);
  lcd.clear();
  
  // attach interrupts
  attachInterrupt(0,starttimer, RISING);
  attachInterrupt(1, stoptimer, RISING);
  
  // initialize variables
  measured = 0;
  started = 0;
  stopped = 0;
  
   lcd.print("****************");
  lcd.setCursor(0,1);
  lcd.print("*    please    *");
  lcd.setCursor(0,2);
  lcd.print("*    shoot     *");
  lcd.setCursor(0,3);
  lcd.print("****************");
}

void loop() {
  
  
  while(started == 0){};
  
  lcd.clear();
  
  lcd.print("****************");
  lcd.setCursor(0,1);
  lcd.print("* measuring... *");
  lcd.setCursor(0,2);
  lcd.print("*              *");
  lcd.setCursor(0,3);
  lcd.print("****************");
  lcd.setCursor(2,2);
  
  while(stopped == 0){
    
    if(micros() - time0 > 1000000)
    {
      stopped = 1;
      };
      
    if(micros() % 10000 == 0)
    {
      lcd.print(".");
    };
  };
  
  lcd.clear();
  
  if(measured == 1)
  {
      v0 = 125000. / deltat;
      E0=.5*mbb*v0*v0;
      lcd.print("****************");
      lcd.setCursor(0,1);
      lcd.print("*v0=");
      lcd.print(v0);
      lcd.print("m/s");
      lcd.setCursor(15,1);
      lcd.print("*");
      lcd.setCursor(0,2);
      lcd.print("*E0=");
      lcd.print(E0);
      lcd.print("J");
      lcd.setCursor(15,2);
      lcd.print("*");
      lcd.setCursor(0,3);
      lcd.print("****************");

  }
  else
  {
      lcd.print("****************");
      lcd.setCursor(0,1);
      lcd.print("*     FAIL     *");
      lcd.setCursor(0,2);
      lcd.print("* shoot again  *");
      lcd.setCursor(0,3);
      lcd.print("****************");
   
  };

  measured = 0;
  started = 0;
  stopped = 0;
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis()/1000);
}

void starttimer() {
  // set timer start variable to current time
  time0 = micros();
  started = 1;
}

void stoptimer() {
  // compute time delay
  deltat = micros() - time0;
  
  //initiate output
  measured = 1;
  stopped = 1;
}
