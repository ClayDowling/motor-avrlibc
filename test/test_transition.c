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

struct motor_state_t MOTOR_STATE;

TEST_GROUP(Transition);

TEST_SETUP(Transition) {
  mock_init();
  switch_state_will_return(false);
  MOTOR_STATE.direction = NODIRECTION;
  MOTOR_STATE.last_check = UNSET;
  MOTOR_STATE.duration = UNSET;
}

TEST_TEAR_DOWN(Transition) {}

TEST(Transition, statePositionZero_byDefault_setsDirectionUpAndTurnsMotorsUp) {
  state_position_zero();
  TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
  TEST_ASSERT_TRUE(mock_was_called(motor_down_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_up_on));
  TEST_ASSERT_TRUE(mock_called_inorder(2, motor_down_off, motor_up_on));
  TEST_ASSERT_EQUAL(MOTOR_SPEED, mock_was_called_with(motor_speed_set));
}

TEST(Transition,
     stateSwitchOn_whenDurationSet_turnsUpOffDownOnSetsDirectionDown) {
  state_switch_on();
  TEST_ASSERT_TRUE(mock_was_called(motor_up_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_down_on));
  TEST_ASSERT_TRUE(mock_called_inorder(2, motor_up_off, motor_down_on));
  TEST_ASSERT_EQUAL(DOWN, MOTOR_STATE.direction);
}

TEST(Transition,
     stateSwitchOn_whenDurationUnset_setsDurationToCurrentTimerMinusLastCheck) {
  timer_value_will_return(1, 10);
  MOTOR_STATE.last_check = 7;
  state_switch_on();
  TEST_ASSERT_EQUAL(3, MOTOR_STATE.duration);
}

TEST(
    Transition,
    stateSwitchOn_whenDurationIsUnset_setsDurationToTimerValueAndLastCheckedToCurrentTimerValue) {
  timer_value_will_return(2, 120, 121);
  MOTOR_STATE.last_check = 10;
  MOTOR_STATE.duration = UNSET;
  state_switch_on();
  TEST_ASSERT_EQUAL(110, MOTOR_STATE.duration);
  TEST_ASSERT_EQUAL(121, MOTOR_STATE.last_check);
}

TEST(Transition, stateSwitchOn_byDefault_turnsUpMotorOffWaitsTurnsDownMotorOn) {
  state_switch_on();
  TEST_ASSERT_TRUE(
      mock_called_inorder(3, motor_up_off, timer_wait, motor_down_on));
}

TEST(Transition,
     statePositionZero_byDefault_turnsOffDownMotorWaitsTurnsOnUpMotor) {
  state_position_zero();
  TEST_ASSERT_TRUE(
      mock_called_inorder(3, motor_down_off, timer_wait, motor_up_on));
}
