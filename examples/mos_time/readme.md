### Demonstrates use of MOS time functionality

    
    printf("- mos_getrtc command: correct to nearest second\r\n");
    printf("- sysvar_time: centi-seconds updated by 2 on vsync\r\n");
    printf("- sysvar_rtc: updated every second from VDP\r\n\r\n");

- `mos_getrtc` command: correct to nearest second

- `sysvar_time`: centi-seconds updated by 2 on vsync

- `sysvar_rtc`: updated every second from VDP

`Sysvar_rtc `returns a pointer to the rtc data which is updated dynamically by MOS, and consequently needs to be declared as dynamic to avoid optimisations.

The format is of the data is contained in the mos_api.h

```
typedef union {
    uint64_t rtc_data;
    struct {
        uint8_t year;               // offset since 1980
        uint8_t month;              // (0-11)
        uint8_t day;                // (1-31)
        uint8_t day_of_year;        // (0-365) - wraps after 255
        uint8_t day_of_week;        // (0-6)
        uint8_t hour;               // (0-23)
        uint8_t minute;             // (0-59)
        uint8_t second;             // (0-59)
    };
} RTC_DATA;

```

There is a bug that the `day_of_year` field is not sufficiently large and the field will wrap on 13/14th September.
