/* Handdle
 * Communication module
 * 2021
 */

/*
 * The UID is the Unique Identifier for the SMT32
 * This value is hardcoded and never changed
 */
#define TYPE_MACHINE 0x01
#define TYPE_RESOURCE 0x02
#define TYPE_POST_TREATMENT 0x03
#define TYPE_BALANCE 0x04

#define UID_START 0xC0

#define MSG_HEADER_UID_BROADCAST 0xFF

// 0x[START][MONTH][YEAR][ID (01/02/03/etc.)]
#define MSG_HEADER_UID_1 UID_START
#define MSG_HEADER_UID_2 0x00
#define MSG_HEADER_UID_3 0x00
#define MSG_HEADER_UID_4 0x01
