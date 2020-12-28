/*
 * Author Name  : Badrikesh Prusty
 * Organisation : Emertxe Information Technologies (P) Ltd.
 * Date         : 03/08/2020
 * Description  : Write an Arduino code to create an LED train using 4 LEDs that enters and exits the tunnel in both Left to Right
                  and Right to Left using blocking delay.
 * Input        : No inputs from the user required
 * Output       : LED train will first enter then Tunnel from the Left and then exit the tunnel. Then it will Enter the tunnel from the 
                  Right and exit the tunnel.
 */

#define ENTER 1             //defining macros for turning ON and OFF the LEDs. ENTER denotes that train entering the tunnel
#define EXIT 0              //EXIT denotes train leaving the tunnel

byte LED[4] = {2, 3, 4, 5};  //Global variable array if LEDs defining the pin the specific LED is connected to

void setup() {              //Setup function is used where we want to run a piece of code only once. Ex: setting up/configuring part
  for ( byte i = 0; i < 4; i++ )//iterate loop as per the size of the array
    pinMode(LED[i], OUTPUT);    //PinMode function is used to define the specific pin of microcontroller that
}                               //whether the PIN is an INPUT pin or the OUTPUT Pin (Taking Input or giving Output)
                                //Here it is providing output to LEDs to Turn ON and OFF
void loop() {               //loop function 
  LED_train_L2R(ENTER);     //function call for the LED train ENTERING from LEFT to Right
  LED_train_L2R(EXIT);      //call to Exit the tunnel
  LED_train_R2L(ENTER);     //call to enter the tunnel from RIght to Left
  LED_train_R2L(EXIT);      //call to exit the tunnel
}

void LED_train_L2R(bool switch_state) {     //function definition for train moving left to right
  for ( char i = 0; i < 4; i++ ) {          //Iterate loop for times as per the value of i
    digitalWrite(LED[i], switch_state);     //turn on or off the LED as per the switch state
    delay(150);                             //delay function here to create a delay of 150 msec to change state of consecutive leds
  }
}

void LED_train_R2L(bool switch_state) {     //function definition for train moving right to left
  for ( char i = 3; i > -1; i-- ) {         //iterate loop from i value of 3 to 0
    digitalWrite(LED[i], switch_state);
    delay(150);
  }
}
