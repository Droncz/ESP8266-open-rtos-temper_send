#include <espressif/esp_common.h>
#include <FreeRTOS.h>
#include <timers.h>
// #include <string.h>
#include <ssd1306/ssd1306.h>

#include "config.h"
#include "ssd1306-my.h"
#include "image.h"

/* Declare device descriptor */
static const ssd1306_t dev = {
    .protocol = PROTOCOL,
#ifdef I2C_CONNECTION
    .i2c_dev.bus      = I2C_BUS,
    .i2c_dev.addr     = ADDR,
#else
    .cs_pin   = CS_PIN,
    .dc_pin   = DC_PIN,
#endif
    .width    = DISPLAY_WIDTH,
    .height   = DISPLAY_HEIGHT
};

/* Local frame buffer */
static uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];
// TimerHandle_t scrol_timer_handle = NULL; // Timer handler

void ssd1306_task(void *pvParameters)
{
    printf("%s: Started user interface task\n", __FUNCTION__);
    vTaskDelay(1000/portTICK_PERIOD_MS);


    if (ssd1306_load_xbm(&dev, image_bits, buffer))
        goto error_loop;

    ssd1306_set_whole_display_lighting(&dev, false);
    bool fwd = false;
    while (1) {
        vTaskDelay(2*SECOND);
        printf("%s: still alive, flipping!\n", __FUNCTION__);
        ssd1306_set_scan_direction_fwd(&dev, fwd);
        fwd = !fwd;
    }

error_loop:
    printf("%s: error while loading framebuffer into SSD1306\n", __func__);
    for(;;){
        vTaskDelay(2*SECOND);
        printf("%s: error loop\n", __FUNCTION__);
    }
}

void scrolling_timer(TimerHandle_t h)
{
    static bool scrol = true ;
    if(scrol)
        ssd1306_start_scroll_hori(&dev, false, 0, 7, FRAME_25);
    else
        ssd1306_stop_scroll(&dev);
    printf("Scrolling status: %s\n", (scrol)? "On" : "Off");
    scrol=!scrol ;
}

void ssd1306_init_my(void)
{

    while (ssd1306_init(&dev) != 0)
    {
        printf("%s: failed to init SSD1306 lcd\n", __func__);
        vTaskDelay(SECOND);
    }

    ssd1306_set_whole_display_lighting(&dev, true);
    vTaskDelay(SECOND);
}