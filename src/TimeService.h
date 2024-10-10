#ifndef TIMESERVICE_H
#define TIMESERVICE_H
#include "LightScheduler.h"

typedef void (*WakeupCallback)(void);

void TimeService_Create();
void TimeService_Destroy();
void TimeService_GetTime(Time*);
void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback);

#endif // TIMESERVICE_H