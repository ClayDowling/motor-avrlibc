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

TEST(Controller, setup_byDefault_setsLastCheckedToCurrentTimer) {
  timer_value_will_return(1, 75);
  setup();
  TEST_ASSERT_EQUAL(75, MOTOR_STATE.last_check);
}

TEST(Controller, setup_byDefault_callsStateBottom) {
  setup();
  TEST_ASSERT_TRUE(mock_was_called(state_bottom));
}

TEST(Controller, loop_whenSwitchStateIsTrue_callsstateSwitchOn) {
  switch_state_will_return(true);

  loop();

  TEST_ASSERT_TRUE(mock_was_called(state_switch_on));
}

TEST(Controller,
     loop_whenDirectionDownAndExpiredLessThanDuration_doNotCallStateBottom) {
  MOTOR_STATE.direction = DOWN;
  MOTOR_STATE.duration = 500;
  MOTOR_STATE.last_check = 10;
  timer_value_will_return(1, 75);

  loop();

  TEST_ASSERT_FALSE(mock_was_called(state_bottom));
}

TEST(Controller,
     loop_whenDirectionDownAndExpiredGreaterThanDuration_callsStateBottom) {
  MOTOR_STATE.direction = DOWN;
  MOTOR_STATE.duration = 500;
  MOTOR_STATE.last_check = 10;

  timer_value_will_return(1, 600);

  loop();

  TEST_ASSERT_TRUE(mock_was_called(state_bottom));
}
