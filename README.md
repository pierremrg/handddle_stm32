# Link between SMT32 and Jetson Nano, trought ST-Link cable

## Introduction

This folder contains every function to :
- Send messages from the SMT32 to the Jetson Nano board ;
- Receive messages from the Jetson Nano board ;
- Manage the UART used for the connection (interruption and callback).

## Message structure

Every message has a fixed structure and size, currently set to 20 bytes and the data is stored inside TLV, Type-Length-Value structures.

On our case, the TLV Message ID encapsulates the data TLV stored inside:
![TLV_Struct](../images/TLV_Struct.png)

Here, the header for every message is:
- Personal identifier (`0x0101`) ;
- Size equal to 20 bytes (`0x0010`) ;
- STM32 UID (`0xC0C0C0C0` for example).

Header example:

|Identifier| Length  | STM32 UID        | Message Type | ... |
|--------|--------|------------|--------------|-----|
| 0101 | 0010 | C0C0C0C0 | ...          | ... |


## How to use the Transport module

The first thing you need is to use the UART2, if you intend to use the St-Link cable to communicate with the STM32. Then, you have to to configure the UART2 and it's interruption.

Several things need to be configured in order to prepare the UART2 (`main.c` file) :

- A buffer variable, in our case `uint8_t Rx_buffer[20];`
- The function `HAL_UART_Receive_IT` has to be activated (User code begin 2) ;
- The `MX_USART2_UART_Init` function has to be checked (verify you have the correct baud rate for example) ;
- The `HAL_UART_RxCpltCallback` function has to be implemented. Basically, when the interruption for UART2 is activated, we have to give a buffer size. This size is very important because nothing will happen before the buffer is full. Once the buffer is full, the `HAL_UART_RxCpltCallback` function will be called, and our code will be executed;

For the `HAL_UART_RxCpltCallback` function we have :  
```c
parser(Rx_buffer, &huart2); // Parse the received message
memset(Rx_buffer, 0, sizeof(Rx_buffer)); // Reset the buffer
HAL_UART_Receive_IT(&huart2, Rx_buffer, MSG_SIZE); // Restart the interruption reception mode
```

## Supported message types

| Message type | 00       | 01       | 02   | 03        | 04     | 05          |
|--------------|----------|----------|------|-----------|--------|-------------|
|Description | Internal | Command  | Main | Secondary | Error | Information |

For every message type, specific messages are supported :
- The `command` and `information` messages are sent by the Jetson Nano to the SMT32 ;
- The `main`, `secondary`, `error` and `internal` messages are sent by the SMT32 to the Jetson Nano

### Internal Messages

For internal messages, only the ACK message is defined for the moment.

- If a message is received, but not recognized as a `command` nor as an `information` message, a general ACK `NOK` is sent with the internal message ID. The general ACK has the following structure :    

| Internal Messages |Identifier| Length | UID      | Msg Type | Information Type | Length |    | Padding      |
|-------------------|----------|--------|----------|----------|------------------|--------|----|--------------|
| NOK               | 0101     | 0010   | C0C0C0C0 | 00       | 00               | 0001   | 00 | (7 bytes)    |

- If a message is received and recognized as a `command` or as an `information` message, but no command or information type matches, then the `command` or `information` ID is used on the ACK `NOK` message sent by the SMT32 :

| Internal Messages |Identifier| Length | UID      | Msg Type | Information Type | Length |    | Padding      |
|-------------------|----------|--------|----------|----------|------------------|--------|----|--------------|
| NOK Cmd           | 0101     | 0010   | C0C0C0C0 | 00       | 01               | 0001   | 00 | (7 bytes)    |
| NOK Info          | 0101     | 0010   | C0C0C0C0 | 00       | 05               | 0001   | 00 | (7 bytes)    |

- If a message is received and recognized as a `command` or as an `information` message and matches a `command` or `information` type, the the ACK OK (`command` or `information` type) is sent :

| Internal Messages |Identifier| Length | UID      | Msg Type | Information Type | Length |     | Padding      |
|-------------------|----------|--------|----------|----------|------------------|--------|-----|--------------|
| ACK Cmd           | 0101     | 0010   | C0C0C0C0 | 00       | 01               | 0001   | 01 | (7 bytes)     |
| ACK Info          | 0101     | 0010   | C0C0C0C0 | 00       | 05               | 0001   | 01 | (7 bytes)     |
  
  
**Attention** this means that the ACK OK is sent if a command/information is recognized, and **not** if the command or information was taken into account. Further development is needed on the SmartFarm functions to enable this behavior (return a success/fail status).

### Command messages 

