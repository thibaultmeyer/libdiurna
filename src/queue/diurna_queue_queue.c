#include <stdlib.h>
#include "diurna_queue.h"

void diurna_queue_queue(struct s_diurna_queue *queue, struct s_diurna_log_message *msg) {
    if (queue == NULL || msg == NULL) {
        return;
    }

    pthread_mutex_lock(&queue->lock);

    if (queue->newest == NULL) {
        queue->newest = msg;
    } else {
        queue->newest->next = msg;
        queue->newest       = msg;
    }

    if (queue->oldest == NULL) {
        queue->oldest = queue->newest;
    }

    pthread_mutex_unlock(&queue->lock);
}
