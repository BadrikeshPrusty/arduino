/*
 * Author Name      : Badrikesh Prusty
 * Organisation     : Emertxe Information Technologies (P) Ltd.
 * Date             : 30/08/2020
 * Description      : Write an Arduino program to implement timer based PWM such that it increases the brightness if key is on hold
 * Input            : Hold the key to increase the brightness
 */

#define LED_PIN 4
#define PWM_KEY 2
#define PERIOD  255

static byte T_on;

void setup() {              //code in setup function only runs once
    cli();        //deactivate interupts for any generation of interrupt while configuring 
  
    //Timer0
    TCCR0A = 0;   //set all the bits of 0A and 0B register to  0
    TCCR0B = 0;
    TCNT0 = 0;    //TCNT register is a timer counter register, the value of this register increases on every TICK, TICK is time taken by 1 instruction cycle
    OCR0A = 10;                            //OCR is a output compare register, TCNT register value is compared with this register
    TCCR0A |= 1 << WGM01;                   //Turn on CTC mode: clear on compare. Turn TCNT to 0 if TCNT and OCR reg value matches
    TCCR0B |= (1 << CS01) | (1 << CS00);    //Set the prescaler value to 64
    TIMSK0 |= 1 << OCIE0A;                  //Generate the interrupt on compare
  
    sei();        //activate interrupts

    pinMode(LED_PIN, OUTPUT);
    pinMode(PWM_KEY, INPUT);
}

ISR(TIMER0_COMPA_vect)  {                   //Interrupt service routine of Timer0 interrupt
    static byte duty;
    
    if ( duty <= T_on )                   //if duty is less than T_on value 
        digitalWrite(LED_PIN, HIGH);      //turn the LED on

    else
        digitalWrite(LED_PIN, LOW);

    if ( duty++ == PERIOD )                //if incremented duty value matches with PERIOD value go to this block
        duty = 0;                          //turn the duty value to 0 every period
}

void loop()  {                  //loop function codes run repeatedly
    static unsigned wait;
    static bool key;

    if ( wait++ == 0x15FF ) {           //detect the keypress on in few milli seconds of delay
        key = digitalRead(PWM_KEY);
        wait = 0;                       //set wait back to 0
    }
    
    if ( key )  {                       //if key is active
        if ( T_on++ == PERIOD )         //post increment T_on value 1
            T_on = 0;                   //if it matches with PERIOD turn it back to 0
            
        key = 0;                        //set the key to 0 to not to increase the T_on value if key is not pressed
    }
}
