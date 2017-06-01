#include <stdbool.h>

#include "controller.h"
#include "mock_motor.h"
#include "mock_switch.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Controller);

TEST_SETUP(Controller) {
  motor_mock_init();
  switch_mock_init();
}

TEST_TEAR_DOWN(Controller) {}

TEST(Controller, setup_byDefault_callsMotorSwitchAndPinInit) {
  setup();
  TEST_ASSERT_EQUAL(true, motor_speed_init_called());
  TEST_ASSERT_EQUAL(true, motor_forward_init_called());
  TEST_ASSERT_EQUAL(true, motor_reverse_init_called());
  TEST_ASSERT_EQUAL(true, switch_init_called());
}
