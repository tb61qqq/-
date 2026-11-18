#include "motor.h"
#include "sys.h"
#include "tb6612.h"

static u16 motor_spd = 0;
static u16 ram_tick  = 0;

void motor_init(void)
{
    tb6612_init(0);                /* TIM1 PWM, 初始占空比0 */
    motor_a_set(MOTOR_REVERSE, 0); /* A电机(AO1/AO2)方向+初始停 */
}

/* 每 ~5ms 调用一次: 缓慢提速到 MOTOR_MAX_SPEED 后保持匀速 */
void motor_poll(void)
{
    if (motor_spd >= MOTOR_MAX_SPEED) {
        return;
    }

    ram_tick += 5;
    if (ram_tick < MOTOR_RAMP_DELAY) {
        return;
    }

    ram_tick = 0;
    motor_spd += MOTOR_RAMP_STEP;
    if (motor_spd > MOTOR_MAX_SPEED) {
        motor_spd = MOTOR_MAX_SPEED;
    }
    motor_a_set(MOTOR_REVERSE, motor_spd);
}