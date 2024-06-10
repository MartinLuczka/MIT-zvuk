#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
#include "delay.h"
//#include "uart1.h"

#define tranzistor GPIOG, GPIO_PIN_3

void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(GPIOG, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);

    init_milis();
}


int main(void)
{
    uint32_t time = 0;
    uint32_t time_switch = 0;
    bool stav_tranzistoru = 0;
    init();

    while(1) {
        if(milis() - time > 5) {
            time = milis();
            REVERSE(tranzistor);
            if(milis() - time_switch > 125) {
                if(stav_tranzistoru == 0) {
                    LOW(tranzistor);
                    delay_ms(125);
                    stav_tranzistoru = 1;
                }
                else if(stav_tranzistoru == 1) {
                    HIGH(tranzistor);
                    delay_ms(125);
                    stav_tranzistoru = 0;
                }
                time_switch = milis();
            }
        }
    }

}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
