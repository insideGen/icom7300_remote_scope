#include <stdio.h>
#include "ic7300.h"

struct scope_waveform_data_tag x;

const unsigned char SCOPE_CMD = 0x27;

const unsigned char SCOPE_WAVEFORM_DATA_SUBCMD        = 0x00;
const unsigned char SCOPE_OFF_ON_SUBCMD               = 0x10;
const unsigned char SCOPE_WAVEFORM_DATA_OUTPUT_SUBCMD = 0x11;
const unsigned char SCOPE_MAIN_OR_SUB_SUBCMD          = 0x12;
const unsigned char SCOPE_SINGLE_OR_DUAL_SUBCMD       = 0x13;
const unsigned char SCOPE_CENTER_OR_FIXED_SUBCMD      = 0x14;
const unsigned char SCOPE_CENTER_SPAN_SUBCMD          = 0x15;
const unsigned char SCOPE_FIXED_EDGE_SUBCMD           = 0x16;
const unsigned char SCOPE_HOLD_SUBCMD                 = 0x17;
const unsigned char SCOPE_REF_LEVEL_SUBCMD            = 0x19;
const unsigned char SCOPE_SPEED_SUBCMD                = 0x1A;
const unsigned char SCOPE_CENTER_TX_INDICATOR_SUBCMD  = 0x1B;
const unsigned char SCOPE_CENTER_MODE_SUBCMD          = 0x1C;
const unsigned char SCOPE_VBW_SUBCMD                  = 0x1D;
const unsigned char SCOPE_FIXED_EDGE_FREQS_SUBCMD     = 0x1E;

//int main(void)
//{
//    unsigned char buf[] = {PREAMBLE, PREAMBLE, 0x01, 0x02, 0xFD};
//    process_cmd_from_radio(buf, sizeof(buf));
//    return 0;
//}

static void process_scope_cmd_from_radio(const unsigned char *buf, int length);

int process_cmd_from_radio(const unsigned char *buf, int nread)
{
    // Spin past the 0xFEs.
    while(nread && PREAMBLE == *buf) {
        buf++;
        nread--;
    }

    // Controller address is going to be our address or 0. We really couldn't
    // be getting a message from anything other than the radio.
    if(nread && (CONT_ADDR == *buf || 0 == *buf)) {
        buf++;
        nread--;
    } else {
        printf("Bad controller address: %02X\n", *buf);
        return -1;
    }

    // Next will be the radio address.
    if(nread && XCVR_ADDR == *buf) {
        buf++;
        nread--;
    } else {
        printf("Bad transceiver address: %02X\n", *buf);
        return -1;
    }
    
    // Nothing to do if no more data.
    if(nread) {
        // Next byte is the command.
        --nread;
        switch(*buf++) {
            case SCOPE_CMD:
                process_scope_cmd_from_radio(buf, nread);
                break;
            default:
                break;
        }
    }

    return 0;
}

static void process_scope_cmd_from_radio(const unsigned char *buf, int length)
{
    // Nothing to do if no sub command.
    if(0 == length)
        return;

    --length;
    switch(*buf++) {
        case SCOPE_WAVEFORM_DATA_SUBCMD:
            puts("SCOPE_WAVEFORM_DATA_SUBCMD unhandled");
            break;
        case SCOPE_OFF_ON_SUBCMD:
            puts("SCOPE_OFF_ON_SUBCMD unhandled");
            break;
        case SCOPE_WAVEFORM_DATA_OUTPUT_SUBCMD:
            puts("SCOPE_WAVEFORM_DATA_OUTPUT_SUBCMD unhandled");
            break;
        case SCOPE_MAIN_OR_SUB_SUBCMD:
            puts("SCOPE_MAIN_OR_SUB_SUBCMD unhandled");
            break;
        case SCOPE_SINGLE_OR_DUAL_SUBCMD:
            puts("SCOPE_SINGLE_OR_DUAL_SUBCMD unhandled");
            break;
        case SCOPE_CENTER_OR_FIXED_SUBCMD:
            puts("SCOPE_CENTER_OR_FIXED_SUBCMD unhandled");
            break;
        case SCOPE_CENTER_SPAN_SUBCMD:
            puts("SCOPE_CENTER_SPAN_SUBCMD unhandled");
            break;
        case SCOPE_FIXED_EDGE_SUBCMD:
            puts("SCOPE_FIXED_EDGE_SUBCMD unhandled");
            break;
        case SCOPE_HOLD_SUBCMD:
            puts("SCOPE_HOLD_SUBCMD unhandled");
            break;
        case SCOPE_REF_LEVEL_SUBCMD:
            puts("SCOPE_REF_LEVEL_SUBCMD unhandled");
            break;
        case SCOPE_SPEED_SUBCMD:
            puts("SCOPE_SPEED_SUBCMD unhandled");
            break;
        case SCOPE_CENTER_TX_INDICATOR_SUBCMD:
            puts("SCOPE_CENTER_TX_INDICATOR_SUBCMD unhandled");
            break;
        case SCOPE_CENTER_MODE_SUBCMD:
            puts("SCOPE_CENTER_MODE_SUBCMD unhandled");
            break;
        case SCOPE_VBW_SUBCMD:
            puts("SCOPE_VBW_SUBCMD unhandled");
            break;
        case SCOPE_FIXED_EDGE_FREQS_SUBCMD:
            puts("SCOPE_FIXED_EDGE_FREQS_SUBCMD unhandled");
            break;
        default:
            printf("Unknown scope sub command: %02X\n", buf[-1]);
            break;
    }
}