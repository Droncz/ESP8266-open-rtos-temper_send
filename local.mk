# INC_DIRS += $(ROOT)../ESP_RTOS_SDK/components/esp8266/include
libesphttpd_CFLAGS += -I${IOT_TOOLS}/ESP_RTOS_SDK/components/esp8266/include -I${IOT_TOOLS}/msys32/mingw32/include
libesphttpd_LDFLAGS += -L${IOT_TOOLS}/msys32/mingw32/lib
# mbedtls_CFLAGS += -DMBEDTLS_DEBUG_C
PROGRAM_CFLAGS += -I${IOT_TOOLS}/ESP_RTOS_SDK/components/esp8266/include 
EXTRA_CFLAGS += -I${IOT_TOOLS}/ESP_RTOS_SDK/components/esp8266/include
EXTRA_LDFLAGS += -L${IOT_TOOLS}/ESP_RTOS_SDK/components/esp8266/lib -L${IOT_TOOLS}/msys32/mingw32/lib
ESPTOOL = C:/Python36/Scripts/esptool.py.exe
FLASH_SIZE = 4
ESPPORT = COM5
