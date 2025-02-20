#pragma once

#include <HID.h>
#include <vendor.h>

typedef struct ATTRIBUTE_PACKED {
    uint16_t buttons;
    int16_t vol_x;
    int16_t vol_y;
} HID_MiniGamepadReport_Data_t;

class MiniGamepad_ {
   public:
    HID_MiniGamepadReport_Data_t report;
    HID_MiniGamepadReport_Data_t last_report;

    MiniGamepad_(void);
    void SendReport(void* data, int length);
    void write(void);
    void begin(void);
};

extern MiniGamepad_ MiniGamepad;
