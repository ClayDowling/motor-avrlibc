#ifndef _MOCK_H_
#define _MOCK_H_

#include <stdbool.h>

void mock_init(void);

/**
 * See if mocks were called in the specified order.
 *
 * @param[in] number The number of mocks being checked for.  If the number
 *                   does not match the number of mocks listed, the results
 *                   are undefined.
 * @param[in] ...    A list of function pointers to look for.
 *
 * @return bool      True if the functions were called in the listed
 *                   order.  False if there were not called or called in a
 *                   different order.
 */
bool mock_called_inorder(int number, ...);

/* Used by mocks to handle mock behavior */

/**
 * Record that a test double was called.
 *
 * @param[in] function Pointer to the function which was called.
 */
void mock_register_call(void *function);

/**
 * Record that a function was called and what it was called with.
 *
 * @param[in] function Pointer to the function which was called.
 * @param[in] argument The argument passed to the function.  This value may
 *                     be retrieved by calling mock_was_called_with
 */
void mock_register_call_with(void *function, int argument);

/* Use these in tests to see what was called */

/**
 * Returns true if the function named was called
 *
 * @param[in] function pointer to function we are checking for.
 *
 * @return bool true if the function was called, false if not.
 */
bool mock_was_called(void *function);

/**
 * Returns the value which a function was called with.
 *
 * @param[in] function to look for.
 *
 * @return int the value the function was called with, -1 if the
 *             function was not called.
 */
int mock_was_called_with(void *function);

#endif