| Command message ID | 00           | 01           | 02               | 03          | 04                                                                                                                 | 05                                                                                                                | 06             |
|--------------------|--------------|--------------|------------------|-------------|--------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|----------------|
| Command type | Ack          | ON/OFF       | Door Open  | Temperature | Led color                                                                                                          | Printing State                                                                                                    | Air extraction |
| Value              | OK: 1 / NOK: 0 | ON: 1 / OFF: 0 | Open: 01 | 0 - 100°C   | Strong White: 0 / Medium White: 1 / Red: 2 / Green: 3 / Steady orange: 4 / Handddle blue: 5 / Blinky Orange: 6 / Low white: others | Door open: 0 / Post treatment: 1 / Print in progress: 2 / Free: 3 / Default: 4 / Material: 5 / Default: 6 / Other: other | 0 - 100%       |

### Main messages

| Main message ID | 01          | 02       | 03                   | 04         | 05                 | 06         | 07        | 08    | 09        | 10             |
|-----------------|-------------|----------|----------------------|------------|--------------------|------------|-----------|-------|-----------|----------------|
|                 | Temperature | Humidity | Temperature/Humidity | Current EE |  Current Printer   |Door state  | Pollution | Sound | Led color | Printing_State |

### Secondary messages
| Secondary message ID | 01            | 02            | 03               | 04                           | 05       | 06          | 07           |
|--------------------|---------------|---------------|------------------|------------------------------|----------|-------------|--------------|
| Main message type | Tachy Extract | Tachy Heating | Rack Temperature | Heating Resistor Temperature | Pressure | Relay state | Buzzer State |

### Error messages

| Error message ID | 01            | 02     | 03                      | 04                   | 05             | 06           |
|--------------------|---------------|--------|-------------------------|----------------------|----------------|--------------|
| Error message type | Tachy Extract | Heater | Environment Temperature | Environment Humidity | Heater Warning | Rack Warning |

### Information messages

| Inforamtion message ID | 01             | 02                    | 03                  | 04           |
|------------------------|----------------|-----------------------|---------------------|--------------|
| Information message type | Day/Night Mode | Manual/Automatic Mode | Pollution Threshold | Preheat Over |

**Attention !** For the pollution threshold information message, there is a special treatment of the data.
- If you want to set every threshold, just use the message as usual, and set the three fields at the value desired ;
- If you only want to set one threshold, you have to set the others to 0xFFFF (the thresholds set to 0xFFFF will be ignored).

## Detailed list of available messages

_".." cases stand for the values of the message._

### Commands
|      Commands       | Identifier | Length | UID      | Msg Type | Cmd Type | Length |      | Padding       |
|---------------------|------------|--------|----------|----------|----------|--------|------|---------------|
| Cmd ACK             | 0101 | 0010   | C0C0C0C0 | 01       | 00       | 0001   | .. | (7 bytes)  |
| Cmd ON/OFF          | 0101 | 0010   | C0C0C0C0 | 01       | 01       | 0001   | .. | (7 bytes)  |
| Cmd Door Open/Close | 0101 | 0010   | C0C0C0C0 | 01       | 02       | 0001   | .. | (7 bytes)  |
| Forcing door | 0101 | 0010   | C0C0C0C0 | 01       | 03       | 0001   | .. | (7 bytes)  |
| Cmd Temperature     | 0101 | 0010   | C0C0C0C0 | 01       | 04       | 0001   | .. | (7 bytes) |
| Cmd Led color       | 0101 | 0010   | C0C0C0C0 | 01       | 05       | 0001   | .. | (7 bytes) |
| Cmd Printing State  | 0101 | 0010   | C0C0C0C0 | 01       | 06       | 0001   | .. | (7 bytes)  |
| Cmd Air Extraction  | 0101 | 0010   | C0C0C0C0 | 01       | 07       | 0001   | .. | (7 bytes) |
| Cmd Relay  | 0101 | 0010   | C0C0C0C0 | 01       | 08       | 0001   | .. | (7 bytes) |

