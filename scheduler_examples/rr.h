#ifndef RR_H
#define RR_H

#include <stdint.h>

// Forward declaration
struct queue;

void rr_scheduler(uint32_t current_time_ms, struct queue *rq, void **cpu_task);

#endif //RR_H