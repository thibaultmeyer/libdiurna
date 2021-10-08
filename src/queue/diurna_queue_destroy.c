#include <stdlib.h>
#include "diurna_internal.h"

void diurna_queue_destroy(struct s_diurna_queue *queue) {
    if (queue != NULL) {
        // Remove and free remaining message from the queue
        while (queue->oldest != NULL) {
            struct s_diurna_log_message *msg = diurna_queue_dequeue(queue);
            if (msg != NULL) {
                free(msg->message);
                free(msg);
            }
        }

        // Destroy mutex
        pthread_mutex_destroy(&queue->lock);

        // Free allocated queue
        free(queue);
    }
}
