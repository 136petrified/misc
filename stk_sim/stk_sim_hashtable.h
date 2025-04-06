#ifndef STK_SIM_HASHTABLE_H
#define STK_SIM_HASHTABLE_H

#include "stk_sim.h"

struct STOCK_SIM_HASHTABLE {
    struct Stock **stocks_buckets;
    unsigned capacity;
};

struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_init(const unsigned capacity);
unsigned STOCK_SIM_HASHTABLE_hash(const char *stk_sym);
struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_insert(struct STOCK_SIM_HASHTABLE *table, struct Stock *stk);
struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_remove(struct STOCK_SIM_HASHTABLE *table, const char *sym);
struct Stock * STOCK_SIM_HASHTABLE_find(struct STOCK_SIM_HASHTABLE *table, const char *sym);
struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_destroy(struct STOCK_SIM_HASHTABLE *table);

#endif // STK_SIM_HASHTABLE_H