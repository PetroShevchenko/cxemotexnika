#include <cstdbool>
#include "clock_config.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"
#include "delay.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"

#define led_task_PRIORITY (configMAX_PRIORITIES - 1)

#ifndef MSEC_TO_TICK
#define MSEC_TO_TICK(msec) \
    ((uint32_t)(msec) * (uint32_t)configTICK_RATE_HZ / 1000uL)
#endif

static void led_task(void *pvParameters)
{
    static bool pinSet = false;
    while (1)
    {
        /* Delay 1000 ms */
        vTaskDelay(MSEC_TO_TICK(1000));
        if (pinSet)
        {
            PRINTF("LED Off\n\r");
            GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, 0U);
            pinSet = false;
        }
        else
        {
            PRINTF("LED On\n\r");
            GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, 1U);
            pinSet = true;
        }
    }
}

int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitLEDPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

    if (xTaskCreate(
            led_task,
            "LED_task",
            configMINIMAL_STACK_SIZE + 100,
            NULL,
            led_task_PRIORITY,
            NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    vTaskStartScheduler();
    return 0;
}