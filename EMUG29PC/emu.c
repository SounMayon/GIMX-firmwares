/*
 Copyright (c) 2026 GIMX Reborn-ffb
 License: GPLv3
 */

#include "../adapter_common.c"

static const uint8_t PROGMEM feature_buf[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void EVENT_USB_Device_ControlRequest(void)
{
    static uint8_t buffer[MAX_CONTROL_TRANSFER_SIZE];

    switch (USB_ControlRequest.bRequest)
    {
    case REQ_SetIdle:
        if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
        {
            Endpoint_ClearSETUP();
            Endpoint_Read_Control_Stream_LE(buffer, USB_ControlRequest.wLength);
            Endpoint_ClearIN();
        }
        break;
    case REQ_GetReport:
        if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
        {
            uint8_t reportType = USB_ControlRequest.wValue >> 8;
            if (reportType == REPORT_TYPE_FEATURE)
            {
                uint16_t len = USB_ControlRequest.wLength < sizeof(feature_buf)
                    ? USB_ControlRequest.wLength
                    : sizeof(feature_buf);
                Endpoint_ClearSETUP();
                Endpoint_Write_Control_PStream_LE(feature_buf, len);
                Endpoint_ClearOUT();
            }
        }
        break;
    case REQ_SetReport:
        if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
        {
            if (USB_ControlRequest.wLength > sizeof(buffer))
            {
                Endpoint_StallTransaction();
                break;
            }
            Endpoint_ClearSETUP();
            Endpoint_Read_Control_Stream_LE(buffer, USB_ControlRequest.wLength);
            Endpoint_ClearIN();
        }
        break;
    }
}
