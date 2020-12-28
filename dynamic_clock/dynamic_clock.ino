/*
 * Author Name    : Badrikesh Prusty 
 * Organisation   : Emertxe Information Technologies (P) Ltd.
 * Date           : 29/08/2020
 * Description    : To implement a dynamic clock such that on pressing or should stop/start the clock and if clock is stopped ask user to enter the time to update 
 * Input          : Push the button to stop/start the clock. if clock is stopped enter the new time in correct format to update the clock   
 */
 
 #include "main.h"

void setup() {                                            //code within setup function run only once
    pinMode(START_STOP_KEY, INPUT);                       //input key to start or stop the clock
    ds1307.init_i2c_n_serial_comm();                      //start i2c and serial communication
    
    strcpy(time_str, "11:59:50, Tuesday 25/08/20"); 
    ds1307.set_time(time_str);
    ds1307.clock_ticks(START);                            //set the time and start the clock ticks
}

void loop() {                                             //code within loop function run infinite times
    static bool key, key_flag, state, msg_flag;
    static unsigned long wait;
    static char get_char; static byte i;

    key = digitalRead(START_STOP_KEY);            //read the button input

    if ( key && key_flag )  {                     //if button is pressed go to this block
        key_flag = 0;
        state = !state;
        ds1307.clock_ticks(state);                //if clock is running stop it or vice versa 

        if ( state == 1 )
            msg_flag = 0;                         //if clock is stopped activate the message flag to display the message
    }

    else if ( !key && !key_flag )                 //this avoids keypress detection if pressed for long enough time
        key_flag = 1;

    if ( !state )  {                              //if clock is running go to this block to display the time
        if ( wait++ == 0x2FFFF ) {                //this wait count gives a time delay of 1 sec
            ds1307.display_time();
            wait = 0;
        }
    }

    else if ( state ) {                           //if clock is not running go to this block
        if ( !msg_flag )  {                       //display the message only once
            Serial.println("Press the key/enter to continue or Enter new time");
            Serial.println("Using this format: HH:MM:SS, Monday DD/MM/YY or DD-MM-YY");
            msg_flag = !msg_flag;
            i = 0;
        }
        get_char = Serial.read();                   //read the characters entered through serial monitor

        if ( get_char != -1 && get_char != '\n' ) {
            Serial.print(get_char);
            time_str[i++] = get_char;               //store it in time string array
        }
        
        else if ( get_char == '\n' )  {
            if ( !i ) {                             //if nothing entered and entered is pressed start the clock
                state = !state;                     //from current position
                ds1307.clock_ticks(state);
                Serial.println();
            }
            
            else {
                time_str[i] = '\0';                 //if string length is greater than 0 terminate the string using null
                
                if ( ds1307.format_check(time_str) )  {     //if format is successfully validated
                    ds1307.set_time(time_str);              //set the time and start the clock
                    state = !state;
                    ds1307.clock_ticks(state);
                }

                else  {                                     //if format is invalid go to this block
                    Serial.println();                       //to ask the user to enter again
                    Serial.println("Entered time format is invalid. Please try again!!");
                    msg_flag = 0;
                }
                    
                i = 0;
            }
            Serial.println();
        }
    }
}
