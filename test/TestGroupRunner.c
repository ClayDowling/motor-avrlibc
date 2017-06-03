#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Controller) {
  RUN_TEST_CASE(Controller, setup_byDefault_callsMotorSwitchAndPinInit);
  RUN_TEST_CASE(Controller, loop_byDefault_setsMotorSpeed);
  RUN_TEST_CASE(Controller, loop_byDefault_setsMotorDirectionToForward);
  RUN_TEST_CASE(Controller, loop_byDefault_calledReverseOffBeforeForwardOn);
}

TEST_GROUP_RUNNER(Mock) {
  RUN_TEST_CASE(Mock, mockCalled_whenAandB_returnsTrue);
  RUN_TEST_CASE(Mock, mockCalled_whenAButNotB_returnsFalse);
  RUN_TEST_CASE(Mock, mockCalledWith_byDefault_returnsValueOfCallParameter);
}
