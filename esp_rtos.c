#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// GPIO Definitions
#define LED_WHITE   GPIO_NUM_5
#define LED_RED     GPIO_NUM_18
#define LED_BLUE    GPIO_NUM_4
#define LED_YELLOW  GPIO_NUM_16
#define LED_GREEN   GPIO_NUM_2

// Structure for passing task parameters
typedef struct {
    gpio_num_t gpio;
    TickType_t delay_ms;
    const char *name;
} LedTaskConfig;

// Task configurations
LedTaskConfig whiteLED  = {LED_WHITE, 5000, "WHITE"};
LedTaskConfig redLED    = {LED_RED,   4000, "RED"};
LedTaskConfig blueLED   = {LED_BLUE,  3000, "BLUE"};
LedTaskConfig yellowLED = {LED_YELLOW,2000, "YELLOW"};
LedTaskConfig greenLED  = {LED_GREEN, 1000, "GREEN"};

// Generic LED Task
void ledTask(void *pvParameters)
{
    LedTaskConfig *config = (LedTaskConfig *)pvParameters;

    gpio_reset_pin(config->gpio);
    gpio_set_direction(config->gpio, GPIO_MODE_OUTPUT);

    bool state = false;

    while (1)
    {
        state = !state;
        gpio_set_level(config->gpio, state);

        printf("%s LED %s\n",
               config->name,
               state ? "ON" : "OFF");

        vTaskDelay(pdMS_TO_TICKS(config->delay_ms));
    }
}

void app_main(void)
{
    printf("Starting FreeRTOS Multi-LED Application...\n");

    xTaskCreate(ledTask,
                "White_LED_Task",
                2048,
                &whiteLED,
                2,
                NULL);

    xTaskCreate(ledTask,
                "Red_LED_Task",
                2048,
                &redLED,
                2,
                NULL);

    xTaskCreate(ledTask,
                "Blue_LED_Task",
                2048,
                &blueLED,
                2,
                NULL);

    xTaskCreate(ledTask,
                "Yellow_LED_Task",
                2048,
                &yellowLED,
                2,
                NULL);

    xTaskCreate(ledTask,
                "Green_LED_Task",
                2048,
                &greenLED,
                2,
                NULL);
}
