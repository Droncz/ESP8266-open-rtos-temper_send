#ifndef __SSD1306_MY_H__
#define __SSD1306_MY_H__

#include "config.h"

void ssd1306_init_my(void);
void ssd1306_task(void *pvParameters);
void scrolling_timer(TimerHandle_t h);

#endif  // __SSD1306_MY_H__