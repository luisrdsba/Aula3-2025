#include "mlfq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg.h"

#define TIME_SLICE_MS 500
#define NUM_QUEUES 3

static int current_queue = 0;
static uint32_t time_slice_used = 0;

void mlfq_scheduler(uint32_t current_time_ms, struct queue *rq, void **cpu_task) {

    if (*cpu_task) {
        time_slice_used += TICKS_MS;

        if (time_slice_used >= TIME_SLICE_MS) {
            // Rebaixa para fila de prioridade mais baixa
            if (current_queue < NUM_QUEUES - 1) {
                current_queue++;
            }
            // Recoloca na fila
            // enqueue_pcb(rq, *cpu_task);
            *cpu_task = NULL;
            time_slice_used = 0;
        }
    }

    if (*cpu_task == NULL) {
        // *cpu_task = dequeue_pcb(rq);
        current_queue = 0;  // Reset para fila de maior prioridade
        time_slice_used = 0;
    }
}