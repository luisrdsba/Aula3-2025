//
// Created by luisr on 9/26/2025.
//

#ifndef SJF_H
#define SJF_H


#include <stdint.h>
#include "queue.h"

void sjf_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task);
pcb_t* dequeue_shortest_job(queue_t *rq);

#endif
