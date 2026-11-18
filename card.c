#include "card.h"
#include "sys.h"
#include "USART1.h"
#include "USART2.h"
#include "LED.h"

void card_init(void)
{
    usart1_card_init(115200);   /* 读卡线圈 8N1 */
    usart2_voice_init(9600);    /* 语音播报 */
    led_init();                 /* 刷卡指示灯 */
}

/* 刷到新卡读块, 文字就绪后转发给语音模块 */
void card_poll(void)
{
    u8 gbk[16];
    u8 n, i;

    if (usart1_card_uid_ok()) {          /* 0x90: 刷到一张新卡 */
        usart1_card_read_block(4);       /* 下发读块命令拿卡内文字 */
        usart1_card_uid_clr();
        led_toggle();
    }

    if (usart1_card_text_ok()) {         /* 0x91: 文字就绪 */
        n = usart1_card_get_text(gbk);
        if (n > sizeof(gbk)) n = sizeof(gbk);   /* 卡内文字超缓存时截断, 防越界 */
        for (i = 0; i < n; i++) {
            usart2_voice_send_byte(gbk[i]);     /* 转发GBK给语音模块 */
        }
    }
}