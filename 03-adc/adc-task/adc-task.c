#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "adc-task.h"

const uint ADC_GPIO_PIN = 26;
const uint ADC_CHANNEL = 0;
const uint ADC_TEMP_CHANNEL = 4;

void adc_task_init()
{
    adc_init();
    adc_gpio_init(ADC_GPIO_PIN);
    adc_set_temp_sensor_enabled(true);
}

float adc_task_read_voltage()
{
    adc_select_input(ADC_CHANNEL);
    uint16_t counts = adc_read();
    float voltage = (counts * 3.3f) / 4095;
    
    return voltage;
}

float adc_task_read_temp(void)
{
    adc_select_input(ADC_TEMP_CHANNEL);
    uint16_t counts = adc_read();
    float voltage = (counts * 3.3f) / 4095;
    float temp = 27.0f - (voltage - 0.706f) / 0.001721f;
    
    return temp;
}