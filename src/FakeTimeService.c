#include <stddef.h>
#include "TimeService.h"
#include "FakeTimeService.h"

static Time time;
static WakeupCallback callback;
static int period;

void TimeService_Create()
{
    time.minuteOfDay = TIME_UNKNOWN;
    time.dayOfWeek = TIME_UNKNOWN;
}

void TimeService_GetTime(Time* t)
{
    *t = time;
}

void FakeTimeService_SetMinute(int m)
{
    time.minuteOfDay = m;
}

void FakeTimeService_SetDay(Day d) 
{
    time.dayOfWeek = d;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
    if (cb == callback && period == seconds)
    {
        callback = NULL;
        period = 0;
    }
}

int FakeTimeService_GetAlarmPeriod(void)
{
    return period;
}

WakeupCallback FakeTimeService_GetAlarmCallback(void) 
{
    return callback;
}