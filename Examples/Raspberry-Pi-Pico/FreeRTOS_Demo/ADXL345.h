#ifndef ADXL345_H
#define ADXL345_H
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

bool init_adxl345(i2c_inst_t *i2c);
bool read_adxl345(i2c_inst_t *i2c, int16_t *accelerometer_data, size_t size);

#endif
