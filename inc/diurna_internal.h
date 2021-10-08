#ifndef LIBDIURNA_INTERNAL_H
# define LIBDIURNA_INTERNAL_H

# include "diurna.h"

#if defined _WIN32 && defined USE_WINTHREAD

#  define WIN32_LEAN_AND_MEAN

#  include <Windows.h>
#  include <processthreadsapi.h>

typedef HANDLE THREAD;

# else

#  include <pthread.h>

typedef pthread_t THREAD;
# endif

/**
 * Message used internally by Diurna.
 */
typedef struct s_diurna_log_message {
    struct s_diurna_log_message *next;
    enum e_diurna_log_level     level;
    struct timeval              time;
    char                        *message;
}                 s_diurna_log_message;

/**
 * Message queue.
 */
typedef struct s_diurna_queue {
    pthread_mutex_t             lock;
    struct s_diurna_log_message *newest;
    struct s_diurna_log_message *oldest;
}                 s_diurna_queue;

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
 * Take the oldest message from the queue.
 *
 * @param queue The queue to use
 * @return The oldest message from the queue. If the queue is empty, NULL will be returned
 */
struct s_diurna_log_message *diurna_queue_dequeue(struct s_diurna_queue *queue);

/**
 * Destroy the given message queue.
 *
 * @param queue The message queue to destroy
 */
void diurna_queue_destroy(struct s_diurna_queue *queue);

/**
 * Initialize message queue.
 *
 * @return The initialized message queue, otherwise, NULL
 */
struct s_diurna_queue *diurna_queue_initialize(void);

/**
 * Add a new message to the queue.
 *
 * @param queue The queue to use
 * @param msg The message to add
 */
void diurna_queue_queue(struct s_diurna_queue *queue, struct s_diurna_log_message *msg);

/**
 * Thread - Log consumer.
 *
 * @param arg Thread argument
 * @return zero
 */
void *log_consumer_thread(void *arg);

#endif //LIBDIURNA_INTERNAL_H
