/* Handdle
 * Communication module
 * 2021
 */

/** @def MSG_TYPE_INTERNAL
 *  @brief Message type for the internal messages. Currently used for the generic ack message when the command or info is not recognized
 */
#define MSG_TYPE_INTERNAL 0x00

/** @def MSG_TYPE_COMMAND
 *  @brief Message type for all command messages (sent by the Jetson card)
 */
#define MSG_TYPE_COMMAND 0x01

/** @def MSG_TYPE_MAIN
 *  @brief Message type for all main messages
 */
#define MSG_TYPE_MAIN 0x02

/** @def MSG_TYPE_SECONDARY
 *  @brief Message type for all secondary messages
 */
#define MSG_TYPE_SECONDARY 0x03

/** @def MSG_TYPE_ERROR
 *  @brief Message type for all error messages
 */
#define MSG_TYPE_ERROR 0x04

/** @def MSG_TYPE_INFORMATION
 *  @brief Message type for every information message (sent by the Jetson card)
 */
#define MSG_TYPE_INFORMATION 0x05

