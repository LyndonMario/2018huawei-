#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "lib_io.h"
#include <string.h>
#include <math.h>
//#define NC 3500
#define k 92.12
void predict_server(char * info[MAX_INFO_NUM], char * data[MAX_DATA_NUM], int data_num, char * filename);

int timecal(int yearbe,int monthbe,int daybe,int hourbe,int minbe,int secbe,int yearend,int monthend,int dayend,int hourend,int minend,int secend);
int pre(int x);
void allot(int* count,char* std,int** allot);
int allotdraw(char* allot,char* save);
#endif
