#include <Wire.h>
#include <Arduino.h>
#include "ds1307.h"

char Day[][10] = {"#", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void DS1307 :: init_i2c_n_serial_comm() {
    Serial.begin(9600);
    Wire.begin(); 
}

void DS1307 :: display_time() {
    BYTE t_reg[7];
    read_from_rtc(t_reg, SEC_ADDR, sizeof(t_reg));
    
    if ( t_reg[2] & _12_HR_MODE_ )        //condition to display in 12 hr mode if HR_ADDR bit 6 is high
        sprintf(time_buffer, "%.2x:%.2x:%.2x %s, %s %.2x/%.2x/20%.2x", t_reg[HR_ADDR] & _12_TIME_, t_reg[MIN_ADDR], t_reg[SEC_ADDR] & SEC_VAL, 
                                                                       t_reg[HR_ADDR] & AM_PM ? "PM" : "AM", Day[t_reg[DAY_ADDR]],
                                                                       t_reg[DATE_ADDR], t_reg[MONTH_ADDR], t_reg[YEAR_ADDR]);
    else          //24 hr format          //print as 2 digit hexadecimal format
        sprintf(time_buffer, "%.2x:%.2x:%.2x, %s %.2x/%.2x/20%.2x", t_reg[HR_ADDR], t_reg[MIN_ADDR], t_reg[SEC_ADDR] & SEC_VAL, Day[t_reg[DAY_ADDR]],
                                                                    t_reg[DATE_ADDR], t_reg[MONTH_ADDR], t_reg[YEAR_ADDR]);
    Serial.println(time_buffer);      //print time to serial monitor
}

void DS1307 :: set_time(char *current_time) {       //set the time
    BYTE time_reg_arr[7], temp;
    BYTE i = 0;
    
    char *token = strtok(current_time, ", -/:");    //break the string to tokens to get time information invidually

    while ( token != NULL )                         //run the loop until the conditon satisfies
    {
        if ( !strcmp(token, "AM") )                 //if AM is detected activate 12 hr mode(bit 6) and disable bit 5 oh HR_ADDR 
            time_reg_arr[0] |= AM;

        else if ( !strcmp(token, "PM") )
            time_reg_arr[0] |= PM;                  //bit 6 high and bit 5 high for HR_ADDR for PM

        else
        {
            if ( i != 3 )                           //if it is not equal to Day
                time_reg_arr[i] = DEC_2_BCD(atoi(token));       //convert decimal to bcd

            else                                    //for 3rd day field
            {
                for( int j = 1; j < 8; j++ )        //compare the day entered by user with day array
                {
                    if ( !strcmp(token, Day[j]) )
                        time_reg_arr[3] = j;        //if found set the day number as BCD
                }
            }
            i++;
        }

        token = strtok(NULL, ", -/:");              //check for next token
    }

    temp = time_reg_arr[2];
    time_reg_arr[2] = time_reg_arr[0];              //swap HR and SEC array indexes
    time_reg_arr[0] = temp | CLK_HLT;               //activate CH bit in SEC_ADDR to stop the clock

    write_2_rtc(time_reg_arr, SEC_ADDR, sizeof(time_reg_arr));      //function call to write to RTC
}

void DS1307 :: clock_ticks(BYTE state) {              //function def to start and stop the clock
    BYTE temp[1];
    read_from_rtc(temp, SEC_ADDR, 1);                 //get the value from sec address
    
    if ( state )
        temp[0] |= CLK_HLT;                           //activate CH bit

    else
        temp[0] &= CLK_STRT;                          //else deactivate CH bit
        
    write_2_rtc(temp, SEC_ADDR, 1);
}

void DS1307 :: write_2_rtc(BYTE *time_reg_arr, BYTE start_add, BYTE total_bytes)  {
    Wire.beginTransmission(RTC_ID);                   //transmit to transmit data to RTC device
    Wire.write(start_add);                            //address to start writing from
    
    for ( BYTE i = 0; i < total_bytes; i++ )
        Wire.write(time_reg_arr[i]);                  //write data as per the number of bytes
                                                      //address will automatically increment
    Wire.endTransmission();
}

void DS1307 :: read_from_rtc(BYTE *time_reg_arr, BYTE start_add, BYTE total_bytes)  {
    Wire.beginTransmission(RTC_ID);                   //read from rtc
    Wire.write(start_add);                            //enter the address to start reading from that address
    Wire.endTransmission();
    Wire.requestFrom(RTC_ID, total_bytes);            //repeat start for 7 cycles read 7 bytes from the entered address

    for ( BYTE i = 0; i < total_bytes; i++ )
        time_reg_arr[i] = Wire.read();                //read and store to the array
}

BYTE DS1307 :: DEC_2_BCD(BYTE num)  {                 //convert decimal input to bcd as RTC store the time in BCD format
    return ((num / 10) << 4) | (num % 10);
}

BYTE DS1307 :: format_check(char *time)               //function to check the time format if entered through serial monitor
{
    char time_cpy[35];

    strcpy(time_cpy, time);                           //copy the entered time to a new string
    
    //symbol separator verification
    if ( time_cpy != NULL ) 
    {
        if ( strlen(time_cpy) > 20 )
        {
            if ( time_cpy[2] == time_cpy[5] && time_cpy[2] == ':' && time_cpy[8] == ',' )       //hr/min/sec separator check
            { /*success*/ }

            else
                return 0;
        }   
        else
            return 0;
    }
    else
        return 0;                                 //return 0 if conditon fails

    char *date = strstr(time_cpy, "day");

    if ( date != NULL )
    {
        if ( strlen(date + 4) == 8 )              //4 is added to move to date pos as using strstr day we will get like: day DD/MM/YY
        {
            if ( *(date + 6) == *(date + 9) && ( *(date + 6) == '/' || *(date + 6) == '-' ) )   //dd/mm/yy separator check 
            { /*success*/ }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;

    
    //total tokens verification
    char *token;
    BYTE token_count = 0;
    BYTE token_vals[7];
    char day_val[10];

    token = strtok(time_cpy, ", -/:");

    while ( token != NULL ) 
    {
        if ( token_count != 3 )
            token_vals[token_count] = atoi(token);
        
        else                                                  //calc total tokens and set the values to new array to store as integer
            strcpy(day_val, token);                           //store day string

        token = strtok(NULL, ", -/:");
        token_count++;
    }

    
    if ( token_count == 7 )
    { /*success*/ }
    else
        return 0;
                                  //change if entered range for all is valid
    if (token_vals[0] >= 0 && token_vals[0] <= 23 )                             //hrs
    {   
        if ( token_vals[1] >= 0 && token_vals[1] <= 59 )                        //mins
        {
            if ( token_vals[2] >= 0 && token_vals[2] <= 59 )                    //secs
            {
                if ( token_vals[4] >= 1 && token_vals[4] <= 31 )                //date
                {
                    if ( token_vals[5] >= 1 && token_vals[5] <= 12 )            //month
                    {
                        if ( token_vals[6] >= 0 && token_vals[6] <= 99 )        //year
                        {
                            for ( byte i = 1; i <= 7; i++ )                     //day
                            {
                                if ( !strcmp(day_val, Day[i]) )                 //if day found break the loop
                                    break;
                                
                                if ( i == 7 )
                                    return 0;
                            } 
                        }
                        else
                            return 0;
                    }
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;

    return 1;                                   //if control reaches successfully, the enterd format is valid
}
