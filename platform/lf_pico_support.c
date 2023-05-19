#ifdef PLATFORM_PICO

#include "lf_pico_support.h"
#include "platform.h"
#include "utils/util.h"
#include "tag.h"

/**
 * Enter a critical section where logical time and the event queue are guaranteed
 * to not change unless they are changed within the critical section.
 * this can be implemented by disabling interrupts.
 * Users of this function must ensure that lf_init_critical_sections() is
 * called first and that lf_critical_section_exit() is called later.
 * @return 0 on success, platform-specific error number otherwise.
 */
int lf_critical_section_enter() {
    return 0;
}

/**
 * Exit the critical section entered with lf_lock_time().
 * @return 0 on success, platform-specific error number otherwise.
 */
int lf_critical_section_exit() {
    return 0;
}

/**
 * Notify any listeners that an event has been created.
 * The caller should call lf_critical_section_enter() before calling this function.
 * @return 0 on success, platform-specific error number otherwise.
 */
int lf_notify_of_event() {
    return 0;
}

/**
 * Initialize the LF clock. Must be called before using other clock-related APIs.
 */
void lf_initialize_clock(void) {
}

/**
 * Fetch the value of an internal (and platform-specific) physical clock and
 * store it in `t`.
 *
 * Ideally, the underlying platform clock should be monotonic. However, the
 * core lib tries to enforce monotonicity at higher level APIs (see tag.h).
 *
 * @return 0 for success, or -1 for failure
 */
int lf_clock_gettime(instant_t* t) {
    return 0;
}

/**
 * Pause execution for a given duration.
 * 
 * @return 0 for success, or -1 for failure.
 */
int lf_sleep(interval_t sleep_duration) {
    return 0;
}

/**
 * @brief Sleep until the given wakeup time.
 * 
 * @param wakeup_time The time instant at which to wake up.
 * @return int 0 if sleep completed, or -1 if it was interrupted.
 */
int lf_sleep_until_locked(instant_t wakeup_time) {
    return 0;
}

#endif // PLATFORM_PICO

