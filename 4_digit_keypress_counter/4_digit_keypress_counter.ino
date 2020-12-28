/*
 * Author Name  : Badrikesh Prusty
 * Organisation : Emertxe Information Technologies (P) Ltd.
 * Date         : 06/08/2020
 * Description  : Write an Arduino program to implement a 4 digit counter that counts from 0000 to 9999 on button press,
                  and for button press and hold it should reset the counter and start a new counter.
 * Input        : Press the Push Button to increment the counter. To reset the counter press and hold the push button until the counter resets.
 * Output       : 
 *                Press the PUSH BUTTON to Initialize the Counter...                                    (button press)
 *                0000                                                                                  (button press)
 *                0001                                                                                  (button press and hold)
 *                0002
 *                
 *                Counter Reset Successful
 *                
 *                New Counter Started
 *                0000                                                                                  (hold button released)
 */
 
#define PUSH_BUTTON 4                     //defining macro for push button and such a value that it is connected to that pin of Arduino
#define RESET_TIME 0x7FFFF                //microcontroller counts upto this value to generate a delay

void setup() {                            //Setup function code only runs once
    Serial.begin(9600);                   //beginning serial communication at a buad rate of 9600
    pinMode(PUSH_BUTTON, INPUT);          //defining pin that the push button is connected to as input
    Serial.println("Press the PUSH BUTTON to Initialize the Counter...");     //display the following message on serial monitor
}

void loop() {                                             //loop() function code runs infinite number of times
    static bool key, button_flag = 1, reset_flag = 0;     //key to check button state, buuton_flag: to mask the button if it is set to 0
    static int counter = 0;                               //reset_flag if set to 1 unmasks the reset property of counter
    static unsigned long hold_time = 0;                   //this is used for delay if switch is pressed and hold
    static char counter_str[5];                           //declare counter string array to hold 4 digit counter

    key = digitalRead(PUSH_BUTTON);                       //checking the button state and assigning it to key
  
    if ( key && button_flag )  {                //if key press and button_flag is not masked then go to this block
        sprintf(counter_str, "%.4d", counter);  //assign counter var value as a 4 digit to counter_str
        Serial.println(counter_str);            //print the counter value 
        
        counter++;                          //post increment by 1
        hold_time = 0;                      //to increment the hold_time from 0 everytime the button is pressed
        button_flag = 0;                    //masking button_flag such that it doesn't enter this block until and unless it is released
    
        if ( counter > 1 )  {               //if counter is greater than 1 go to this block
            if ( counter > 9999 )
                counter = 0;                    //if greater than 9999 change the counter to 0
            else
                reset_flag = 1;                 //if counter lies between 2 and 9999 activate the reset_flag that adds the ability to reset the counter 
        }    
        else                                //if counter less than equal to 1
            reset_flag = 0;                   //remove the ability to reset the counter. After reset if button is pressed and hold it shouldn't reset
    }
  
    else if ( key == 0 && button_flag == 0 ) {    //if key depressed. Activate the button flag and mask the reset flag
        button_flag = 1;
        reset_flag = 0;
    }

    if ( reset_flag )  {                          //if reset_flag is unmasked goto this block
        hold_time++;                                //increment the hold time everytime the loop runs
        if ( hold_time >= RESET_TIME )  {           //if the hold time matches and becomes greater than defined reset value goto this block
            Serial.println("\nCounter Reset Successful\n\nNew Counter Started");
            counter = 0;                              //reset the counter and unmask the button flag
            button_flag = 1;
        }
    }
}
