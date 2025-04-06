#include "stk_sim_hashtable.h"

struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_init(const unsigned capacity) {
    struct STOCK_SIM_HASHTABLE *table = (struct STOCK_SIM_HASHTABLE *) malloc(sizeof(struct STOCK_SIM_HASHTABLE));
    table->stocks_buckets = (struct STOCK_SIM_HASHTABLE *) malloc(capacity * sizeof(struct Stock));
    table->capacity = capacity;
    return table;
}

struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_insert(struct STOCK_SIM_HASHTABLE *table, struct Stock *stk) {
    unsigned bucket = STOCK_SIM_HASHTABLE_hash(stk->sym);
    stk->next = table->stocks_buckets[bucket];
    table->stocks_buckets[bucket] = stk;
    return table;
}

struct STOCK_SIM_HASHTABLE * STOCK_SIM_HASHTABLE_remove(struct STOCK_SIM_HASHTABLE *table, const char *sym) {
    unsigned bucket = STOCK_SIM_HASHTABLE_hash(sym);
    for (struct Stock *curr = table->stocks_buckets[bucket], *prev = NULL; curr != NULL; curr = curr->next) {
        if (sym == curr->sym) {
            prev->next = curr->next;
            free(curr);
            return table;
        }

        prev = curr;
    }

    return table;
}

struct Stock * STOCK_SIM_HASHTABLE_find(struct STOCK_SIM_HASHTABLE *table, const char *sym) {
    unsigned bucket = STOCK_SIM_HASHTABLE_hash(sym);
    for (struct Stock *curr = table->stocks_buckets[bucket]; curr != NULL; curr = curr->next) {
        if (sym == curr->sym) {
            return curr;
        }
    }

    return NULL; // NULL if not found
}
