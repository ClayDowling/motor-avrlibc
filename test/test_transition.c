#include <stdbool.h>
#include <stdio.h>

#include "controller.h"
#include "mock.h"
#include "mock_switch.h"
#include "mock_timer.h"
#include "motor.h"
#include "state_transition.h"
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
}

TEST_TEAR_DOWN(Transition) {}

// TESTS START HERE

TEST(Transition, stateBottom_byDefault_setsDirectionUpAndTurnsMotorsUp) {
  state_bottom();
  TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
  TEST_ASSERT_TRUE(mock_was_called(motor_down_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_up_on));
  TEST_ASSERT_TRUE(mock_called_inorder(2, motor_down_off, motor_up_on));
  TEST_ASSERT_EQUAL(MOTOR_SPEED, mock_was_called_with(motor_speed_set));
}

TEST(Transition, stateBottom_byDefault_turnsOffDownMotorWaitsTurnsOnUpMotor) {
  state_bottom();
  TEST_ASSERT_TRUE(
      mock_called_inorder(3, motor_down_off, timer_wait, motor_up_on));
}

TEST(Transition, stateBottom_byDefault_setsLastCheckedAfterTimerWait) {
  timer_value_will_return(1, 57);
  state_bottom();
  TEST_ASSERT_TRUE(mock_called_inorder(2, timer_wait, timer_value));
  TEST_ASSERT_EQUAL(57, MOTOR_STATE.last_check);
}

TEST(Transition,
     stateSwitchOn_whenDurationSet_turnsUpOffDownOnSetsDirectionDown) {
  state_switch_on();
  TEST_ASSERT_TRUE(mock_was_called(motor_up_off));
  TEST_ASSERT_TRUE(mock_was_called(motor_down_on));
  TEST_ASSERT_TRUE(mock_called_inorder(2, motor_up_off, motor_down_on));
  TEST_ASSERT_EQUAL(DOWN, MOTOR_STATE.direction);
}

TEST(
    Transition,
    stateSwitchOn_whenDurationIsUnset_setsDurationToTimerValueAndLastCheckedToCurrentTimerValue) {
  timer_value_will_return(1, 121);
  MOTOR_STATE.last_check = 10;
  state_switch_on();
  TEST_ASSERT_EQUAL(121, MOTOR_STATE.last_check);
}

TEST(Transition, stateSwitchOn_byDefault_turnsUpMotorOffWaitsTurnsDownMotorOn) {
  state_switch_on();
  TEST_ASSERT_TRUE(
      mock_called_inorder(3, motor_up_off, timer_wait, motor_down_on));
}

TEST(Transition, stateSwitchOn_whenDurationSet_callsWaitBeforeGettingTime) {
  timer_value_will_return(1, 75);

  state_switch_on();

  TEST_ASSERT_TRUE(mock_called_inorder(2, timer_wait, timer_value));
}
