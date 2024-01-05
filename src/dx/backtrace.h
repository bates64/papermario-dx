#ifndef BACKTRACE_H
#define BACKTRACE_H

/**
 * @brief Walk the stack and return the current call stack
 *
 * This function will analyze the current execution context,
 * walking the stack and returning informations on the active
 * call frames.
 *
 * This function adheres to POSIX specification. It does not
 * allocate memory so it is safe to be called even in the
 * context of low memory conditions or possibly corrupted heap.
 *
 * If called within an interrupt or exception handler, the function
 * is able to correctly walk backward the interrupt handler and
 * show the context even before the exception was triggered.
 *
 * @param buffer    Empty array of pointers. This will be populated with pointers
 *                  to the return addresses for each call frame.
 * @param size      Size of the buffer, that is, maximum number of call frames
 *                  that will be walked by the function.
 * @return          Number of call frames walked (at most, size).
 */
int backtrace(void **buffer, int size);

/** @brief Print a backtrace. */
void debug_backtrace(void);

#endif
