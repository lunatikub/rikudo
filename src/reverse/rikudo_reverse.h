#ifndef RIKUDO_REVERSE_H_
# define RIKUDO_REVERSE_H_

void rikudo_reverse_from_html(rikudo_t   *ri,
                              const char *grid,
                              const char *nr_t,
                              const char *trans);

void rikudo_reverse_dump_to_html(rikudo_t *ri,
                                 grid_t   *grid);

#endif /* !RIKUDO_REVERSE_H_ */
