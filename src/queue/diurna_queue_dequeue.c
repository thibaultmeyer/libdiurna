#include <stdlib.h>
#include "diurna_internal.h"

struct s_diurna_log_message *diurna_queue_dequeue(struct s_diurna_queue *queue) {
    if (queue == NULL) {
        return (NULL);
    }

    pthread_mutex_lock(&queue->lock);

    struct s_diurna_log_message *msg = queue->oldest;
    if (msg != NULL) {
        queue->oldest = msg->next;
    } else {
        queue->oldest = NULL;
    }

    if (queue->oldest == NULL) {
        queue->newest = queue->oldest;
    }

    pthread_mutex_unlock(&queue->lock);

    return (msg);
}
