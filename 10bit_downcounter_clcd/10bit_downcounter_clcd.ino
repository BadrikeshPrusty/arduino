/*
 * Author Name      : Badrikesh Prusty
 * Organisation     : Emertxe Information Technologies (P) Ltd.
 * Date             : 17/08/2020
 * Description      : Write an Arduino program to implement 10-bit Down-Counter such that it counts from 9999999999 to 000000000 in CLCD
 * Input            : No user input required
 * Output           : In CLCD:
 *                    9999999999                    (count increments every 250ms)
 *                    9999999998
 *                    .
 *                    .
 *                    0000000000
 *                    9999999999
 */

#include "main.h"
#include "clcd.h"

CLCD clcd(D0, D1, D2, D3, D4, D5, D6, D7, RS, EN);        //creating class object and passing all the PIN numbers LCD is connected to

void setup() {      //code in the setup function run only once
    clcd.begin();   //calling begin function that initializes all the pins and lcd
    clcd.print("10BitDownCounter", LINE_1(0));            //printing the first line of the LCD
}

void loop() {     //code with the loop function runs multiple times
    static char counter[11];         //counter string to store counter value
    static unsigned lower = 9999, upper = 9999;    //lower and upper denotes the last(from LSB) and first(from MSB) 4 bits of count 
    static byte mid = 99;                 //mid denotes middle 2 bits

    sprintf(counter, "%.4u%.2hhu%.4u", upper, mid, lower);    //creating a string of counter
    clcd.print(counter, LINE_2(3));                           //printing the counter string value to LCD

    if ( lower-- == 0 )  {           //if lower reaches 0, revert it back to 9999 and increment the mid
      lower = 9999;
      
        if ( mid-- == 0 )  {           //if mid reaches 0 revert back to 99 and increment upper
            mid = 99;
  
            if ( upper-- == 0 )      //if upper reaches 0 revert it back to 9999 to restart the count again
              upper = 9999;
        }
    }
    delay(250);                 //wait for 250ms between the count increments 
}
