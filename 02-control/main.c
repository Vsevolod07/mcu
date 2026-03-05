#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "stdio-task/stdio-task.h"
#include "protocol-task/protocol-task.h"
#include "led-task/led-task.h"
#include "stdio.h"

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

void version_callback(const char* args)
{
	printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void led_on_callback(const char* args)
{
    led_task_state_set(1);
    printf("Led is enabled\n");
}

void led_off_callback(const char* args)
{
    led_task_state_set(0);
    printf("Led is disabled\n");
}

void led_blink_callback(const char* args)
{
    led_task_state_set(2);
    printf("Led blinks\n");
}

void led_blink_set_period_ms_callback(const char* args)
{
    uint period_ms = 0;
    sscanf(args, "%u", &period_ms);
    if(period_ms == 0)
    {
        printf("Error: period of action is zero\n");
        return;
    } 
    led_task_set_blink_period_ms(period_ms);
}

void help_callback(const char* args);

api_t device_api[] =
{
    {"help", help_callback, "List of commands"},
    {"set_period", led_blink_set_period_ms_callback, "Set a period of blinking"},
    {"on", led_on_callback, "turn on led"},
    {"off", led_off_callback, "turn off led"},
    {"blink", led_blink_callback, "make led blink"},
	{"version", version_callback, "get device name and firmware version"},
	{NULL, NULL, NULL},
};

void help_callback(const char* args)
{
    int i = 0;
    while(device_api[i].command_name != NULL)
    {
        printf("Command: %s, Destination: %s\n",  device_api[i].command_name, device_api[i].command_help);
        i++;
    }
}

int main()
{
    stdio_init_all();
    stdio_task_init();
    led_task_init();
    protocol_task_init(device_api);
    while (1)
{
    protocol_task_handle(stdio_task_handle());
    led_task_handle();
}
}