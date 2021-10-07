#include <stdlib.h>
#include <string.h>
#include "diurna_queue.h"

struct s_diurna_queue *diurna_queue_initialize(void) {
    struct s_diurna_queue *queue = malloc(sizeof(struct s_diurna_queue));
    if (queue == NULL) {
        return (NULL);
    }

    memset(queue, 0, sizeof(struct s_diurna_queue));
    pthread_mutex_init(&queue->lock, NULL);

    return (queue);
}
