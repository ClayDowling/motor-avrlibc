#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Controller) {
  RUN_TEST_CASE(Controller, setup_byDefault_callsMotorSwitchAndPinInit);
  RUN_TEST_CASE(Controller, setup_byDefault_initializesMotorState)
  RUN_TEST_CASE(Controller, setup_byDefault_setsLastCheckedToCurrentTimer);

  // loop
  RUN_TEST_CASE(Controller, loop_whenSwitchIsTrue_setsDirectionToDown);
  RUN_TEST_CASE(
      Controller,
      loop_whenDirectionIsDownAndDurationExceeded_turnsDownMotorOffUpMotorOnDirectionToUp);

  // state_position_zero
  RUN_TEST_CASE(Controller,
                statePositionZero_byDefault_setsDirectionUpAndTurnsMotorsUp);
  RUN_TEST_CASE(
      Controller,
      statePositionZero_byDefault_turnsOffDownMotorWaitsTurnsOnUpMotor);

  // state_switch_on
  RUN_TEST_CASE(Controller,
                stateSwitchOn_whenMaxSet_turnsUpOffDownOnSetsDirectionDown);
  RUN_TEST_CASE(
      Controller,
      stateSwitchOn_whenDurationUnset_setsDurationToCurrentTimerMinusLastCheck);
  RUN_TEST_CASE(
      Controller,
      stateSwitchOn_whenDurationIsUnset_setsDurationToTimerValueAndLastCheckedToCurrentTimerValue);
  RUN_TEST_CASE(Controller,
                stateSwitchOn_byDefault_turnsUpMotorOffWaitsTurnsDownMotorOn);
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
