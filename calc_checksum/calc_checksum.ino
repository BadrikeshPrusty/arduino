/*
 * Author Name    : Badrikesh Prusty
 * Organisation   : Emertxe Information Technologies (P) Ltd.
 * Date           : 20/08/2020
 * Description    : Write and Arduino program to implement a checksum to calculate odd and even parity of an ASCII character or 8 bit data 
 * Input          : Enter 8 bit data or a single ASCII character
 * Output         : 
 *                  Enter an ASCII character or 8 bit data to check it's parity: 10100010 
 *                  INFO: Even parity. Number of 0s is even
 *                  
 *                  Enter an ASCII character or 8 bit data to check it's parity: C
 *                  INFO: Odd parity. Number of 1s is odd
 */

void setup() {      //code in setup function run only once
    Serial.begin(9600);         //begin serial communication at 9600 baud rate
    Serial.print("Enter an ASCII character or 8 bit data to check it's parity: ");
}

void loop() {       //code in loop function runs infinite number of times
    static char get_char, byte_char;
    static bool error_flag;
    static byte bit_count, count_1;

    get_char = Serial.read();       //read from the serial monitor

    if ( get_char != -1 && get_char != '\n' ) {   //check if any input is given or not other than newline character
        if ( get_char == '1' )
            count_1++;                            //increment if 1 is detected
        
        else if ( get_char != '0' && get_char != '1' )    //raise the error flag if bits other than 1 or 0 is entered
            error_flag = 1;                                 //if number of characters is greater than 1
        
        Serial.print(get_char);
        
        if ( ++bit_count == 1 )
            byte_char = get_char;                           //assign the first character to a variable
    }

    else if ( get_char == '\n' )  {                         //go to this block if user presses enter

        if ( bit_count == 1 ) {                             //if only 1 character is entered consider it as an ascii character
            count_1 = 0;
            error_flag = 0;                                 //reset the flag as it got set due to entered character diff from 1 or 0
            for ( byte i = 0; i < 8; i++ )  {
                if ( (byte_char >> i) & 1 )                 //calculate the number of 1s
                    count_1++;
            }
        }

        if ( !error_flag )  {                     //if error flag is low go to his block
            if ( bit_count == 8 || bit_count == 1 ) {
                if ( count_1 % 2 )                //for odd number of 1s go to this block
                    Serial.println("\nINFO: Odd parity. Number of 1s is odd");
    
                else
                    Serial.println("\nINFO: Even parity. Number of 0s is even");
            }
    
            else
                Serial.println("\nERROR: Number of data bits entered is not equal to 8");
        }

        else
            Serial.println("\nERROR: Invalid data bits format. Value other than 1s or 0s is entered");
        bit_count = 0;
        error_flag = 0;                           //reset all flags, bit, count for the next input
        count_1 = 0;
        Serial.print("\nEnter an ASCII character or 8 bit data to check it's parity: ");
    }
}
