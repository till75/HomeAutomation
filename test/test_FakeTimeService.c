#ifdef TEST
#include "unity.h"
#include "FakeTimeService.h"
void setUp(void) 
{
    TimeService_Create();
}
void tearDown(void){}

void test_FakeTimeService_Create(void)
{
    Time time;
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
    TEST_ASSERT_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

void test_FakeTimeService_Set(void)
{
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL(42, time.minuteOfDay);
    TEST_ASSERT_EQUAL(SATURDAY, time.dayOfWeek);
}
#endif // TEST
