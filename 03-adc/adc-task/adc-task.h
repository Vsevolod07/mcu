#pragma once
#include "stdio.h"
#include "pico/stdlib.h"

void adc_task_init();
float adc_task_read_voltage();
float adc_task_read_temp();