/*
 * Author Name  : Badrikesh Prusty
 * Organisation : Emertxe Information Technologies (P) Ltd.
 * Date         : 05/08/2020
 * Description  : Write an Arduino program to implement 8 field password matcher such that a user is provided 3 tries to enter 
                  enter the correct password. If user enters within 3 successful trials print password successful else lock the
                  password entering capability if all the 3 trial fails.
 * Input        : Enter the correct password and press enter within 3 tries.
 * Output       : 
 *                NOTE: You have only 3 tries left

                  Enter Password: ********
                  
                  INFO: You have entered correct password
                  Password Successful
 */

char curr_pass[] = "hellohie";          //current password

void setup() {                          //code written within void function runs only once and this function can be called by loop function
    Serial.begin(9600);                 //start the serial communication at the baud rate of 9600
}

void loop() {                         //loop function runs infinite number of times util next power off
    static char get_char;               //get_char variable to get the character from the sent command from serial monitor
    static bool try_flag = 1, match = 1;//match variable to check matching character by character. match fails if it is 0
    static byte i = 0, tries = 3;       //i for index value, tries number of times user gets chance to enter the password  
    
    get_char = Serial.read();           //Read the string character by character from the serial monitor and assign it to variable 
    
    if ( get_char != -1 && get_char != '\n' ) {           //if the password not entered or enter is pressed do not go to this block
          if ( curr_pass[i] != get_char )                 //if the password doesn't match with current index of current password set
                  match = 0;                              //match to 0 this will denote match failure.
          i++;                                            //increment current_pass index by 1 to compare with the next character entered
          Serial.write("*");                              //Enter convert entered characters to * for protecting the original password
    }

    else if ( get_char == '\n' )  {                    //if get_char  == '\n' go to this block
        if ( i != strlen(curr_pass) )
            match = 0;                                    //unset match if length of cur_pass doesn't match with i value
        
        if ( i == 0 )                                    //if enter or send button is pressed and password not entered goto this block
            Serial.println("\n\nERROR: Password not entered. Please enter the password");
    
        else  {                           //goto this block if length of password is equal to 8
            if ( match == 1 )  {                          //if matches go to this block
                Serial.println("\n\nINFO: You have entered correct password\n**PASSWORD SUCCESSFUL**");
                Serial.end();                               //print the messages and end the serial communication
            }
      
            else
                Serial.println("\n\nERROR: You have entered incorrect password.");
        }
      
        try_flag = 1;                             //activate try_flag to check how many tries left
    }
    
    if ( try_flag )  {                        //go to this block if try flag is 1
        if ( i != 0 ) {                       //if length of password is 0 don't don't go to this block
            tries--;                          //decrement number of tries everytime setup function is 
            i = 0;                            //change the array index value to 0
            match = 1;                        //match value to 1. if match got unset due to failed comparison
        }
      
        if ( tries != 0 ) {                 //if tries is not 0 give user another try
            Serial.print((String)"\nNOTE: You have only "+tries+" tries left"); //showing remaining tries
            Serial.print("\n\nEnter Password: ");               //print the message
        }
        
        else  {                                       //if tries left is 0
            Serial.println("\nERROR: You have entered incorrect password three times\n**PASSWORD LOCKED**");
            Serial.end();                               //end the serial communication
        }
        try_flag = 0;                                 //disable the try flag
    }
}
