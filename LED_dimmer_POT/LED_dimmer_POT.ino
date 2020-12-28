/*
 * Author Name      : Badrikesh Prusty
 * Organisation     : Emertxe Information Technologies (P) Ltd.
 * Date             : 17/08/2020
 * Description      : Write an Arduino program to implement LED dimmer applications with Potentiometer
 * Input            : Adjust the Potentiometer to control the brighness of LED.
 * Output           : LED brightness varies from 0 to 100% based on potentiometer position
 */
 
#define LED     10                //LED is attached to Digital Pin 10 of arduino
#define PERIOD  255               //setting PERIOD value. PERIOD = T(on) + T(off)
#define POT     A0                //Potentiometer middle pin is connected to Analog Pin A0

void setup() {                    //code within setup function runs only once 
    pinMode(LED, OUTPUT);
}

void loop() {                         //code within loop function runs infinite number of times in a loop
    static byte Pot_Value, duty, wait;

    if ( duty <= Pot_Value )          //if value of duty is less than or equal to POT value go to this block 
        digitalWrite(LED, HIGH);      //turn the LED on

    else
        digitalWrite(LED, LOW);

    if ( duty++ == PERIOD ) {         //if incremented duty value matches with PERIOD value go to this block
        if ( wait++ == 20 ) {                     //go to this block every 20 period
            Pot_Value = analogRead(POT) / 4;      //as analog read function is very slow, checking it every cycle will lead to flickering 
            wait = 0;                             //converting 10 bit analog read value to 8 bit, by dividing by 4. So, max value = 255
        }
        duty = 0;                     //turn the duty value to 0 every period
    }
}
