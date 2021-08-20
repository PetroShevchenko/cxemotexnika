#include <string.h>
#include <stdio.h>
#include "ADXL345.h"

// Registers for ADXL345
#define ADXL345_ADDRESS         (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB   (0x32)

static void i2c_write(i2c_inst_t *i2c, int addr, uint8_t reg, uint8_t val)
{
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    i2c_write_blocking(i2c, addr, data, sizeof(data), false);
}

static void i2c_read(i2c_inst_t *i2c, int addr, uint8_t reg, size_t size, uint8_t *val)
{
    i2c_write_blocking(i2c, addr, &reg, 1, false);
    i2c_read_blocking(i2c, addr, val, size, false);
}

bool init_adxl345(i2c_inst_t *i2c)
{
    uint8_t data = 0;
    if (i2c == NULL)
        return false;

    i2c_write(i2c, ADXL345_ADDRESS, 0x31, 0x0B);   // 13-bit mode  +_ 16g
    i2c_write(i2c, ADXL345_ADDRESS, 0x2D, 0x08);   // Power register


    i2c_write(i2c, ADXL345_ADDRESS, 0x1E, 0x00);   // x
    i2c_write(i2c, ADXL345_ADDRESS, 0x1F, 0x00);   // Y
    i2c_write(i2c, ADXL345_ADDRESS, 0x20, 0x05);   // Z

    // Check to see if it worked!
    i2c_read(i2c, ADXL345_ADDRESS, 0X00, 1, &data);
    if(data==0xE5)
        return true;
    else
        return false;
}

bool read_adxl345(i2c_inst_t *i2c, int16_t *accelerometer_data, size_t size) 
{
    uint8_t bytes[6];
    memset(bytes,0,6);

    if (accelerometer_data == NULL
        || i2c == NULL
        || size != (3 * sizeof(int16_t)))
        return false;

    // Read 6 bytes from the ADXL345
    i2c_read(i2c, ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
    // Unpack data
    for (int i=0;i<3;++i) {
        accelerometer_data[i] = (int16_t)bytes[2*i] + (((int16_t)bytes[2*i + 1]) << 8);
    }
    return true;
}
