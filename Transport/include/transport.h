/* Handdle
 * Communication module
 * 2021
 */

#include "../../Core/Inc/main.h"


/** @def MSG_SIZE
 *  @brief Message size. This variable controls the size expected for the message received, and the message size for those sent.
 */
#define MSG_SIZE 20

/* Header information */
// Message identifier
#define MSG_HEADER_IDENTIFIER_1 0x01
#define MSG_HEADER_IDENTIFIER_2 0x01

// Message size included in the header message
#define MSG_HEADER_SIZE_1 0x00
#define MSG_HEADER_SIZE_2 0x10


/* Bytes positions */
// TODO Replace this with a struct. Should be included in the whole system.
#define POS_IDENTIFIER_1 0
#define POS_IDENTIFIER_2 1
#define POS_LENGTH_1 2
#define POS_LENGTH_2 3
#define POS_UID_1 4
#define POS_UID_2 5
#define POS_UID_3 6
#define POS_UID_4 7
#define POS_MSG_TYPE 8
#define POS_MSG_SUBTYPE 9
#define POS_CONTENT_LENGTH_1 10
#define POS_CONTENT_LENGTH_2 11
#define POS_DATA 12


/* Misc data */
#define AUTO_VALUE 0xFF
