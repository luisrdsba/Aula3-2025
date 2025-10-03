#include "sjf.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg.h"



void sjf_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task) {
    if (*cpu_task) {
        (*cpu_task)->ellapsed_time_ms += TICKS_MS;
        if ((*cpu_task)->ellapsed_time_ms >= (*cpu_task)->time_ms) {
            msg_t msg = {
                .pid = (*cpu_task)->pid,
                .request = PROCESS_REQUEST_DONE,
                .time_ms = current_time_ms
            };
            if (write((*cpu_task)->sockfd, &msg, sizeof(msg_t)) != sizeof(msg_t)) {
                perror("write");
            }
            free(*cpu_task);
            *cpu_task = NULL;
        }
    }
    if (*cpu_task == NULL) {
        *cpu_task = dequeue_shortest_job(rq);
    }
}

pcb_t* dequeue_shortest_job(queue_t *rq) {
    if (rq->head == NULL) return NULL;

    queue_elem_t *shortest = rq->head;
    queue_elem_t *current = rq->head;

    // Loop over the list and find the queue element with shortest pcb time
    while (current != NULL) {
        if (current->pcb->time_ms < shortest->pcb->time_ms) {
            shortest = current;
        }
        current = current->next;
    }

    // Remove the queue elem from the list
    queue_elem_t *next_pcb_elem = remove_queue_elem(rq, shortest);

    // Keep a pointer to the next pcb
    pcb_t *next_pcb = next_pcb_elem->pcb;

    // Free the queue element as it is no longer needed
    free(next_pcb_elem);

    return next_pcb;
}
