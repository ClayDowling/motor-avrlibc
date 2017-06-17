#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Controller) {
  RUN_TEST_CASE(Controller, setup_byDefault_callsMotorSwitchAndPinInit);
  RUN_TEST_CASE(Controller, setup_byDefault_initializesMotorState)
  RUN_TEST_CASE(Controller, setup_byDefault_setsLastCheckedToCurrentTimer);
  RUN_TEST_CASE(Controller, set_byDefault_callsStatePositionZero);

  // loop
  RUN_TEST_CASE(Controller, loop_whenSwitchStateIsTrue_callsstateSwitchOn);
  RUN_TEST_CASE(
      Controller,
      loop_whenDirectionDownAndExpiredLessThanDuration_doNotCallStatePositionZero);
}

TEST_GROUP_RUNNER(Mock) {
  RUN_TEST_CASE(Mock, mockCalled_whenAandB_returnsTrue);
  RUN_TEST_CASE(Mock, mockCalled_whenAButNotB_returnsFalse);
  RUN_TEST_CASE(Mock, mockCalledWith_byDefault_returnsValueOfCallParameter);
  RUN_TEST_CASE(
      Mock, timerValueWillReturn_givenOneValue_timerValueWillReturnOneValue);
  RUN_TEST_CASE(
      Mock, timerValueWillReturn_givenTwoValues_timerValueWillReturnTwoValues);
}
