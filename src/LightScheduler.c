#include "LightScheduler.h"
#include "TimeService.h"
#include "LightController.h"
#include <stdio.h>
#include <stdbool.h>

enum
{
    UNUSED = -1,
    TURN_OFF, TURN_ON,
    MAX_EVENTS = 128
};

typedef struct {
    int id;
    int event;
    Day day;
    int minuteOfDay;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create() 
{
    scheduledEvent.id = UNUSED;
    
    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy() 
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

static void operateLight(ScheduledLightEvent* scheduledEvent)
{
    if (scheduledEvent->event == TURN_ON)
        LightController_On(scheduledEvent->id);
    else if (scheduledEvent->event == TURN_OFF)
        LightController_Off(scheduledEvent->id);
}

static bool itsWeekend(Day today, Day scheduled)
{
    return 
    (
        (
            (today == SATURDAY)
            ||
            (today == SUNDAY)
        )
        &&
        (scheduled == WEEKEND)

    );
}

static bool itsNotWeekend(Day today, Day scheduled)
{
    return 
    (
        (today != SATURDAY)
        &&
        (today != SUNDAY)
        &&
        (scheduled == WEEKDAY)
    );
}

static bool LightRespondsToday(Day today, Day scheduled)
{
    return (
       (scheduled == EVERYDAY)
       ||
       (today == scheduled)
       ||
       itsWeekend(today, scheduled)
       ||
       itsNotWeekend(today, scheduled)    
    );
    
}

static void processEventDueNow(Time* time, ScheduledLightEvent* scheduledEvent)
{
    if (scheduledEvent->id == UNUSED)
        return;
    if (!LightRespondsToday(time->dayOfWeek, scheduledEvent->day))
        return;
    if (time->minuteOfDay != scheduledEvent->minuteOfDay)
        return;    
    
    operateLight(scheduledEvent);
}

void LightScheduler_WakeUp(void)  
{
    Time time;
    TimeService_GetTime(&time);
    
    processEventDueNow(&time, &scheduledEvent);
}

void LightScheduler_ScheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.day = day;
    scheduledEvent.id = id;
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    LightScheduler_ScheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    LightScheduler_ScheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
