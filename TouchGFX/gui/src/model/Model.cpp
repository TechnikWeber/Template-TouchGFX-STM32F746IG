#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "cmsis_os.h"
#include "semphr.h"

extern osSemaphoreId binarySemUartMsgHandle;
extern osMessageQueueId_t queueScreen1Handle;
extern osMessageQueueId_t queueScreen1_2Handle;



Model::Model() : modelListener(0)
{

}

// Das wird von TouchGFX geupdatet (wie Polling)
void Model::tick()
{
	if (binarySemUartMsgHandle != NULL)
	{
		 if( xSemaphoreTake( (QueueHandle_t)binarySemUartMsgHandle, ( TickType_t ) 10 ) == pdTRUE )
		{
			uartMsgRdy();
		}
	}
}

void Model::uartMsgRdy()
{
	modelListener->uartMsgRdy();
}

void Model::screen1ButtonClicked(int button)
{
	uint16_t item;
	item = button;

	xQueueSend( (QueueHandle_t)queueScreen1Handle, &item, ( TickType_t ) 10);
}

void Model::screen1Button2Clicked(int button)
{
	uint16_t item;
	item = button;

	xQueueSend( (QueueHandle_t)queueScreen1_2Handle, &item, ( TickType_t ) 10);
}
