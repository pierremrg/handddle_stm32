# Handddle Comunication software
### Link between SMT32 and Jetson Nano, trought ST-Link cable

This folder contains every function to :
	- Send messages from the SMT32 to the Jetson Nano board
	- Receive messages from the Jetson Nano
	- Manage the Uart used for the connection (Interruption and callback)


Every message has a fixed structure and size, currently set to 20 bytes. The concept is that the data is stored inside TLV, Type-Length-Value structures.
On our case, the TLV Message ID encapsulates the data TLV stored inside:
![TLV_Struct](../images/TLV_Struct.png)

In our case, the header for every message is:
	- With,
		- Size equal to 20 bytes
		- UID equal to C0C0C0C0
|        | Length  | UID        | Message Type | ... |
|--------|--------|------------|--------------|-----|
| 0x0101 | 0x0010 | 0xc0c0c0c0 | ...          | ... |


## How to use the Transport module
The first thing you'll need, is to use the UART2, if you intend to use the St-Link cable to comunicate with the STM32. Then you have to to configure the UART2 and it's interruption.
Several things need to be configured in order to prepare the UART2 (*main.c* file) :

- A buffer variable, in our case `uint8_t Rx_buffer[20];`
- The function `HAL_UART_Receive_IT` has to activated; (User code begin 2)
- The `MX_USART2_UART_Init` function has to be checkd. Verify you have the correct baud rate for example
- The `HAL_UART_RxCpltCallback` function has to be implemented. Basically, when the interruption for UART2 is activated, we have to give a buffer size. This size is very important because nothing will happen before the buffer is full. Once the buffer is full, the `HAL_UART_RxCpltCallback` function will be called, and our code will be executed.
For the `HAL_UART_RxCpltCallback` we have :  
`parser(Rx_buffer,&huart2);`  
`memset(Rx_buffer,0,sizeof(Rx_buffer));`  
`HAL_UART_Receive_IT(&huart2,Rx_buffer,MSG_SIZE);// This restarts the interruption reception mode`  

## The different message types supported are:
| Message type | 00       | 01       | 02   | 03        | 04     | 05          |
|--------------|----------|----------|------|-----------|--------|-------------|
|              | Internal | Command  | Main | Secondary | Errors | Information |

For every message type there are specific messages supported. The command and information messages are sent by the Jetson Nano to the SMT32, and the Main, Secondary, Error and internal messages are sent by the SMT32 to the Jetson Nano. 
### Internal Messages
For internal messages, only the ack message is defined for the moment.
- If a message is received, but not recognized as a command or an information, a general ack NOK is sent with the internal message ID. The general ack has the following structure :    

| Internal Messages |    |    |    | Length | UID      | Msg Type | Information Type | Length |    |    | Padding      |
|-------------------|----|----|----|--------|----------|----------|------------------|--------|----|----|--------------|
| Ack               | 0x | 01 | 01 | 0010   | c0c0c0c0 | 00       | 00               | 0001   | 00 | xx | xxxxxxxxxxxx |
- If a message is received and recognized as a command or an information but no command or information types match, then the command or information ids are used on the ack NOK message sent by the SMT32    

| Internal Messages |    |    |    | Length | UID      | Msg Type | Information Type | Length |    |    | Padding      |
|-------------------|----|----|----|--------|----------|----------|------------------|--------|----|----|--------------|
| Ack Cmd           | 0x | 01 | 01 | 0010   | c0c0c0c0 | 00       | 01               | 0001   | 00 | xx | xxxxxxxxxxxx |
| Ack Info          | 0x | 01 | 01 | 0010   | c0c0c0c0 | 00       | 05               | 0001   | 00 | xx | xxxxxxxxxxxx |
- If a message is received and recognized as a command or an information and matchs a command or information type, the the ack OK (command or information) is sent.     

| Internal Messages |    |    |    | Length | UID      | Msg Type | Information Type | Length |    |    | Padding      |
|-------------------|----|----|----|--------|----------|----------|------------------|--------|----|----|--------------|
| Ack Cmd           | 0x | 01 | 01 | 0010   | c0c0c0c0 | 00       | 01               | 0001   | 01 | xx | xxxxxxxxxxxx |
| Ack Info          | 0x | 01 | 01 | 0010   | c0c0c0c0 | 00       | 05               | 0001   | 01 | xx | xxxxxxxxxxxx |
  
  
**Attention** this means that the ack OK is sent if a command/information is recognized, and **not** if the command or information was taken into account. Further development is needed on the SmartFarm functions to enable this behaviour (return a succes/fail status).

