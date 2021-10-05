/*
 * PollingRoutines.h
 *
 *  Created on: Sep 6, 2021
 *      Author: Philipp
 */

#ifndef INC_POLLINGROUTINES_H_
#define INC_POLLINGROUTINES_H_


// Compiler klar machen, dass es ein C File ist (Weil es eigentlich ein C++ Projekt ist)
#ifdef __cplusplus
extern "C" {
#endif

#define UART_BUF_SIZE 16


// Prototypen
void PollingInit();
void PollingRoutine();
void SendUartMsg(char *msg);

// Für Buttons:
typedef union{
	struct {
		uint8_t byte;
	}Bytes;
	struct {
		unsigned button1:1;
		unsigned button2:1;
		unsigned button3:1;
		unsigned :5;
	}Status;
}ButtonClicked;



#ifdef __cplusplus
}
#endif

#endif /* INC_POLLINGROUTINES_H_ */
