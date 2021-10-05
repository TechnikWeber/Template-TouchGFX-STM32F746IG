/*
 * PollingRoutines.c
 *
 *  Created on: Sep 6, 2021
 *      Author: Philipp
 */

// Grundsätzliches Prinzip vom Daten (UART) zu Display
// Model.cpp -> ModelListener.cpp -> ScreenPresenter.cpp -> ScreenView.cpp
// MODEL -> LISTENER -> PRESENTER -> VIEW

// Grundsätziches Prinzip von Buttonclick zu Daten (UART)
// ScreenViewBase.hpp -> ScreenView.cpp -> ScreenPresenter.cpp -> Model.cpp

#include "main.h"
#include "PollingRoutines.h"
#include "string.h"
#include "cmsis_os.h"
#include "semphr.h"


extern UART_HandleTypeDef huart1;
extern osSemaphoreId binarySemUartMsgHandle;
extern osMessageQueueId_t queueScreen1Handle;
extern osMessageQueueId_t queueScreen1_2Handle;

uint8_t uartMsgBuf[UART_BUF_SIZE];
uint8_t uartMsgData[2];
uint8_t msgIndex = 0;
uint8_t msgRdyFlag = 0;

ButtonClicked screen1ButtonClicked;
ButtonClicked screen1Button2Clicked;


const char uartMsgOut[] = "Button 1\n\r";
const char uartMsgOut2[] = "Button 2\n\r";
char myString[100];


void PollingInit()
{
	// Interrupt einschalten, Speichert 1 Byte ins Array
	HAL_UART_Receive_IT(&huart1, uartMsgData, 1);
}

void PollingRoutine()
{
	uint16_t item;

	// Schauen ob Daten kommen
	if (msgRdyFlag)
	{
		// Setzt das Semaphore wenn Nachricht ansteht
		xSemaphoreGive(binarySemUartMsgHandle);
		msgRdyFlag = 0;
	}

	// Schauen ob Button gedrückt
	if (xQueueReceive(queueScreen1Handle, &item, ( TickType_t ) 10) == pdPASS)
	{
		memset(&myString, 0, sizeof(myString));

		switch(item)
		{
		case 1: // Button 1
			strcat(myString, uartMsgOut);
			break;
		case 2:	// Button 2
			strcat(myString, uartMsgOut2);
			break;
		}
		SendUartMsg(myString);
	}
}

void SendUartMsg(char *msg)
{
	if (HAL_UART_Transmit_IT(&huart1, (uint8_t *)msg, strlen(msg)) != HAL_OK)
		{
			// ERROR?
		}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (msgIndex == 0)
	{
		memset(&uartMsgBuf, 0 , sizeof(uartMsgBuf));
	}
	// Ist das Byste eine CR? (Dezimal!)
	if (uartMsgData[0] != 13)
	{
		uartMsgBuf[msgIndex++] = uartMsgData[0];
	}
	else
	{
		uartMsgBuf[msgIndex] = uartMsgData[0];
		msgIndex = 0;

		msgRdyFlag = 1;
	}

	// Wenn fertig den IT wieder einschalten!
	HAL_UART_Receive_IT(&huart1, uartMsgData, 1);
}
