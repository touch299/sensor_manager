#ifndef SENSOR_H
#define SENSOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 32

typedef struct SensorData{
    char name[NAME_MAX];
    float temperature;
    float humidity;
    struct SensorData *next;
} SensorData;

void add_records(SensorData **records);
void print_list(const SensorData *records);
SensorData *find(SensorData *records,SensorData **prev_out);
int delete_node(SensorData **records);
int update_records(SensorData *records);
int save_to_file(const SensorData *records,const char *filename);
int load_from_file(SensorData **records,const char *filename);
void free_list(SensorData **records);

#endif