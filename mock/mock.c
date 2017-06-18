#include "mock.h"
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CALL_MAX 200
#define MOCK_NOT_CALLED -1

int mock_call_index(void *target);

bool mock_init_called = false;
unsigned int CALL_IDX;
void *called[CALL_MAX];
int argument[CALL_MAX];

void mock_init(void) {
  mock_init_called = true;
  CALL_IDX = 0;
  memset((void *)called, 0, sizeof(called));
}

void mock_register_call(void *mock) {
  if (!mock_init_called) {
    mock_init();
  }
  called[CALL_IDX++] = mock;
}

void mock_register_call_with(void *mock, int arg) {
  if (!mock_init_called) {
    mock_init();
  }
  argument[CALL_IDX] = arg;
  mock_register_call(mock);
}

bool mock_called_inorder(int num, ...) {
  int previous = MOCK_NOT_CALLED;
  int current;
  va_list args;
  void *function;
  bool inorder = true;

  va_start(args, num);
  for (int i = 0; i < num; ++i) {
    function = va_arg(args, void *);
    current = mock_call_index(function);
    if (current <= previous) {
      inorder = false;
      break;
    }
    previous = current;
  }

  va_end(args);
  return inorder;
}

int mock_call_index(void *target) {
  for (int i = 0; i < CALL_IDX; ++i) {
    if (called[i] == target) {
      return i;
    }
  }
  return MOCK_NOT_CALLED;
}

bool mock_was_called(void *target) {
  if (mock_call_index(target) == MOCK_NOT_CALLED)
    return false;
  return true;
}

int mock_was_called_with(void *target) {
  int idx = mock_call_index(target);
  if (idx == MOCK_NOT_CALLED) {
    return MOCK_NOT_CALLED;
  }
  return argument[idx];
}
