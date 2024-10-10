#ifndef FAKETIMESERVICE_H
#define FAKETIMESERVICE_H
#include "TimeService.h"

void FakeTimeService_SetMinute(int);
void FakeTimeService_SetDay(Day);
int FakeTimeService_GetAlarmPeriod(void);
WakeupCallback FakeTimeService_GetAlarmCallback(void); 

#endif // FAKETIMESERVICE_H
