#ifndef LIBDIURNA_INTERNAL_H
# define LIBDIURNA_INTERNAL_H

#if defined _WIN32 && defined USE_WINTHREAD

#  define WIN32_LEAN_AND_MEAN

#  include <Windows.h>
#  include <processthreadsapi.h>

typedef HANDLE THREAD;

# else

#  include <pthread.h>

typedef pthread_t THREAD;
# endif

# include "queue/diurna_queue.h"

/**
 * Diurna context.
 */
typedef struct s_diurna_context {
    char                    *app_name;
    enum e_diurna_log_level log_level;
    THREAD                  log_consumer_thread;
    struct s_diurna_queue   *msg_queue;
    f_appender              appender[32];
}                 s_diurna_context;

/**
 * Handle to the global Diurna context.
 */
extern s_diurna_context *gl_diurna_ctx_handle;

/**
 * Thread - Log consumer.
 *
 * @param arg Thread argument
 * @return zero
 */
void *log_consumer_thread(void *arg);

#endif //LIBDIURNA_INTERNAL_H
