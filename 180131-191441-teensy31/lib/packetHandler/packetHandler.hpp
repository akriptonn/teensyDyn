#ifndef _PACKET_HANDLER_H_
#define _PACKET_HANDLER_H_

#ifndef _STDINT_H_
#define _STDINT_H_

#include <stdint.h>

#endif

#ifndef _VECTOR_
#define _VECTOR_

#include <vector>

#endif

#define __BROADCAST_ID__ 0xFE
#define MAX_ID              0xFC    // 252

/* Macro for Control Table Value */
#define DXL_MAKEWORD(a, b)  ((uint16_t)(((uint8_t)(((uint64_t)(a)) & 0xff)) | ((uint16_t)((uint8_t)(((uint64_t)(b)) & 0xff))) << 8))
#define DXL_MAKEDWORD(a, b) ((uint32_t)(((uint16_t)(((uint64_t)(a)) & 0xffff)) | ((uint32_t)((uint16_t)(((uint64_t)(b)) & 0xffff))) << 16))
#define DXL_LOWORD(l)       ((uint16_t)(((uint64_t)(l)) & 0xffff))
#define DXL_HIWORD(l)       ((uint16_t)((((uint64_t)(l)) >> 16) & 0xffff))
#define DXL_LOBYTE(w)       ((uint8_t)(((uint64_t)(w)) & 0xff))
#define DXL_HIBYTE(w)       ((uint8_t)((((uint64_t)(w)) >> 8) & 0xff))

/* Instruction for DXL Protocol */
#define INST_PING               1
#define INST_READ               2
#define INST_WRITE              3
#define INST_REG_WRITE          4
#define INST_ACTION             5
#define INST_FACTORY_RESET      6
#define INST_SYNC_WRITE         131     // 0x83
#define INST_BULK_READ          146     // 0x92

// Communication Result
#define COMM_SUCCESS        0       // tx or rx packet communication success
#define COMM_PORT_BUSY      -1000   // Port is busy (in use)
#define COMM_TX_FAIL        -1001   // Failed transmit instruction packet
#define COMM_RX_FAIL        -1002   // Failed get status packet
#define COMM_TX_ERROR       -2000   // Incorrect instruction packet
#define COMM_RX_WAITING     -3000   // Now recieving status packet
#define COMM_RX_TIMEOUT     -3001   // There is no status packet
#define COMM_RX_CORRUPT     -3002   // Incorrect status packet
#define COMM_NOT_AVAILABLE  -9000   //

#define bytes uint8_t
///////////////// for Protocol 1.0 Packet /////////////////
#define PKT_HEADER0             0
#define PKT_HEADER1             1
#define PKT_ID                  2
#define PKT_LENGTH              3
#define PKT_INSTRUCTION         4
#define PKT_ERROR               4
#define PKT_PARAMETER0          5

///////////////// Protocol 1.0 Error bit /////////////////
#define ERRBIT_VOLTAGE          1       // Supplied voltage is out of the range (operating volatage set in the control table)
#define ERRBIT_ANGLE            2       // Goal position is written out of the range (from CW angle limit to CCW angle limit)
#define ERRBIT_OVERHEAT         4       // Temperature is out of the range (operating temperature set in the control table)
#define ERRBIT_RANGE            8       // Command(setting value) is out of the range for use.
#define ERRBIT_CHECKSUM         16      // Instruction packet checksum is incorrect.
#define ERRBIT_OVERLOAD         32      // The current load cannot be controlled by the set torque.
#define ERRBIT_INSTRUCTION      64      // Undefined instruction or delivering the action command without the reg_write command.

class DynamixelPacket{
    bytes *biPacket = 0;
    uint8_t arrsize;
    void checksum(uint8_t *data_blk_ptr, uint8_t data_blk_size, uint8_t idx);
    int txpacket(uint8_t *txpacket);

    public:
        DynamixelPacket( bytes aID, bytes aInstruction, std::vector< bytes > adata );
        ~DynamixelPacket();
        void transaction();
};

#undef bytes
#endif