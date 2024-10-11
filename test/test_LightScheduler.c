#ifdef TEST
#include "unity.h"

#include "LightScheduler.h"
#include "FakeTimeService.h"
#include "LightControllerSpy.h"

static void setTimeTo(int day, int minute)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minute);
}

static void testLightStatus(int id, int level)
{
    TEST_ASSERT_EQUAL(id, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(level, LightControllerSpy_GetLastState());
}


void setUp(void)
{
    LightController_Create();
    LightScheduler_Create();
}

void tearDown(void)
{
    LightScheduler_Destroy();
    LightController_Destroy();
}

void test_LightScheduler_NoChangeToLightsDuringInitialization(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

void test_LightScheduler_NoScheduleNothingHappens(void)
{
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_WakeUp();
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

void test_LightScheduler_ScheduleEverydayNotTimeYet(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1199);
    LightScheduler_WakeUp();
    testLightStatus(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_LightScheduler_ScheduleOnEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(3, LIGHT_ON);
}

void test_LightScheduler_ScheduleOffEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(3, LIGHT_OFF);
}

void test_LightScheduler_ScheduleTuesdayButItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);    
}

void test_LightScheduler_ScheduleTuesdayAndItsTuesday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(3, LIGHT_ON);    
}

void test_LightScheduler_ScheduleWeekendAndItsFriday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);    
}


void test_LightScheduler_ScheduleWeekendAndItsSaturday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(3, LIGHT_ON);    
}

void test_LightScheduler_ScheduleWeekendAndItsSunday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(3, LIGHT_ON);    
}

void test_LightScheduler_ScheduleWeekendAndItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);    
}

void test_LightScheduler_ScheduleWeekdayAndItsSaturday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);    
}

void test_LightScheduler_ScheduleWeekdayAndItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(3, LIGHT_ON);    
}

void test_LightScheduler_ScheduleWeekdayAndItsFriday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_WakeUp();
    testLightStatus(3, LIGHT_ON);    
}


/////////////////////////////////////////////////////////
// "Test the Wiring" - requires that setUp() is empty!
/////////////////////////////////////////////////////////

// void test_LightScheduler_CreateStartsOneMinuteAlarm(void)
// {
//     LightScheduler_Create();
//     TEST_ASSERT_EQUAL_PTR(  (void*)LightScheduler_WakeUp,
//                             (void*)FakeTimeService_GetAlarmCallback()
//                           );
//     TEST_ASSERT_EQUAL(60, FakeTimeService_GetAlarmPeriod());
//     LightScheduler_Destroy();
// }

// void test_LightScheduler_DestroyCancelsOneMinuteAlarm(void)
// {
//     LightScheduler_Create();
//     LightScheduler_Destroy();
//     TEST_ASSERT_EQUAL_PTR(NULL, (void*)FakeTimeService_GetAlarmCallback());
// }


#endif // TEST
