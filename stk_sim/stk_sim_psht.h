#ifndef STOCK_SIM_PORTFOLIO_STOCK_H
#define STOCK_SIM_PORTFOLIO_STOCK_H

#include "stk_sim.h"

struct PSTOCK_HASHTABLE {
    struct Stock **pstocks_buckets;
    unsigned capacity;
};



#endif // STOCK_SIM_PORTFOLIO_STOCK_H