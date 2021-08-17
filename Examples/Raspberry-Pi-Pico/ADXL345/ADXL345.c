#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// Registers for ADXL345
#define ADXL345_ADDRESS         (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB   (0x32)

static int16_t accelerometer_data[3];

void i2c_write(int addr, uint8_t reg, uint8_t val)
{
    uint8_t data[2];
    data[0] = reg;
    data[1] = val;
    i2c_write_blocking(I2C_PORT, addr, data, sizeof(data), false);
}

void i2c_read(int addr, uint8_t reg, size_t size, uint8_t *val)
{
    i2c_write_blocking(I2C_PORT, addr, &reg, 1, false);
    i2c_read_blocking(I2C_PORT, addr, val, size, false);
}

void init_adxl345()
{
    uint8_t data = 0;

    i2c_write(ADXL345_ADDRESS, 0x31, 0x0B);   // 13-bit mode  +_ 16g
    i2c_write(ADXL345_ADDRESS, 0x2D, 0x08);   // Power register


    i2c_write(ADXL345_ADDRESS, 0x1E, 0x00);   // x
    i2c_write(ADXL345_ADDRESS, 0x1F, 0x00);   // Y
    i2c_write(ADXL345_ADDRESS, 0x20, 0x05);   // Z

    // Check to see if it worked!
    i2c_read(ADXL345_ADDRESS, 0X00, 1, &data);
    if(data==0xE5)
        printf("Success\n");
    else
        printf("Fail\n");
}

void read_adxl345() 
{
    uint8_t bytes[6];
    memset(bytes,0,6);

    // Read 6 bytes from the ADXL345
    i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
    // Unpack data
    for (int i=0;i<3;++i) {
        accelerometer_data[i] = (int16_t)bytes[2*i] + (((int16_t)bytes[2*i + 1]) << 8);
    }
}

int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    memset(accelerometer_data, 0, sizeof(accelerometer_data));
    init_adxl345();
    puts("Peripherals initialized\n");

    while(1)
    {
        read_adxl345();
        //3.9mg/LSB scale factor in 13-bit mode
        printf("RAW: %d\t%d\t%d\n",accelerometer_data[0], accelerometer_data[1], accelerometer_data[2]);
        printf("ACCEL: %f\t%f\t%f\n",
                        ((float)accelerometer_data[0])*3.9/1000,
                        ((float)accelerometer_data[1])*3.9/1000,
                        ((float)accelerometer_data[2])*3.9/1000);
        sleep_ms(1000);
    }

}