### Important information for the Jetson Nano script
- For the temperature, humidity and temperature/humidity messages, the temperature value sent in the message by the STM32 is multiplied by 100. To use the value on the Jetson side, you have do divide it by 100. This is due to decimal values, and wanting to keep the use of unsigned integers on every frame.
- For the pressure message, the value sent inside has had an increment of 50. In the Jetson script, you have to subtract 50 before using the value. This is due to the presence of negative values (down to -50), and wanting to keep the use of unsigned integers on every frame. 
### Command Messages 

| Command message ID | 00           | 01           | 02               | 03          | 04                                                                                                                 | 05                                                                                                                | 06             |
|--------------------|--------------|--------------|------------------|-------------|--------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|----------------|
|                    | Ack          | ON/OFF       | Door Open  | Temperature | Led color                                                                                                          | Printing State                                                                                                    | Air extraction |
| Value              | OK: 1 NOK: 0 | ON: 1 OFF: 0 | Open: 01 | 0 - 100°C   | Strong White: 0   Medium White: 1   Red: 2   Green: 3 Steady orange: 4 Handdle blue: 5 Blinky Orange: 6 Low white: other | Door open: 0 Post treatment: 1 Print in progress: 2 Free: 3 Default: 4 Primal material: 5 Default: 6 Other: other | 0 - 100%       |

**Attention** For the temperature command, there is a special treatment of the data.
- To set a temperature during the setup data state, just use the usual message.
- If the user don't specify any temperature value, the app have to send 0xFFFF.(The desired temperature will be the ambiant temperature)

### Main Messages

| Main message ID | 01          | 02       | 03                   | 04         | 05                 | 06         | 07        | 08    | 09        | 10             |
|--------------------|-------------|----------|----------------------|------------|--------------------|------------|-----------|-------|-----------|----------------|
|                    | Temperature | Humidity | Temperature/Humidity | Current EE |  Current Printer   |Door state  | Pollution | Sound | Led color  | Printing_State |

### Secondary Messages
| Secondary message ID | 01            | 02            | 03               | 04                           | 05       | 06          | 07           |
|--------------------|---------------|---------------|------------------|------------------------------|----------|-------------|--------------|
|                    | Tachy Extract | Tachy Heating | Rack Temperature | Heating Resistor Temperature | Pressure | Relay state | Buzzer State |

### Error Messages

| Error message ID | 01            | 02     | 03                      | 04                   | 05             | 06           |
|--------------------|---------------|--------|-------------------------|----------------------|----------------|--------------|
|                    | Tachy Extract | Heater | Environment Temperature | Environment Humidity | Heater Warning | Rack Warning |

## Information Messages

| Information message ID | 01             | 02                    | 03                  | 04           |
|------------------------|----------------|-----------------------|---------------------|--------------|
|                        | Day/Night Mode | Manual/Automatic Mode | Pollution Threshold | Preheat Over |

**Attention** For the pollution threshold information message, there is a special treatment of the data.
- If you want to set every threshold, just use the message as per usual, and set the three fields at the value desired.
- If you only want to set one threshold, you have to set the others at 0xFFFF.(The thresholds set to 0xFFF will be ignored) 
## The list of available messages is:
.. Case are for the values of the message
xx Case are for padding

### Commands
|      Commands       |    |    |    | Length | UID      | Msg Type | Cmd Type | Length |    |    | Padding       |
|---------------------|----|----|----|--------|----------|----------|----------|--------|----|----|---------------|
| Cmd Ack             | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 00       | 0001   | .. | xx | xxxxxxxxxxxx  |
| Cmd ON/OFF          | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 01       | 0001   | .. | xx | xxxxxxxxxxxx  |
| Cmd Door Open/Close | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 02       | 0001   | .. | xx | xxxxxxxxxxxx  |
| Cmd Forcing Door	  | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 03       | 0001   | .. | xx | xxxxxxxxxxxx  |
| Cmd Temperature     | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 04       | 0002   | .. | .. | xxxxxxxxxxxx  |
| Cmd Led color       | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 05       | 0002   | .. | .. | xxxxxxxxxxxx
| Cmd Printing State  | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 06       | 0001   | .. | xx | xxxxxxxxxxxx  |
| Cmd Air Extraction  | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 07       | 0002   | .. | .. | xxxxxxxxxxxx  |
| Cmd Relay			  | 0x | 01 | 01 | 0010   | c0c0c0c0 | 01       | 08       | 0001   | .. | xx | xxxxxxxxxxxx  |

