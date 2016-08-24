
#include "rikudo_stat.h"
#include "rikudo_cfg.h"

#ifdef RIKUDO_CFG_STAT

void rikudo_stat_init(rikudo_stat_t *stat)
{
    memset(stat, 0, sizeof(rikudo_stat_t));
}

#else

void rikudo_stat_init(rikudo_stat_t *stat) { (void)stat; }

#endif
