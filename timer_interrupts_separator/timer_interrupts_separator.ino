/*
 * Author Name      : Badrikesh Prusty
 * Organisation     : Emertxe Information Technologies (P) Ltd.
 * Date             : 11/08/2020
 * Description      : Write an Arduino program to implement timer interrupts separator using LEDs for each timer and toggle the LEDs
                      on its own interrupt generation such that it blinks every half second, simultanously.
 * Input            : No input from the user required
 * Output           : All three LEDs blinks every every half second synchronously.
 */

#define LED0 11     //defining macros for LEDs as pin numbers
#define LED1 12
#define LED2 13

void setup() {              //setup function codes executes only once
    cli();        //deactivate interupts to avoid accidental generation of interrupts while configuring
  
    //Timer0
    TCCR0A = 0;                               //clear all bits of 0A and 0B register
    TCCR0B = 0;
    TCNT0 = 0;                                //initialize Timeer counter register from 0. This reg value increments with every tick
    OCR0A = 249;                              //output compare register is used to compare its value with TCNT register value
    TCCR0A |= 1 << WGM01;                     //Turn on CTC mode, clear on compare mode if TCNT matches with output compare reg
    TCCR0B |= (1 << CS01) | (1 << CS00);      //Set the prescaler to 64
    TIMSK0 |= 1 << OCIE0A;                    //generate the interrupts on compare
  
    //Timer1
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;                                //initial timer counter value 0
    OCR1A = 249;
    TCCR1B |= 1 << WGM12;                     //turn on CTC mode
    TCCR1B |= (1 << CS11) | (1 << CS10);      //set prescaler to 64
    TIMSK1 = 1 << OCIE1A;                     //generate the interrupts on compare
  
    //Timer2
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;                                //initial timer counter register to 0
    OCR2A = 249;
    TCCR2A |= 1 << WGM21;                     //turn on CTC mode
    TCCR2B |= (1 << CS22);                    //set prescaler to 64
    TIMSK2 = 1 << OCIE2A;                     //generate the interrupt on compare
  
    sei();    //activate interrupts
  
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);      //intitialize led pins
    pinMode(LED2, OUTPUT);
}

ISR(TIMER0_COMPA_vect)  {                     //interrupt service routine of Timer0 interrupt
    static unsigned count0;
    static bool SW0;
    if ( ++count0 == 500 )  {                   //increment the counter every time the interrupt is generated
        count0 = 0;                             //if interrupt is generated every 1ms increment the count value by 1
        SW0 = !SW0;                             //such that on 500ms it act/deact the switch and turn the counter to 0
        digitalWrite(LED0, SW0);
    }
}

ISR(TIMER1_COMPA_vect)  {                          //interrupt service routine of Timer1 interrupt
    static unsigned count1;
    static bool SW1;
    if ( ++count1 == 500 )  {                    //increment with every 1msec interrupt generation
        count1 = 0;                              //turn count value to 0
        SW1 = !SW1;                              //turn on/off switch
        digitalWrite(LED1, SW1);
    }
}

ISR(TIMER2_COMPA_vect)  {                       //interrupt service routine of Timer2 interrupt
    static unsigned count2;
    static bool SW2;
    if ( ++count2 == 500 )  {                   //increment with every 1msec interrupt generation
        count2 = 0;                             //turn count value to 0
        SW2 = !SW2;                             //turn on/off switch
        digitalWrite(LED2, SW2);
    }
}

void loop() {
}
