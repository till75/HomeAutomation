#ifdef TEST
#include "unity.h"
#include "LightControllerSpy.h"

void setUp(void)
{
    LightController_Create();
}

void tearDown(void)
{
    LightController_Destroy();
}

void test_LightControllerSpy_Create(void)
{
    TEST_ASSERT_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

void test_LightControllerSpy_RememberTheLastLightIdControlled(void)
{
    LightController_On(10);
    TEST_ASSERT_EQUAL(10, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}
#endif // TEST
