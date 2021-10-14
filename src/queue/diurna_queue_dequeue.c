#include <stdlib.h>
#include "diurna_internal.h"

struct s_diurna_log_message *diurna_queue_dequeue(struct s_diurna_queue *queue) {
    if (queue == NULL) {
        return (NULL);
    }

    DIURNA_LOCK_WAIT_FOR(queue->lock);

    struct s_diurna_log_message *msg = queue->oldest;
    if (msg != NULL) {
        queue->oldest = msg->next;
    } else {
        queue->oldest = NULL;
    }

    if (queue->oldest == NULL) {
        queue->newest = queue->oldest;
    }

    DIURNA_LOCK_RELEASE(queue->lock);

    return (msg);
}
