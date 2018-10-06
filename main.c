#include <stdio.h>
#include <stdlib.h>
#include "bme280.h"
//#include "bme280_51.h"

int main(int argc, char *argv[])
{
    //uint8_t reg_data[] ={0x4C,0xD1,0x00,0x84,0xFB,0x00,0x94,0x9D};
    char* p;
    uint8_t calib_data1[]={0x85,0x6E,0x8C,0x67,0x32,0x00,0x46,0x92,0x37,0xD6,0xD0,0x0B,0x8A,0x1F,0xE3,0xFF,0xF9,0xFF,0x0C,0x30,0x20,0xD1,0x88,0x13,0x00,0x4B};
    uint8_t calib_data2[]={0x45,0x01,0x00,0x1A,0x27,0x03,0x1E};
    //struct bme280_uncomp_data uncomp_data = {322784,548608,39448};
    struct bme280_uncomp_data uncomp_data = {0};
    //bme280_uncomp_data2 uncomp_data2 = {0};
    struct bme280_data comp_data;
    //bme280_data2 comp_data2;
    struct bme280_dev dev;
    if(argc <4) return 1;
    uncomp_data.pressure=strtol(argv[1],&p,10);
    uncomp_data.temperature=strtol(argv[2],&p,10);
    uncomp_data.humidity=strtol(argv[3],&p,10);
    //printf("%d\n",argc);
    //printf("Hello world!\n");
    //bme280_parse_sensor_data(reg_data, &uncomp_data);
    //printf("%d %d %d\n",uncomp_data.temperature,uncomp_data.humidity,uncomp_data.pressure);
    //bme280_parse_sensor_data2(reg_data, &uncomp_data2);
    //printf("%d %d %d\n",uncomp_data2.temperature,uncomp_data2.humidity,uncomp_data2.pressure);
    parse_temp_press_calib_data(calib_data1, &dev);
    parse_humidity_calib_data(calib_data2, &dev);
    //printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",dev.calib_data.dig_T1,dev.calib_data.dig_T2,dev.calib_data.dig_T3,dev.calib_data.dig_P1,dev.calib_data.dig_P2,dev.calib_data.dig_P3,dev.calib_data.dig_P4,dev.calib_data.dig_P5,dev.calib_data.dig_P6,dev.calib_data.dig_P7,dev.calib_data.dig_P8,dev.calib_data.dig_P9,dev.calib_data.dig_H1,dev.calib_data.dig_H2,dev.calib_data.dig_H3,dev.calib_data.dig_H4,dev.calib_data.dig_H5,dev.calib_data.dig_H6);
    bme280_compensate_data(BME280_ALL, &uncomp_data, &comp_data, &dev.calib_data);
    printf("%.2f %.2f %.2f \n",comp_data.temperature,comp_data.humidity,comp_data.pressure/100);
    //bme280_compensate_data2(BME280_ALL, &uncomp_data2, &comp_data2);
    //printf("%d %d %d\n",comp_data2.temperature,comp_data2.humidity,comp_data2.pressure);
    return 0;
}
