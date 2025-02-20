#include "MiniGamepad.h"

#include <hid_def.h>

#include "Custom-HID.h"
#include "IDs.h"

static const uint8_t _hidMultiReportDescriptorMiniGamepad[] PROGMEM = {
    /* Gamepad with 10 buttons and 2 axis*/
    HID_USAGE_PAGE(GENERIC_DESKTOP),
    HID_USAGE(JOYSTICK),
    HID_COLLECTION(APPLICATION),
    HID_REPORT_ID(HID_REPORTID_MINI_GAMEPAD),

    /* 16 Buttons */
    HID_USAGE_PAGE(BUTTONS),
    HID_USAGE_MINIMUM(1, 1),
    HID_USAGE_MAXIMUM(1, 10),
    HID_LOGICAL_MINIMUM(1, 0),
    HID_LOGICAL_MAXIMUM(1, 1),
    HID_REPORT_SIZE(1),
    HID_REPORT_COUNT(16),
    HID_INPUT(DATA, VARIABLE, ABSOLUTE),

    /* 2 16bit Axis */
    HID_USAGE_PAGE(GENERIC_DESKTOP),
    HID_COLLECTION(PHYSICAL),
    HID_USAGE(X),
    HID_USAGE(Y),
    HID_LOGICAL_MINIMUM(2, -32768),
    HID_LOGICAL_MAXIMUM(2, 32767),
    HID_REPORT_SIZE(16),
    HID_REPORT_COUNT(2),
    HID_INPUT(DATA, VARIABLE, ABSOLUTE),

    HID_END_COLLECTION(PHYSICAL),
    HID_END_COLLECTION(APPLICATION),
};

MiniGamepad_::MiniGamepad_(void) {
    static HIDSubDescriptor node(_hidMultiReportDescriptorMiniGamepad,
                                 sizeof(_hidMultiReportDescriptorMiniGamepad));

    CustomHID().AppendDescriptor(&node);

    report.vol_x = report.vol_y = report.buttons = 0;
    last_report.vol_x = last_report.vol_y = last_report.buttons = 0;
}
void MiniGamepad_::SendReport(void* data, int length) {
    CustomHID().SendReport(HID_REPORTID_MINI_GAMEPAD, data, length);
}
void MiniGamepad_::write(void) {
    if (last_report.vol_x != report.vol_x || last_report.vol_y != report.vol_y ||
        last_report.buttons != report.buttons) {
        SendReport(&report, sizeof(report));

        last_report.buttons = report.buttons;
        last_report.vol_x = report.vol_x;
        last_report.vol_y = report.vol_y;
    }
}
void MiniGamepad_::begin(void) { return; }

MiniGamepad_ MiniGamepad;
