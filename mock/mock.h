#ifndef _MOCK_H_
#define _MOCK_H_

#include <stdbool.h>

void mock_init(void);
bool mock_called_inorder(void *, void *);

/* Used by mocks to handle mock behavior */
void mock_register_call(void *);
void mock_register_call_with(void *, int);

/* Use these in tests to see what was called */
bool mock_was_called(void *);
int mock_was_called_with(void *);

#endif
