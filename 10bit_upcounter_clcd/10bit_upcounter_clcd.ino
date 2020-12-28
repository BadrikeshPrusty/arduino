/*
 * Author Name      : Badrikesh Prusty
 * Organisation     : Emertxe Information Technologies (P) Ltd.
 * Date             : 17/08/2020
 * Description      : Write an Arduino program to implement 10-bit Up-Counter such that it counts from 0000000000 to 9999999999 in CLCD
 * Input            : No user input required
 * Output           : In CLCD:
 *                    0000000000                    (count increments every 250ms)
 *                    0000000001
 *                    .
 *                    .
 *                    9999999999
 *                    0000000000
 */

#include "main.h"
#include "clcd.h"

CLCD clcd(D0, D1, D2, D3, D4, D5, D6, D7, RS, EN);        //creating class object and passing all the PIN numbers LCD is connected to

void setup() {      //code in the setup function run only once
    clcd.begin();   //calling begin function that initializes all the pins and lcd
    clcd.print("10-bit UpCounter", LINE_1(0));            //printing the first line of the LCD
}

void loop() {     //code with the loop function runs multiple times
    static char counter[11];         //counter string to store counter value
    static unsigned lower, upper;    //lower and upper denotes the last(from LSB) and first(from MSB) 4 bits of count 
    static byte mid;                 //mid denotes middle 2 bits

    sprintf(counter, "%.4u%.2hhu%.4u", upper, mid, lower);    //creating a string of counter
    clcd.print(counter, LINE_2(3));                           //printing the counter string value to LCD

    if ( lower++ == 9999 )  {           //if lower reaches 9999, revert it back to 0 and increment the mid
      lower = 0;
      
        if ( mid++ == 99 )  {           //if mid reaches 99 revert back to 0 and increment upper
            mid = 0;
  
            if ( upper++ == 9999 )      //if upper reaches 9999 revert it back to 0 to restart the count again
              upper = 0;
        }
    }
    delay(250);                 //wait for 250ms between the count increments 
}
