#include <stdlib.h>

#include "mock.h"
#include "mock_timer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Mock);

void FUNCTION_A(int x) { mock_register_call_with(FUNCTION_A, x); }

void FUNCTION_B(int y) { mock_register_call_with(FUNCTION_B, y); }

TEST_SETUP(Mock) { mock_init(); }

TEST_TEAR_DOWN(Mock) {}

TEST(Mock, mockCalled_whenAandB_returnsTrue) {

  FUNCTION_A(1);
  FUNCTION_B(2);

  TEST_ASSERT_TRUE(mock_called_inorder(FUNCTION_A, FUNCTION_B));
}

TEST(Mock, mockCalled_whenAButNotB_returnsFalse) {
  FUNCTION_A(1);

  TEST_ASSERT_FALSE(mock_called_inorder(FUNCTION_A, FUNCTION_B));
}

TEST(Mock, mockCalledWith_byDefault_returnsValueOfCallParameter) {
  FUNCTION_A(7);
  TEST_ASSERT_EQUAL(7, mock_was_called_with(FUNCTION_A));
}

TEST(Mock, timerValueWillReturn_givenOneValue_timerValueWillReturnOneValue) {
  timer_value_will_return(1, 1);
  TEST_ASSERT_EQUAL(1, timer_value());
  TEST_ASSERT_EQUAL(0, timer_value());
}

TEST(Mock, timerValueWillReturn_givenTwoValues_timerValueWillReturnTwoValues) {
  timer_value_will_return(2, 3, 7);
  TEST_ASSERT_EQUAL(3, timer_value());
  TEST_ASSERT_EQUAL(7, timer_value());
  TEST_ASSERT_EQUAL(0, timer_value());
}
