#include <stdlib.h>
#include "diurna_internal.h"

void diurna_queue_queue(struct s_diurna_queue *queue, struct s_diurna_log_message *msg) {
    if (queue == NULL || msg == NULL) {
        return;
    }

    DIURNA_LOCK_WAIT_FOR(queue->lock);

    if (queue->newest == NULL) {
        queue->newest = msg;
    } else {
        queue->newest->next = msg;
        queue->newest       = msg;
    }

    if (queue->oldest == NULL) {
        queue->oldest = queue->newest;
    }

    DIURNA_LOCK_RELEASE(queue->lock);
}
