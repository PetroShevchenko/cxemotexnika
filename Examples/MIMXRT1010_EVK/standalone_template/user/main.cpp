#include <cstdbool>
#include "clock_config.h"
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"
#include "delay.h"
#include "fsl_debug_console.h"

static bool g_pinSet = false;

int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitLEDPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

    while (1)
    {
        /* Delay 1000 ms */
        delay_ms(1000);
        if (g_pinSet)
        {
            PRINTF("LED Off\n\r");
            GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, 0U);
            g_pinSet = false;
        }
        else
        {
            PRINTF("LED On\n\r");
            GPIO_PinWrite(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, 1U);
            g_pinSet = true;
        }
    }
	return 0;
}