#ifndef LIBDIURNA_INTERNAL_H
# define LIBDIURNA_INTERNAL_H

# include "diurna.h"

#if defined _WIN32 && defined USE_WINTHREAD

#  define WIN32_LEAN_AND_MEAN

#  include <Windows.h>
#  include <processthreadsapi.h>

typedef HANDLE THREAD;
typedef HANDLE MUTEX;

#  define DIURNA_LOCK_WAIT_FOR(lock_instance)  WaitForSingleObject(lock_instance, INFINITE)
#  define DIURNA_LOCK_RELEASE(lock_instance)   ReleaseMutex(lock_instance)
#  define DIURNA_LOCK_DESTROY(lock_instance)   CloseHandle(lock_instance)

# else

#  include <pthread.h>

typedef pthread_t       THREAD;
typedef pthread_mutex_t MUTEX;

#  define DIURNA_LOCK_WAIT_FOR(lock_instance)  pthread_mutex_lock(&lock_instance)
#  define DIURNA_LOCK_RELEASE(lock_instance)   pthread_mutex_unlock(&lock_instance)
#  define DIURNA_LOCK_DESTROY(lock_instance)   pthread_mutex_destroy(&lock_instance)
# endif

# define DIURNA_MAX_APPENDER 32

/**
 * Message used internally by Diurna.
 */
typedef struct s_diurna_log_message {
    struct s_diurna_log_message *next;
    enum e_diurna_log_level     level;
    struct timeval              time;
    char                        *message;
}                       s_diurna_log_message;

/**
 * Message queue.
 */
typedef struct s_diurna_queue {
    MUTEX                       lock;
    struct s_diurna_log_message *newest;
    struct s_diurna_log_message *oldest;
}                       s_diurna_queue;

typedef struct s_diurna_appender_file_ctx {
    char *output_filename;
    char *current_filename;
    char *current_date;
}                       s_diurna_appender_file_ctx;

/**
 * Diurna context.
 */
typedef struct s_diurna_context {
    char                     *app_name;
    enum e_diurna_log_level  log_level;
    THREAD                   log_consumer_thread;
    struct s_diurna_queue    *msg_queue;
    struct s_diurna_appender *appender[DIURNA_MAX_APPENDER];
}                       s_diurna_context;

/**
 * Handle to the global Diurna context.
 */
extern s_diurna_context *gl_diurna_ctx_handle;

/**
 * Takes the oldest message from the queue.
 *
 * @param queue The queue to use
 * @return The oldest message from the queue. If the queue is empty, NULL will be returned
 */
struct s_diurna_log_message *diurna_queue_dequeue(struct s_diurna_queue *queue);

/**
 * Destroys the given message queue.
 *
 * @param queue The message queue to destroy
 */
void diurna_queue_destroy(struct s_diurna_queue *queue);

/**
 * Initializes message queue.
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


/**
 * Appender - Console - Write.
 *
 * @param appender_ctx The appender context
 * @param app_name The application name
 * @param log_level The log level (ie : DIURNA_LOGLEVEL_INFO)
 * @param tv The current time
 * @param log_msg The current message
 */
void diurna_appender_console_write(void *const appender_ctx,
                                   const char *app_name,
                                   enum e_diurna_log_level log_level,
                                   const struct timeval *tv,
                                   const char *log_msg);

/**
 * Appender - File - Write.
 *
 * @param appender_ctx The appender context
 * @param app_name The application name
 * @param log_level The log level (ie : DIURNA_LOGLEVEL_INFO)
 * @param tv The current time
 * @param log_msg The current message
 */
void diurna_appender_file_write(void *appender_ctx,
                                const char *app_name,
                                enum e_diurna_log_level log_level,
                                const struct timeval *tv,
                                const char *log_msg);

/**
 * Appender - File - Destroy.
 *
 * @param appender_ctx The appender context
 */
void diurna_appender_file_destroy(void *appender_ctx);

# if defined HAVE_SYSLOG

/**
 * Appender - Syslog - Write.
 *
 * @param appender_ctx The appender context
 * @param app_name The application name
 * @param log_level The log level (ie : DIURNA_LOGLEVEL_INFO)
 * @param tv The current time
 * @param log_msg The current message
 */
void diurna_appender_syslog_write(void *const appender_ctx,
                                  const char *app_name,
                                  enum e_diurna_log_level log_level,
                                  const struct timeval *tv,
                                  const char *log_msg);

# endif

#if defined WIN32
/**
 * Suspends the execution of the calling thread until either at
 * least the time specified has elapsed.
 *
 * @param ns The number of nanoseconds to wait
 */
BOOLEAN nanosleep(LONGLONG ns);
#endif

#endif //LIBDIURNA_INTERNAL_H
