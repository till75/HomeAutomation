#ifndef LIGHTSCHEDULER_H
#define LIGHTSCHEDULER_H

typedef enum Day {
    TIME_UNKNOWN = -2, NONE = -1, EVERYDAY = 10, WEEKDAY, WEEKEND,
    MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
} Day;

typedef struct {
        int minuteOfDay;
        Day dayOfWeek;
} Time;

void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_WakeUp();
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);

#endif // LIGHTSCHEDULER_H