### Main Messages
| Main Messages       |  Identifier   | Length | UID      | Msg Type | Main Msg Type | Length |    | Padding     |
|---------------------|---------------|----------|----------|---------------|--------|--------|----|-------------|
| Temperature         | 0101 | 0010   | C0C0C0C0 | 02       | 01            | 0002   | .. .. | (6 bytes)        |
| Humidity            | 0101 | 0010   | C0C0C0C0 | 02       | 02            | 0002   | .. .. | (6 bytes)       |
| Temperature Humidiy | 0101 | 0010   | C0C0C0C0 | 02       | 03            | 0004   | .. .. .. .. | (4 bytes)        |
| Current EE          | 0101 | 0010   | C0C0C0C0 | 02       | 04            | 0002   | .. .. | (6 bytes)        |
| Current Printer     | 0101 | 0010   | C0C0C0C0 | 02       | 05            | 0002   | .. .. | (6 bytes)       |
| State door          | 0101 | 0010   | C0C0C0C0 | 02       | 06            | 0001   | .. | (7 bytes)       |
| Pollution           | 0101 | 0010   | C0C0C0C0 | 02       | 07            | 0006   | .. .. .. .. .. .. | (2 bytes) |
| Sound               | 0101 | 0010   | C0C0C0C0 | 02       | 08            | 0002   | .. .. | (6 bytes)        |
| Led Color           | 0101 | 0010   | C0C0C0C0 | 02       | 09            | 0002   | .. .. | (6 bytes)        |
| Printing State      | 0101 | 0010   | C0C0C0C0 | 02       | 0A            | 0002   | .. .. | (6 bytes)        |

#### Important information for the Jetson Nano script

- For the temperature, humidity and temperature/humidity messages, the temperature value sent in the message by the STM32 is multiplied by 100. To use the value on the Jetson side, you have do divide it by 100. This is due to decimal values, and wanting to keep the use of unsigned integers on every frame.
- For the pressure message, the value sent inside has had an increment of 50. In the Jetson script, you have to subtract 50 before using the value. This is due to the presence of negative values (down to -50), and wanting to keep the use of unsigned integers on every frame. 

### Secondary Messages
| Secondary Messages           |  Identifier | Length | UID      | Msg Type | Secondary Msg Type | Length |   | Padding      |
|------------------------------|-------------|--------|----------|----------|--------------------|--------|---|--------------|
| Tachy extraction             | 0101 | 0010   | C0C0C0C0 | 03       | 01                 | 0002   | .. .. | (6 bytes) |
| Tachy heating                | 0101 | 0010   | C0C0C0C0 | 03       | 02                 | 0002   | .. .. | (6 bytes) |
| Rack Temperature             | 0101 | 0010   | C0C0C0C0 | 03       | 03                 | 0002   | .. .. | (6 bytes) |
| Heating resistor temperature | 0101 | 0010   | C0C0C0C0 | 03       | 04                 | 0002   | .. .. | (6 bytes) |
| Pressure                     | 0101 | 0010   | C0C0C0C0 | 03       | 05                 | 0002   | .. .. | (6 bytes) |
| Relay State                  | 0101 | 0010   | C0C0C0C0 | 03       | 06                 | 0002   | .. .. | (6 bytes) |
| Buzzer State                 | 0101 | 0010   | C0C0C0C0 | 03       | 07                 | 0002   | .. .. | (6 bytes) |

### Error Messages

In order to facilitate the management of error messages by the Jetson script and to keep the same structure, error messages will have a length of 1 (the byte content will be ignored).

| Error Messages          | Identifier  | Length | UID      | Msg Type | Second Msg Type | Length | Padding      |
|-------------------------|-----|--------|----------|----------|--------|------------|--------------|
| Tachy extraction        | 0101 | 0010   | C0C0C0C0 | 04     | 01   | 0001       | (7 bytes) |
| Heater                  | 0101 | 0010   | C0C0C0C0 | 04     | 02   | 0001       | (7 bytes) |
| Environment Temperature | 0101 | 0010   | C0C0C0C0 | 04     | 03   | 0001       | (7 bytes) |
| Environment Humidity    | 0101 | 0010   | C0C0C0C0 | 04     | 04   | 0001       | (7 bytes) |
| Heater Warning          | 0101 | 0010   | C0C0C0C0 | 04     | 05   | 0001       | (7 bytes) |
| Rack Warning            | 0101 | 0010   | C0C0C0C0 | 04     | 06   | 0001       | (7 bytes) |

### Information Messages

| Information Messages | Identifier | Length | UID      | Msg Type | Information Type | Length |  | Padding    |
|----------------------|------------|--------|----------|----------|------------------|--------|--|------------|
| Ack                  | 0101 | 0010   | C0C0C0C0 | 05       | 00               | 0001   | .. | (7 bytes)      |
| Day/Night            | 0101 | 0010   | C0C0C0C0 | 05       | 01               | 0001   | .. | (7 bytes)        |
| Temperature manual mode | 0101 | 0010   | C0C0C0C0 | 05       | 02               | 0001   | .. | (7 bytes)      |
| Filtration manual mode | 0101 | 0010   | C0C0C0C0 | 05       | 03               | 0001   | .. | (7 bytes)      |
| Pollution threshold  | 0101 | 0010   | C0C0C0C0 | 05       | 04               | 0006   | .. | (7 bytes)      |  
| Door state         | 0101 | 0010   | C0C0C0C0 | 05       | 05 | 0001   | .. | (7 bytes)     |
