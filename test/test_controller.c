#include <stdbool.h>
#include <stdio.h>

#include "controller.h"
#include "mock.h"
#include "mock_switch.h"
#include "mock_timer.h"
#include "motor.h"
#include "switch.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Controller);

TEST_SETUP(Controller) {
  mock_init();
  switch_state_will_return(false);
  MOTOR_STATE.direction = NODIRECTION;
  MOTOR_STATE.last_check = UNSET;
  MOTOR_STATE.duration = UNSET;
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
  TEST_ASSERT_EQUAL(0, MOTOR_STATE.last_check);
  TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
  TEST_ASSERT_EQUAL(UNSET, MOTOR_STATE.duration);
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
  TEST_ASSERT_TRUE(mock_called_inorder(2, motor_down_off, motor_up_on));
  TEST_ASSERT_EQUAL(MOTOR_SPEED, mock_was_called_with(motor_speed_set));
}

TEST(Controller, stateSwitchOn_whenMaxSet_turnsUpOffDownOnSetsDirectionDown) {
  state_switch_on();
  TEST_ASSERT_TRUE(mock_was_called(motor_up_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_down_on));
  TEST_ASSERT_TRUE(mock_called_inorder(2, motor_up_off, motor_down_on));
  TEST_ASSERT_EQUAL(DOWN, MOTOR_STATE.direction);
}

TEST(Controller,
     stateSwitchOn_whenDurationUnset_setsDurationToCurrentTimerMinusLastCheck) {
  timer_value_will_return(1, 10);
  MOTOR_STATE.last_check = 7;
  state_switch_on();
  TEST_ASSERT_EQUAL(3, MOTOR_STATE.duration);
}

TEST(Controller, loop_whenSwitchIsTrue_setsDirectionToDown) {
  MOTOR_STATE.last_check = 9;
  MOTOR_STATE.direction = UP;
  switch_state_will_return(true);
  loop();
  TEST_ASSERT_EQUAL(DOWN, MOTOR_STATE.direction);
}

TEST(Controller, setup_byDefault_setsLastCheckedToCurrentTimer) {
  timer_value_will_return(1, 75);
  setup();
  TEST_ASSERT_EQUAL(75, MOTOR_STATE.last_check);
}

TEST(
    Controller,
    loop_whenDirectionIsDownAndDurationExceeded_turnsDownMotorOffUpMotorOnDirectionToUp) {
  MOTOR_STATE.direction = DOWN;
  MOTOR_STATE.last_check = 10;
  MOTOR_STATE.duration = 100;
  timer_value_will_return(2, 120, 121); // State change will call timer again
  loop();
  TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
  TEST_ASSERT_TRUE(mock_called_inorder(2, motor_down_off, motor_up_on));
}

TEST(
    Controller,
    stateSwitchOn_whenDurationIsUnset_setsDurationToTimerValueAndLastCheckedToCurrentTimerValue) {
  timer_value_will_return(2, 120, 121);
  MOTOR_STATE.last_check = 10;
  MOTOR_STATE.duration = UNSET;
  state_switch_on();
  TEST_ASSERT_EQUAL(110, MOTOR_STATE.duration);
  TEST_ASSERT_EQUAL(121, MOTOR_STATE.last_check);
}

TEST(Controller, stateSwitchOn_byDefault_turnsUpMotorOffWaitsTurnsDownMotorOn) {
  state_switch_on();
  TEST_ASSERT_TRUE(
      mock_called_inorder(3, motor_up_off, timer_wait, motor_down_on));
}

TEST(Controller,
     statePositionZero_byDefault_turnsOffDownMotorWaitsTurnsOnUpMotor) {
  state_position_zero();
  TEST_ASSERT_TRUE(
      mock_called_inorder(3, motor_down_off, timer_wait, motor_up_on));
}
