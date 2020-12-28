/*
 * Author Name    : Badrikesh Prusty
 * Organisation   : Emertxe Information Technologies (P) Ltd.
 * Date           : 30/08/2020
 * Description    : Write an Arduino program to implement 5 level timer based PWM LED dimmer
 * Input          : Press the button to increse the brightness by 20%
 * Output         : LED brightness increases by 20% on every keypress after 100% if key is pressed it turns off and cycle continues
 */

#define PWM_KEY   2
#define LED_PIN   4
#define PERIOD    250

static byte T_on;

void setup() {
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

    
    pinMode(PWM_KEY, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

ISR(TIMER0_COMPA_vect)  {                   //Interrupt service routine of Timer0 interrupt
    static byte duty;
    
    if ( duty <= T_on )                   //if duty is less than equal to T_on value
        digitalWrite(LED_PIN, HIGH);      //turn the LED on

    else                                  //of more then turn off the LED
        digitalWrite(LED_PIN, LOW);

    if ( duty++ == PERIOD )                //if incremented duty value matches with PERIOD value go to this block
        duty = 0;                          //turn the duty value to 0 every period
}

void loop() {                         //code within loop function runs infinite number of times in a loop
    static bool key, key_flag;

    key = digitalRead(PWM_KEY);       //check for keypress
    
    if ( key && key_flag )  {         //don't increase T_on by more than 50 if key is pressed for long enough time
        key_flag = 0;

        if ( T_on >= PERIOD )
            T_on = 0;                 //turn the T_on back to 0 if it is equal to PERIOD
        
        else
            T_on += 50;               //else increment by 50 if the key is pressed
    }

    else if ( !key && !key_flag )     //keypress flag to stop detecting the keypress until next time key is pressed
        key_flag = 1;
}
