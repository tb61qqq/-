#ifndef __MOTOR_H
#define __MOTOR_H

/* ===== 电机软启动参数 =====
 * MOTOR_MAX_SPEED : 匀速时的转速(0~999)，越大转越快
 * MOTOR_RAMP_STEP : 每次提速量(1~999)，越小启动越平滑
 * MOTOR_RAMP_DELAY: 每次提速间隔(ms)，越大启动越慢
 */
#define MOTOR_MAX_SPEED   600
#define MOTOR_RAMP_STEP   1
#define MOTOR_RAMP_DELAY  20

void motor_init(void);
void motor_poll(void);

#endif