/*
 * tests.c
 *
 * Created: 11/02/2015 12:40:48
 *  Author: Nicolas Rabault
 */


#include "poppyNetwork.h"
#include "inc/sys_msg.h"
#include "inc/target.h"
#include "test_mngmnt.h"

#include <stdio.h>

int test_value = 0;
unsigned short target_value = 0;

typedef enum {
    TARGET_CMD = WRITE_ID,
    TEST_CMD = PROTOCOL_CMD_NB,
    NO_OVERLAP_TARGET_CMD,
    MODULE_PROTOCOL_NB
}module_register_t;

void rx_cb(msg_t *msg) {
    switch (msg->header.cmd) {
        case TEST_CMD :
            test_value = ((int)msg->data[0] << 8) | (int)msg->data[1];
        break;
        case TARGET_CMD :
        case NO_OVERLAP_TARGET_CMD:
            target_value = msg->header.target;
        break;
        default :
            test_value = 0;
        break;
    }
}

/*
 * TEST SEQUENCES
 */

unsigned char test_init(void) {
    printf("\nInitialisation :\n");
    poppyNetwork_init(rx_cb);
    if (test(ctx.rx_cb == rx_cb)) return 1;
    return 0;
}


unsigned char set_id_brdcst(void) {
    printf("\nSet ID with BROADCAST mode :\n");
    if (test(!set_extern_id(BROADCAST, BROADCAST_VAL, 0x000A))) return 1;
    if (test(ctx.id == 0x000A)) return 1;
    return 0;
}

unsigned char set_id(void) {
    printf("\nSet ID in ID mode :\n");
    if (test(!set_extern_id(ID, ctx.id, 0x000B))) return 1;
    if (test(ctx.id == 0x000B)) return 1;
    return 0;
}

unsigned char set_id_type(void) {
    printf("\nSet ID in TYPE mode :\n");
    if (test(!set_extern_id(TYPE, ctx.type, 0x000C))) return 1;
    if (test(ctx.id == 0x000C)) return 1;
    return 0;
}

unsigned char set_id_ack(void) {
    // this one can't be tested in stub mode...
    printf("\nSet ID in IDACK mode :\n");
    if (test(!set_extern_id(IDACK, ctx.type, 0x000D))) return 1;
    if (test(ctx.id == 0x000D)) return 1;
    if (test(ctx.msg.ack)) return 1;
    return 0;
}

unsigned char write_id_mode(void) {
    printf("\nSend something in id_mode message :\n");
    msg_t msg = {.header.cmd = TEST_CMD,
                 .header.target = ctx.id,
                 .header.target_mode = ID,
                 .header.size = 2,
                 .data[0] = 0xCA,
                 .data[1] = 0xFE};

    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(test_value == 0xCAFE)) return 1;
    test_value = 0x0000;
    return 0;
}

unsigned char write_broadcast_mode(void) {
    printf("\nSend something in BROADCAST mode message :\n");
    msg_t msg = {.header.cmd = TEST_CMD,
                 .header.target = BROADCAST_VAL,
                 .header.target_mode = BROADCAST,
                 .header.size = 2,
                 .data[0] = 0xCA,
                 .data[1] = 0xFE};
    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(test_value == 0xCAFE)) return 1;
    test_value = 0x0000;
    return 0;
}

unsigned char add_multicast(void) {
    printf("\nAdd a MULTICAST target :\n");
    add_multicast_target(0x000E);
    if (test(ctx.multicast_target_bank[ctx.max_multicast_target] != 0x000E)) return 1;
    msg_t msg = {.header.cmd = TARGET_CMD,
                 .header.target = 0x000E,
                 .header.target_mode = MULTICAST,
                 .header.size = 2,
                 .data[0] = 0xCA,
                 .data[1] = 0xFE};
    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(target_value == 0x000E)) return 1;
    add_multicast_target(0x00AE);
    msg.header.target = 0x00AE;
    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(target_value == 0x00AE)) return 1;
    msg.header.target = 0x000E;
    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(target_value == 0x000E)) return 1;
    target_value = 0x0000;
    return 0;
}

unsigned char add_virtual(void) {
    printf("\nAdd a VIRTUAL target :\n");
    add_virtual_target(0x000E);
    if (test(ctx.virtual_target_bank[ctx.max_virtual_target] != 0x000E)) return 1;
    msg_t msg = {.header.cmd = WRITE_ID,
                 .header.target = 0x000E,
                 .header.target_mode = ID,
                 .header.size = 2,
                 .data[0] = 0xCA,
                 .data[1] = 0xFE};
    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(ctx.id == 0xCAFE)) return 1;
    add_virtual_target(0x00AE);
    msg.header.target = 0x00AE;
    msg.header.cmd = NO_OVERLAP_TARGET_CMD;
    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(target_value == 0x00AE)) return 1;
    msg.header.target = 0x000E;
    if (test(!poppyNetwork_send(&msg))) return 1;
    if (test(target_value == 0x000E)) return 1;
    target_value = 0x0000;
    return 0;
}

int main(void) {
    printf("test sequences :\n");

    test_sequences(test_init);
    test_sequences(set_id_brdcst);
    test_sequences(set_id);
    test_sequences(set_id_type);
    test_sequences(write_id_mode);
    test_sequences(write_broadcast_mode);
    test_sequences(add_multicast);
    test_sequences(add_virtual);

    return test_end();
}
