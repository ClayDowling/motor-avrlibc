#include <stdbool.h>
#include <stdio.h>

#include "controller.h"
#include "mock.h"
#include "motor.h"
#include "switch.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Controller);

TEST_SETUP(Controller) {
  mock_init();
  MOTOR_STATE.direction = NODIRECTION;
  MOTOR_STATE.position = UNSET;
  MOTOR_STATE.max_position = UNSET;
}

TEST_TEAR_DOWN(Controller) {}

TEST(Controller, setup_byDefault_callsMotorSwitchAndPinInit) {
  setup();
  TEST_ASSERT_TRUE(mock_was_called(motor_speed_init));
  TEST_ASSERT_TRUE(mock_was_called(motor_up_init));
  TEST_ASSERT_TRUE(mock_was_called(motor_down_init));
  TEST_ASSERT_TRUE(mock_was_called(switch_init));
}

TEST(Controller, setup_byDefault_initializesMotorState) {
  setup();
  TEST_ASSERT_EQUAL(0, MOTOR_STATE.position);
  TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
  TEST_ASSERT_EQUAL(UNSET, MOTOR_STATE.max_position);
}

TEST(Controller, loop_byDefault_setsMotorSpeed) {
  loop();
  TEST_ASSERT_EQUAL(MOTOR_SPEED, mock_was_called_with(motor_speed_set));
}

TEST(Controller, statePositionZero_byDefault_setsDirectionUpAndTurnsMotorsUp) {
  state_position_zero();
  TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
  TEST_ASSERT_TRUE(mock_was_called(motor_down_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_up_on));
  TEST_ASSERT_TRUE(mock_called_inorder(motor_down_off, motor_up_on));
}

TEST(Controller, stateSwitchOn_whenMaxSet_turnsUpOffDownOnSetsDirectionDown) {
  state_switch_on();
  TEST_ASSERT_TRUE(mock_was_called(motor_up_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_down_on));
  TEST_ASSERT_TRUE(mock_called_inorder(motor_up_off, motor_down_on));
  TEST_ASSERT_EQUAL(DOWN, MOTOR_STATE.direction);
}

TEST(Controller, stateSwitchOn_whenMaxUnset_setsMaxToCurrentPosition) {
  MOTOR_STATE.position = 7;
  state_switch_on();
  TEST_ASSERT_EQUAL(7, MOTOR_STATE.max_position);
}

TEST(Controller, loop_whenDirectionIsUp_addsOneToPosition) {
  MOTOR_STATE.position = 0;
  MOTOR_STATE.direction = UP;
  loop();
  TEST_ASSERT_EQUAL(1, MOTOR_STATE.position);
}

TEST(Controller, loop_whenDirectionIsDown_subtractsOneFromPosition) {
  MOTOR_STATE.position = 10;
  MOTOR_STATE.direction = DOWN;
  loop();
  TEST_ASSERT_EQUAL(9, MOTOR_STATE.position);
}
