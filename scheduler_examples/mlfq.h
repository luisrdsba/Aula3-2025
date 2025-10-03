#ifndef MLFQ_H
#define MLFQ_H

#include <stdint.h>

// Forward declaration
struct queue;

void mlfq_scheduler(uint32_t current_time_ms, struct queue *rq, void **cpu_task);

#endif //MLFQ_H