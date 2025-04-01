#ifndef STK_SIM_HASHTABLE_H
#define STK_SIM_HASHTABLE_H

struct STOCK_SIM_HASHTABLE;


struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_init(struct STOCK_SIM_HASHTABLE *table, const struct Stock *stk);
unsigned STOCK_SIM_HASHTABLE_hash(const char *stk_sym);
struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_insert(struct STOCK_SIM_HASHTABLE *table, const struct Stock *stk);
struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_remove(struct STOCK_SIM_HASHTABLE *table, const struct Stock *stk);
struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_find(struct STOCK_SIM_HASHTABLE *table, const struct Stock *stk);

#endif // STK_SIM_HASHTABLE_H