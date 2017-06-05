#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Controller) {
  RUN_TEST_CASE(Controller, setup_byDefault_callsMotorSwitchAndPinInit);
  RUN_TEST_CASE(Controller, setup_byDefault_initializesMotorState)
  RUN_TEST_CASE(Controller,
                statePositionZero_byDefault_setsDirectionUpAndTurnsMotorsUp);
  RUN_TEST_CASE(Controller,
                stateSwitchOn_whenMaxSet_turnsUpOffDownOnSetsDirectionDown);
  RUN_TEST_CASE(Controller,
                stateSwitchOn_whenMaxUnset_setsMaxToCurrentPosition);
  RUN_TEST_CASE(Controller, loop_whenDirectionIsUp_addsOneToPosition);
  RUN_TEST_CASE(Controller, loop_whenDirectionIsDown_subtractsOneFromPosition);
  RUN_TEST_CASE(Controller, loop_whenSwitchIsTrue_setsDirectionToDown);
}

TEST_GROUP_RUNNER(Mock) {
  RUN_TEST_CASE(Mock, mockCalled_whenAandB_returnsTrue);
  RUN_TEST_CASE(Mock, mockCalled_whenAButNotB_returnsFalse);
  RUN_TEST_CASE(Mock, mockCalledWith_byDefault_returnsValueOfCallParameter);
}
