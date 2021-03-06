/* Handdle
 * Communication module
 * 2021
 */

/*
 * The UID is the Unique Identifier for the SMT32
 * This value is hardcoded and never changed
 */

#define TYPE_MACHINE_TOIT 0xC1
#define TYPE_MACHINE_RACK 0xC2
#define TYPE_MP 		  0xC3
#define TYPE_POST_TREATMENT 0xC4

#define UID_START 0xC0

#define MSG_HEADER_UID_BROADCAST 0xFF
#define MSG_HEADER_UID_1_BROADCAST 0xCF

// 0x[TYPOLOGY][MONTH][YEAR][ID (01/02/03/etc.)]
#define MSG_HEADER_UID_1 TYPE_MACHINE_RACK //
#define MSG_HEADER_UID_2 0x00
#define MSG_HEADER_UID_3 0x00
#define MSG_HEADER_UID_4 0x01
