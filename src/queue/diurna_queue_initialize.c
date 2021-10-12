#include <stdlib.h>
#include <string.h>
#include "diurna_internal.h"

struct s_diurna_queue *diurna_queue_initialize(void) {
    struct s_diurna_queue *queue = malloc(sizeof(struct s_diurna_queue) + 1);
    if (queue == NULL) {
        return (NULL);
    }

    memset(queue, 0, sizeof(struct s_diurna_queue));
    int ret = pthread_mutex_init(&queue->lock, NULL);
    if (ret != 0) {
        free(queue);
        return (NULL);
    }

    return (queue);
}