### Main Messages
| Main Messages       |    |    |    | Length | UID      | Msg Type | Main Msg Type | Length |    |    |    |    |    |    | Padding     |
|---------------------|----|----|----|--------|----------|----------|---------------|--------|----|----|----|----|----|----|-------------|
| Temperature         | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 01            | 0002   | .. | .. | xx | xx | xx | xx | xxxx        |
| Humidity            | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 02            | 0002   | .. | .. | xx | xx | xx | xx | xxxx        |
| Temperature Humidiy | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 03            | 0004   | .. | .. | .. | .. | xx | xx | xxxx        |
| Current EE          | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 04            | 0002   | .. | .. | xx | xx | xx | xx | xxxx        |
| Current Printer     | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 05            | 0002   | .. | .. | xx | xx | xx | xx | xxxx        |
| State door          | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 06            | 0001   | .. | xx | xx | xx | xx | xx | xxxx        |
| Pollution           | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 07            | 0006   | .. | .. | .. | .. | .. | .. | xxxx        |
| Sound               | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 08            | 0002   | .. | .. | xx | xx | xx | xx | xxxx        |
| Led Color           | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 09            | 0002   | .. | .. | xx | xx | xx | xx | xxxx        |
| Printing State      | 0x | 01 | 01 | 0010   | c0c0c0c0 | 02       | 0A            | 0002   | .. | .. | xx | xx | xx | xx | xxxx        |

### Secondary Messages
| Secondary Messages           |    |    |    | Length | UID      | Msg Type | Secondary Msg Type | Length |    |    | Padding      |
|------------------------------|----|----|----|--------|----------|----------|--------------------|--------|----|----|--------------|
| Tachy extraction             | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 01                 | 0002   | .. | .. | xxxxxxxxxxxx |
| Tachy heating                | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 02                 | 0002   | .. | .. | xxxxxxxxxxxx |
| Rack Temperature             | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 03                 | 0002   | .. | .. | xxxxxxxxxxxx |
| Heating resistor temperature | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 04                 | 0002   | .. | .. | xxxxxxxxxxxx |
| Pressure                     | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 05                 | 0002   | .. | .. | xxxxxxxxxxxx |
| Relay State                  | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 06                 | 0002   | .. | .. | xxxxxxxxxxxx |
| Buzzer State                 | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 07                 | 0002   | .. | .. | xxxxxxxxxxxx |
| Preheat over                 | 0x | 01 | 01 | 0010   | c0c0c0c0 | 03       | 08                 | 0002   | .. | .. | xxxxxxxxxxxx |

### Error Messages
| Error Messages          |    |    |    | Length | UID      | Msg Type | Length | Error Type | Padding      |
|-------------------------|----|----|----|--------|----------|----------|--------|------------|--------------|
| Tachy extraction        | 0x | 01 | 01 | 0010   | c0c0c0c0 | 0400     | 0002   | 0001       | xxxxxxxxxxxx |
| Heater                  | 0x | 01 | 01 | 0010   | c0c0c0c0 | 0400     | 0002   | 0002       | xxxxxxxxxxxx |
| Environment Temperature | 0x | 01 | 01 | 0010   | c0c0c0c0 | 0400     | 0002   | 0003       | xxxxxxxxxxxx |
| Environment Humidity    | 0x | 01 | 01 | 0010   | c0c0c0c0 | 0400     | 0002   | 0004       | xxxxxxxxxxxx |
| Heater Warning          | 0x | 01 | 01 | 0010   | c0c0c0c0 | 0400     | 0002   | 0005       | xxxxxxxxxxxx |
| Rack Warning            | 0x | 01 | 01 | 0010   | c0c0c0c0 | 0400     | 0002   | 0006       | xxxxxxxxxxxx |

### Information Messages
| Information Messages 		|    |    |    | Length | UID      | Msg Type | Information Type | Length |    |    |    |    |    |    | Padding    |
|----------------------		|----|----|----|--------|----------|----------|------------------|--------|----|----|----|----|----|----|------------|
| Ack                  		| 0x | 01 | 01 | 0010   | c0c0c0c0 | 05       | 00               | 0001   | .. | xx | xx | xx | xx | xx | xxxx       |
| Day/Night            		| 0x | 01 | 01 | 0010   | c0c0c0c0 | 05       | 01               | 0001   | .. | xx | xx | xx | xx | xx | xxxx       |
| Manual_Temperature ON/OFF	| 0x | 01 | 01 | 0010   | c0c0c0c0 | 05       | 02               | 0001   | .. | xx | xx | xx | xx | xx | xxxx       |
| Manual_Filtration ON/OFF	| 0x | 01 | 01 | 0010   | c0c0c0c0 | 05       | 03               | 0001   | .. | xx | xx | xx | xx | xx | xxxx       |
| Pollution Threshold  		| 0x | 01 | 01 | 0010   | c0c0c0c0 | 05       | 04               | 0006   | .. | .. | .. | .. | .. | .. | xxxx       |  
| Door Status				| 0x | 01 | 01 | 0010   | c0c0c0c0 | 05       | 05               | 0001   | .. | xx | xx | xx | xx | xx | xxxx       |