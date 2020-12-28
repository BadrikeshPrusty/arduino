/*
 * Author Name  : Badrikesh Prusty
 * Organisation : Emertxe Information Technologies (P) Ltd.
 * Date         : 03/08/2020
 * Description  : Write an Arduino program to create an LED train using 4 LEDs that enters and exits the tunnel in both Left to Right
                  and Right to Left using non-blocking delay.
 * Input        : No user input required
 * Output       : LED train will first enter then Tunnel from the Left and then exit the tunnel. Then it will Enter the tunnel from the 
                  Right and exit the tunnel.
 */

#define L2R 0               //Defining direction value for train moving Left to Right 
#define R2L 1               //For train moving Right to Left
#define some_msec 0xFFFF    //defining wait time this value creates delay in the order of milli seconds (non blocking delay)

byte LED[4] = {2, 3, 4, 5}; //Defining array of LED with values as arduino pins
                            //that a specific LED is connected to
void setup() {              //setup function runs only once the after arduino is connected to the power or reset button is pressed
  for ( byte i = 0; i < 4; i++ )    //iterate the loop 4 times as number of LEDs is used is 4
    pinMode(LED[i], OUTPUT);        //creating all 4 digital pins of arduino that the LEDs are connected to as OUTPUT
}

void loop() {                         //Loop function iterates all the the time after the setup function 
  static char i = 0;                  //defining static variables such that it gets declared only once if the loop runs for the first time
  static bool flag = 1, route = L2R;  //flag is the state of the switch and initially set to on, initial route to follow is Left to right
  static unsigned wait = 0;           //initial value of nuon blocking delay is 0
  
  if ( wait == some_msec )  {         //if wait time matches the defined milli_seconds delay go to this block 
    wait = 0;                         //set back the wait value to 0
    digitalWrite(LED[i], flag);       //Turn on or off the LED as per the flag value, 0 for OFF, 1 for ON
    if ( route == L2R )               //if the route is Left to Right
      i++;                            //increment the i which will point to next consecutive LED
    else if ( route == R2L )
      i--;                            //if Right to left point to previous consecutive LED
  }
  
  if ( i == 4 || i == -1 )  {         //if i value reaches 4 and -1 then all the LEDs are in same state and waiting for turning on or off
    if ( flag == 0 )                  //if switch state is 0 that mean all the LEDs are off then change the route
      route = !route;                 //if route is Left to right then change to Right to Left and vise-versa
    flag = !flag;                     //if value of flag is 0 change it to 1 or vise-versa
    
    if ( route == L2R )               //if the root is Left to Right
      i = 0;                          //LEDs will start from 0th location. i.e., start glowing from 0 to 3 or turning off from 0 to 3
    else if ( route == R2L )
      i = 3;                          //else 3 to 0. Starting from 3
  }
  wait++;                             //increment the wait value everytime the loop runs 
}
