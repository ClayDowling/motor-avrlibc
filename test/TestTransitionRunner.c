#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Transition) {
  // state_position_zero
  RUN_TEST_CASE(Transition,
                statePositionZero_byDefault_setsDirectionUpAndTurnsMotorsUp);
  RUN_TEST_CASE(
      Transition,
      statePositionZero_byDefault_turnsOffDownMotorWaitsTurnsOnUpMotor);

  // state_switch_on
  RUN_TEST_CASE(
      Transition,
      stateSwitchOn_whenDurationSet_turnsUpOffDownOnSetsDirectionDown);
  RUN_TEST_CASE(
      Transition,
      stateSwitchOn_whenDurationUnset_setsDurationToCurrentTimerMinusLastCheck);
  RUN_TEST_CASE(
      Transition,
      stateSwitchOn_whenDurationIsUnset_setsDurationToTimerValueAndLastCheckedToCurrentTimerValue);
  RUN_TEST_CASE(Transition,
                stateSwitchOn_byDefault_turnsUpMotorOffWaitsTurnsDownMotorOn);
}