/*
 * Author Name    : Badrikesh Prusty
 * Organisation   : Emertxe Information Technologies (P) Ltd.
 * Date           : 13/08/2020
 * Description    : Write an Arduino program to implement a static clock and with time format: HH:MM:SS
 * Input          : No user input required
 * Output         : 00:00:00
 *                  00:00:01
 *                  00:00:02
 */

bool toggle;

void setup() {              //code in setup function only runs once
    Serial.begin(9600);     //begin serial communication @9600 baud rate
    
    cli();        //deactivate interupts for any generation of interrupt while configuring 
  
    //Timer0
    TCCR0A = 0;   //set all the bits of 0A and 0B register to  0
    TCCR0B = 0;
    TCNT0 = 0;    //TCNT register is a timer counter register, the value of this register increases on every TICK, TICK is time taken by 1 instruction cycle
    OCR0A = 249;                            //OCR is a output compare register, TCNT register value is compared with this register
    TCCR0A |= 1 << WGM01;                   //Turn on CTC mode: clear on compare. Turn TCNT to 0 if TCNT and OCR reg value matches
    TCCR0B |= (1 << CS01) | (1 << CS00);    //Set the prescaler value to 64
    TIMSK0 |= 1 << OCIE0A;                  //Generate the interrupt on compare
  
    sei();      //activate interrupts
}

ISR(TIMER0_COMPA_vect)  {                   //Interrupt service routine of Timer0 interrupt
    static unsigned count;                  //whenever timer0 interrupt is generated codes written in this gets executed
    if ( ++count == 1000 )  {               //As interrupt is generated every 1ms, incrementing count value to 1000 will generate 1 sec delay
        count = 0;
        toggle = 1;                         //activating toggle value to print the time in loop function
    }
}

void loop()  {                  //loop function codes run repeatedly
    static byte hr, mint, sec;
    static char clock_time[9];  //declaring char array to store the time in form of character array
    
    if ( toggle ) {                             //if toggle gets activated in interrupt go to this block
        sprintf(clock_time, "%.2d:%.2d:%.2d", hr, mint, sec);     //store the time in the form of string in clock_time array
        Serial.println(clock_time);                               //print the time in serial monitor
      
        if ( ++sec == 60 ) {                    //increment sec value goto this block every 60 seconds
            sec = 0;
            
            if ( ++mint == 60 ) {               //pre increment minute value and go to this block every 60 minutes
                mint = 0;

                if ( ++hr == 24 )               //increment hour value and go to this block every every 24 hours
                    hr = 0; 
            }
        }
        toggle = 0;                             //disable toggle flag
    }
}
