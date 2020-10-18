#ifndef DELAY_H
#define DELAY_H

#define delay_us(d) SDK_DelayAtLeastUs(d, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY)
#define delay_ms(d) SDK_DelayAtLeastUs(d * 1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY)


#endif


