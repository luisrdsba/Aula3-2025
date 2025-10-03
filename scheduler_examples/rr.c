#include "rr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg.h"

#define TIME_SLICE_MS 500

void rr_scheduler(uint32_t current_time_ms, struct queue *rq, void **cpu_task) {
    static uint32_t time_slice_used = 0;

    if (*cpu_task) {
        time_slice_used += TICKS_MS;

        if (time_slice_used >= TIME_SLICE_MS) {
            // enqueue_pcb(rq, *cpu_task);
            *cpu_task = NULL;
            time_slice_used = 0;
        }
    }

    if (*cpu_task == NULL) {
        // *cpu_task = dequeue_pcb(rq);
        time_slice_used = 0;
    }
}