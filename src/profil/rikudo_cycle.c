#include <linux/perf_event.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "rikudo_cycle.h"
#include "rikudo_cfg.h"

#ifdef RIKUDO_CFG_CYCLE

typedef struct {
    uint64_t c[RIKUDO_SUBSYS_SZ];
    uint64_t n[RIKUDO_SUBSYS_SZ];
    uint64_t cur;
    uint64_t tot_c;
    uint64_t tot_n;
    int      fd;
} cycle_t;

static cycle_t cycles;

void rikudo_cycle_init(void)
{
    struct perf_event_attr pea;

    memset(&cycles, 0, sizeof(cycle_t));
    memset(&pea, 0, sizeof(struct perf_event_attr));

    pea.type            = PERF_TYPE_HARDWARE;
    pea.config          = PERF_COUNT_HW_CPU_CYCLES;
    pea.disabled        = 1;
    pea.inherit         = 0;
    pea.enable_on_exec  = 0;
    pea.size            = sizeof(struct perf_event_attr);

    cycles.fd = syscall(__NR_perf_event_open, &pea, 0, -1, -1, 0);
    ioctl(cycles.fd, PERF_EVENT_IOC_ENABLE);
}

static inline uint64_t rikudo_cycle_read(void)
{
    uint64_t value = 0;

    if (cycles.fd > 0 && read(cycles.fd, &value, sizeof(value)) == sizeof(value)) {
        return value;
    }

    return 0;
}

static inline const char* rikudo_cycle_subsys_string_get(uint32_t s)
{
    switch (s) {
        case RIKUDO_SUBSYS_STACK_PUSH:
            return "rikudo_stack_push";
        case RIKUDO_SUBSYS_STACK_POP:
            return "rikudo_stack_pop";
        case RIKUDO_SUBSYS_STACK_EMPTY:
            return "rikudo_stack_is_empty";
        case RIKUDO_SUBSYS_CONNEX:
            return "rikudo_connex";
        default:
            return NULL;
    }
}

void rikudo_cycle_start(void)
{
    cycles.cur = rikudo_cycle_read();
}

void rikudo_cycle_stop(uint32_t s)
{
    uint64_t n = rikudo_cycle_read() - cycles.cur;

    cycles.c[s] += n;
    cycles.n[s]++;
    cycles.tot_c += n;
    cycles.tot_n++;
}

void rikudo_cycle_dump(void)
{
    uint32_t i = 0;

    for (i = RIKUDO_SUBSYS_STACK_PUSH; i < RIKUDO_SUBSYS_SZ; ++i) {
        printf("%-30s %-20lu %-20.2f %-20lu %-20.2f\n",
               rikudo_cycle_subsys_string_get(i),
               cycles.c[i], ((float)cycles.c[i] / (float)cycles.tot_c) * 100,
               cycles.n[i], ((float)cycles.n[i] / (float)cycles.tot_n) * 100);
    }
    printf("%-30s %-20lu %-20i %-20lu %-20i\n", "total",
           cycles.tot_c, 100, cycles.tot_n, 100);
}

#else /* RIKUDO_CFG_CYCLE */

void rikudo_cycle_init(void) { }
void rikudo_cycle_start(void) { }
void rikudo_cycle_stop(uint32_t s) { (void)s; }
void rikudo_cycle_dump(void) { }

#endif
