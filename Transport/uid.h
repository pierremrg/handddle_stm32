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

// 0x[TYPE][00][POS_X][POS_Y]
#define MSG_HEADER_UID_1 UID_START             // Ne pas toucher
#define MSG_HEADER_UID_2 TYPE_MACHINE   // A configurer
#define MSG_HEADER_UID_3 0x05                  // position x, y     toit du 2e module -> 2 - 1    et rack 2 - 2
#define MSG_HEADER_UID_4 0x01
