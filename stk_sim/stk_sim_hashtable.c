#include "stk_sim_hashtable.h"

struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_init(const unsigned capacity) {
    struct STOCK_SIM_HASHTABLE *table = (struct STOCK_SIM_HASHTABLE *) malloc(capacity * sizeof(struct Stock));
    return table;
}

struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_insert(struct STOCK_SIM_HASHTABLE *table, struct Stock *stk) {
    unsigned bucket = STOCK_SIM_HASHTABLE_hash(stk->sym);
    stk->next = table->stocks_buckets[bucket];
    table->stocks_buckets[bucket] = stk;
    return table;
}
