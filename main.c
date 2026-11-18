#include "delay.h"
#include "motor.h"
#include "card.h"

int main(void)
{
    delay_init();

    motor_init();   /* TB6612 + 方向 */
    card_init();    /* 读卡 + 语音 + 指示灯 */

    while (1) {
        motor_poll();   /* 软启动: 缓慢提速到 MOTOR_MAX_SPEED */
        card_poll();    /* 刷卡识别 -> 语音播报 */

        delay_ms(10);    /* 主循环周期约 10ms */
    }
}