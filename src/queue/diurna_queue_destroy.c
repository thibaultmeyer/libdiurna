#include <stdlib.h>
#include "diurna_queue.h"

void diurna_queue_destroy(struct s_diurna_queue *queue) {
    if (queue != NULL) {
        pthread_mutex_destroy(&queue->lock);

        free(queue);
    }
}
