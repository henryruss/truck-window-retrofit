/*
• A program to roll a car window up and down from button inputs
• Author: Henry Russell
*/

//constants for arduino pins
const int RPWM = 6;
const int LPWM = 5;
const int R_EN = 7;
const int L_EN = 8;
const int upButtonPin = 12;
const int downButtonPin = 13;
const int currentPin = A5;
// constant for debounce time
const long debounceDelay = 100;

//global variables for debouncing
int upButtonState; //keep track of up button state being high or low
int lastUpButtonState = LOW; //set initial state to unpressed
int downButtonState; //keep track of down button state being high or low
int lastDownButtonState = LOW; //set initial state to unpressed
long lastUpDebounceTime = 0; //needs to be a long because time in ms will get too large for an int
long lastDownDebounceTime = 0;

void setup() {
  //set outputs- these can be changed by the arduino 
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  //set inputs- these are signals to the arduino
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(currentPin, INPUT);

  //start with motor off in setup to avoid accidental signals
  motorOff(); 

  //Serial.begin(9600); include for using print statements

}

  // main loop to constantly check for button presses
void loop() {

  int upReading = digitalRead(upButtonPin); //get state of up button every loop iteration
  int downReading = digitalRead(downButtonPin); //get state of down button every loop iteration
  // float currentReading = analogRead(currentPin); //get state of current drawn every loop iteration (commented out since automatic mode is not in use yet)


  if(upReading != lastUpButtonState){ //if we detect a button press, enter
    lastUpDebounceTime = millis(); //get the number of milliseconds it has been 
  }

  if ((millis()-lastUpDebounceTime) > debounceDelay){ //if the amount of time passed is greater than the debounce time, it is a genuine button press
    if (upReading != upButtonState){ //check that we have switches states
      upButtonState = upReading; //update state
    }
  }
  lastUpButtonState = upReading; //update previous state so that we can check for the next state change

    if(downReading != lastDownButtonState){ //if we detect a button press, enter
    lastDownDebounceTime = millis(); //get the number of milliseconds it has been 
  }

  if ((millis()-lastDownDebounceTime) > debounceDelay){ //if the amount of time passed is greater than the debounce time, it is a genuine button press
    if (downReading != downButtonState){ //check that we have switches states
      downButtonState = downReading; //update state
    }
  }
  lastDownButtonState = downReading; //update previous state so that we can check for the next state change


  bool upPressed = (upButtonState); //boolean variable for up button being pressed vs non pressed
  bool downPressed = (downButtonState); //boolean variable for down button being pressed vs non pressed

  // Print statements for testing
  // Serial.print("Down button state: ");
  // Serial.print(downPressed);
  // Serial.print(" Up button state: ");
  // Serial.print(upPressed);
  // Serial.print(" current: ");
  // Serial.println(currentReading);

if (upPressed && !downPressed) { // UP is pressed and DOWN is NOT pressed
  // Serial.println("Up! (Debounced)"); // Use this for testing debounce
  rollUp(); //helper function to roll the window up
}
else if (downPressed && !upPressed) { // DOWN is pressed and UP is NOT pressed
  // Serial.println("Down! (Debounced)"); // Use this for testing debounce
  rollDown(); //helper function to roll the window down
}

else{ //if no buttons have been pressed (or if both are simultaneously pressed) turn the motor off
  motorOff();
}

}
 
//helper function to turn on motor driver and roll the motor up
void rollUp(){
    //R_EN and L_EN connects the H Bridge, allowing us to run the motor
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  //RPWM high and LPWM low turns the motor such that the window raises
  digitalWrite(RPWM, HIGH);
  digitalWrite(LPWM, LOW);
}

//helper function to turn on motor driver and roll the motor down
void rollDown(){
    //R_EN and L_EN connects the H Bridge, allowing us to run the motor
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  //RPWM low and LPWM high turns the motor such that the window lowers
  digitalWrite(RPWM, LOW);
  digitalWrite(LPWM, HIGH);
}

//function to kill the motor
void motorOff(){
  //shut off H-bridge
  digitalWrite(R_EN, LOW);
  digitalWrite(L_EN, LOW);

  //Turn of PWM signaling
  digitalWrite(RPWM, LOW);
  digitalWrite(LPWM, LOW);
}

