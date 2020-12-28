#ifndef DS1307_H
#define DS1307_H

#define RTC_ID        0x68

#define SEC_ADDR      0x00
#define MIN_ADDR      0x01
#define HR_ADDR       0x02
#define DAY_ADDR      0x03
#define DATE_ADDR     0x04
#define MONTH_ADDR    0x05
#define YEAR_ADDR     0x06

#define AM            0x40
#define PM            0x60
#define _12_HR_MODE_  0x40
#define AM_PM         0x20
#define _12_TIME_     0x1F
#define SEC_VAL       0x7F

#define CLK_HLT       0x80
#define CLK_STRT      0x7F

typedef unsigned char BYTE;

class DS1307  {
    char time_buffer[35];
    BYTE DEC_2_BCD(BYTE NUM);
    void write_2_rtc(BYTE *time_reg_arr, BYTE start_add, BYTE total_bytes);
    void read_from_rtc(BYTE *time_reg_arr, BYTE start_add, BYTE total_bytes);

    public:
        void init_i2c_n_serial_comm();
        void set_time(char *current_time);
        void display_time();
        void clock_ticks(BYTE state);
        BYTE format_check(char *time);
};

#endif
