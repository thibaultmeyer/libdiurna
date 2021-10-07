#ifndef LIBDIURNA_QUEUE_INTERNAL_H
# define LIBDIURNA_QUEUE_INTERNAL_H

# include "../diurna.h"
# include <pthread.h>

/**
 * Message used internally by Diurna.
 */
typedef struct s_diurna_log_message {
    struct s_diurna_log_message *next;
    enum e_diurna_log_level     level;
    struct timeval              time;
    char                        *message;
} s_diurna_log_message;

/**
 * Message queue.
 */
typedef struct s_diurna_queue {
    pthread_mutex_t             lock;
    struct s_diurna_log_message *newest;
    struct s_diurna_log_message *oldest;
} s_diurna_queue;

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

#endif //LIBDIURNA_QUEUE_INTERNAL_H
