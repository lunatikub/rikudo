#ifndef RIKUDO_CYCLE_H_
# define RIKUDO_CYCLE_H_

enum {
    RIKUDO_SUBSYS_STACK_PUSH,
    RIKUDO_SUBSYS_STACK_POP,
    RIKUDO_SUBSYS_STACK_EMPTY,
    RIKUDO_SUBSYS_CONNEX,
    RIKUDO_SUBSYS_SZ,
};

void rikudo_cycle_init(void);
void rikudo_cycle_start(void);
void rikudo_cycle_stop(uint32_t s);
void rikudo_cycle_dump(void);

#endif /* !RIKUDO_CYCLE_H_ */
