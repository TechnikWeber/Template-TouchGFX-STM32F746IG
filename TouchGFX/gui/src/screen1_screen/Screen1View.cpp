#include <gui/screen1_screen/Screen1View.hpp>

#include "string.h"
#include "PollingRoutines.h"

extern uint8_t uartMsgBuf[UART_BUF_SIZE];

extern ButtonClicked screen1ButtonClicked;
extern ButtonClicked screen1Button2Clicked;

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::uartMsgRdy()
{
	if (uartMsgBuf[0] == 0)
		{
		return;	// Leeres Array also nichts zu tun
		}

	memset(&textArea1Buffer, 0, TEXTAREA1_SIZE);

	Unicode::strncpy(textArea1Buffer, (char*) uartMsgBuf, TEXTAREA1_SIZE - 1);
	textArea1Buffer[16] = '\0'; // Letzten Index immer 0 setzem
	textArea1.invalidate();
}


// Kopiert aus Screen1ViewBase
void Screen1View::buttonSendClicked()
{
	presenter->buttonClicked(1);
}

void Screen1View::buttonSend2Clicked()
{
	presenter->buttonClicked(2);
}
