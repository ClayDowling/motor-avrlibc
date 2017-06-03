#include <stdbool.h>
#include <stdio.h>

#include "controller.h"
#include "mock.h"
#include "motor.h"
#include "switch.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Controller);

TEST_SETUP(Controller) { mock_init(); }

TEST_TEAR_DOWN(Controller) {}

TEST(Controller, setup_byDefault_callsMotorSwitchAndPinInit) {
  setup();
  TEST_ASSERT_TRUE(mock_was_called(motor_speed_init));
  TEST_ASSERT_TRUE(mock_was_called(motor_forward_init));
  TEST_ASSERT_TRUE(mock_was_called(motor_reverse_init));
  TEST_ASSERT_TRUE(mock_was_called(switch_init));
}

TEST(Controller, loop_byDefault_setsMotorSpeed) {
  loop();
  TEST_ASSERT_EQUAL(MOTOR_SPEED, mock_was_called_with(motor_speed_set));
}

TEST(Controller, loop_byDefault_setsMotorDirectionToForward) {
  loop();
  TEST_ASSERT_TRUE(mock_was_called(motor_reverse_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_forward_on));
}

TEST(Controller, loop_byDefault_calledReverseOffBeforeForwardOn) {
  loop();
  TEST_ASSERT_TRUE(mock_called_inorder(motor_reverse_off, motor_forward_on));
}
