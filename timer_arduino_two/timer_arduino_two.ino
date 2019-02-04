//******************* HEADER *********************
/*
  Name : Timer_arduino_two
  Title: Countdown Timer, arduino based.
  Desc: Countdown Timer: 1-99 minutes. Output(mm:ss) 
  to 4-digit seven segment display(SMA420564) and Buzzer.
  Push button start. Time select via potentiometer input
  Author: Gavin Lyons 
  URL:https://github.com/gavinlyonsrepo/timer_arduino_two
*/

//******************** GLOBALS ********************

//buzzer the pin of the active buzzer A3
int buzzer = 17; 

// Button pin , A4
#define buttonPin 18
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int count_start = 0;

// vars for timer calculations
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60)
// hold time selected in ms.
unsigned long timeLimit = 0;

//pot pin Analog A5
int potPin = A5;
// Varibles to Sample and smooth the A0 input from pot to reduce gitter on display
// Define the number of samples to keep track of. The higher the number, the
const int numReadings = 15;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total

//the pins of 4-digit 7-segment display attach to pin2-13 respectively 
int ledPins[] = { 2, 3, 4, 5, 6, 7, 8}; // an array of pin numbers to which LEDs of the segments are attached
// Four pins to connect to four digits.
int d4 = 10;
int d3 = 11;
int d2 = 12;
int d1 = 13;
int del = 5; //timing delay for 7-seg display adjust 


//************************ SETUP ************************
void setup() {

  // Setup serial
  Serial.begin(9600);
  delay(50);
  Serial.println("----------- Timer Arduino TWO Comms up ------------");

  // button setup
  // Setup pins for push button enable internal pull-up resistors
  digitalWrite(buttonPin, HIGH);

  //buzzer setup
  pinMode(buzzer, OUTPUT); 
  digitalWrite(buzzer, LOW);

  
  // initialize all the readings in array to 0(array used to stablize pot readings):
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

   //seven segment setup
   //set all the pins of the LED display as output
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  for (int thisPin = 0; thisPin < 7; thisPin++)  
    {
       //  Serial.println(thisPin);
        pinMode(ledPins[thisPin], OUTPUT);      
    }   
}

//******************* MAIN LOOP *****************
void loop() {
  // read the pot
  if (count_start == 0)
  {
    potRead();
  }

  // read and debounce push button.
  int reading = digitalRead(buttonPin);
  // If the switch changed?
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // start timer if the new button state is low
      if (buttonState == LOW) {
        TestButton();
      }
    }
  }

  // save the reading.
  lastButtonState = reading;
  delay(1);
}

// ********************* FUNCTIONS *************************

// TestButton:  Function to handle button press
void TestButton()
{
  Serial.print("Count: ");
  //Serial.println(count_start);
  count_start ++;
  if (count_start == 1)
  {
    countdown();
    my_buzzer();
  }
}

// potRead: Function to read analog pin connected to pot and display it in 7-seg
// includes smoothing the analog sample by taking avergae of 15 readings
void potRead()
{
  unsigned long average = 0;
  // subtract the last reading:
  total = total - readings[readIndex];
  readings[readIndex] = map(analogRead(potPin), 0, 1023, 1, 99);
  // increment total and array
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  // check for end of array, wrap to start if yes
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  timeLimit = ((average * 60) * 1000);
  //Serial.println(average); debug 
  Display_time(0,int(average));
  //delay(5);
}

//my_buzzer: function to switch on buzzer and display "0" on 7-seg
void my_buzzer (void)
{
  unsigned char i;
  unsigned char j;
  Display_time(0,0);
  // run  buzzer for a few minutes.
  for (j = 0; j < 250; j++)
  {
    //output an frequency
    for (i = 0; i < 100; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(1);//wait for 1ms
      digitalWrite(buzzer, LOW);
      delay(1);//wait for 1ms
    }
    //output another frequency
    for (i = 0; i < 100; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(2);//wait for 2ms
      digitalWrite(buzzer, LOW);
      delay(2);//wait for 2ms
    }
    
  }
   digitalWrite(buzzer, LOW);
   clearLEDs(); 
   while(1)
   {
      __asm__("nop\n\t"); // Finished , loop until hard  reset by user
   }
}

// countdown: function to handle and display the countdown time
void countdown() {
  // Calculate the time remaining
  unsigned long  runTime = 0;
  //Serial.println(timeLimit); debug
  runTime = millis();
  unsigned long timeRemaining = timeLimit - (millis() - runTime);
  Serial.println("Countdown started..: ");
  // Serial.println(timeRemaining); debug
  while (timeRemaining > 50 )
  {
    // To display the countdown in mm:ss format, separate the parts
    int seconds = numberOfSeconds(timeRemaining);
    int minutes = numberOfMinutes(timeRemaining);
    // Serial.println(timeRemaining); debug
    Display_time(seconds,minutes);
    // Update the time remaining
    timeRemaining = timeLimit - (millis() - runTime);
  }
  Serial.println("Countdown Finshed..: ");
}

//Function : Display_time : display the time to 7-seg
 void Display_time(int seconds, int minutes)
 {
 
  clearLEDs();//clear the 7-segment display screen
  pickDigit(0);//Light up 7-segment display d1
  pickNumber((minutes/10%10));
  delay(del);

  clearLEDs();//clear the 7-segment display screen
  pickDigit(1);//Light up 7-segment display d2
  pickNumber(minutes%10);
  delay(del);

  clearLEDs();//clear the 7-segment display screen
  pickDigit(2);//Light up 7-segment display d3
  pickNumber((seconds/10)%10);
  delay(del);
  
  clearLEDs();//clear the 7-segment display screen
  pickDigit(3);//Light up 7-segment display d4
  pickNumber(seconds%10);
  delay(del);
 }

//Function to select each digit of seven seg individually
 void pickDigit(int x) 
{
  //The 7-segment LED display is a common-cathode one. 
  // digitalWrite set d1 as high and the LED will go out
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  switch(x)
  {
    case 0: 
    digitalWrite(d1, LOW);//Light d1 up 
    break;
    case 1: 
    digitalWrite(d2, LOW); //Light d2 up 
    break;
    case 2: 
    digitalWrite(d3, LOW); //Light d3 up 
    break;
    default: 
    digitalWrite(d4, LOW); //Light d4 up 
    break;
  }
}

//Function to set all LEDS low on seven segment
void clearLEDs() //clear the 7-segment display screen
{
    for (int thisPin = 0; thisPin < 7; thisPin++)  
    {
        
        digitalWrite(ledPins[thisPin], LOW);      
    }
}

//Function to Display number data pattern on each 7-seg digit, is 
//passed digit to display
void pickNumber(int digitnumber)
{
    uint8_t data[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67}; //array holds 1-10 pattern
    //example display zero = 0x3f =  0b0111111 mapped to pins gfedcba on seven segment.
    int data1;
    // Loop thru LED array and bitshift the data pattern 
    //of passed digit and AND mask it and then apply it to LED array.
    for (int thisPin = 0; thisPin < 7; thisPin++)  
    {
         data1 = (data[digitnumber] >> thisPin) & 0x01; 
         if (data1 == 1)
         {
            digitalWrite(ledPins[thisPin], HIGH);
         }
         else if (data1 == 0)
         {
            digitalWrite(ledPins[thisPin], LOW);
         }
    }
}
//******************* EOF *****************

