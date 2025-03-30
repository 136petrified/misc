#include "stk_sim.h"

struct Wallet {
    char *name;
    double bal;
    struct Portfolio *portfolio;

    int elligible_for_loan;
    struct Loan **loans;
};

struct Stock {
    char *name;
    char *sym;
    double val;
    double diff;
    int status;
    unsigned avail_shares;
    unsigned total_shares;
};

struct Portfolio {
    struct PortfolioStock **stocks;
    unsigned port_size;
    unsigned port_cap;
};

struct PortfolioStock {
    char *name;
    char *sym;
    unsigned owned_shares;
    unsigned total_shares;
};

struct Market {
    struct Stock **avail_stocks;
    unsigned n_stocks;

    int u_speed;
};

struct Loan {
    unsigned amount;
    unsigned fulfilled;
    time_t deadline;
};

void m_display_ticker(const struct Market *m) {
    for (unsigned i = 0, s = m->n_stocks; i < s; ++i) {
        struct Stock *stk = m->avail_stocks[i];

        printf("%-6s %.2lf %.2lf%%\n", stk->sym,
                                     stk->val,
                                     stk->diff);
    }
}

struct Stock * m_find_stock(const struct Market *m, const char *sym) {
    struct Stock **as = m->avail_stocks;

    for (unsigned i = 0, s = m->n_stocks; i < s; ++i) {
        if (sym == as[i]->sym) {
            return as[i];
        }
    }

    return NULL;
}

double generate_value() {
    srand(time(NULL));
    uint64_t ct = (uint64_t) time(NULL);
    unsigned mask = 0x7F;
    unsigned offset = ((unsigned) (~ct ^ mask) & mask) & mask;

    double a = (1 + (rand() % 10)) * ((rand() % 2) ? -1.0 : 1.0);
    double b = ((1 + (rand() % 10)) / 10) * ((rand() % 2) ? -1.0 : 1.0);
    double c = ((rand() + offset) % 64) * ((rand() % 2) ? -1.0 : 1.0);
    double x = rand() % 8;

    return a * sin(b * x + c);
}

void s_update(struct Stock *stk) {
    if (stk == NULL) {
        return;
    }

    double new_val = stk->val + value_generate();

    if (s_bad_event()) {
        stk->val *= 0.02;
    } else if (s_good_event()) {
        stk->val *= 50.0;
    }

    stk->diff = s_calc_diff(stk->val, new_val);
    if (new_val < 0) {
        new_val = 0;
    }
    stk->val = new_val;
}

double s_calc_diff(const double prev, const double curr) {
    if (prev == 0) {
        return curr * 100;
    }

    return (curr / prev - 1) * 100;
}

int s_bad_event() {
    srand((time(NULL)));  // random seed
    int rval = rand();
    return rval % 67 == 0;
}

int s_good_event() {
    srand((time(NULL)));  // random seed
    int rval = rand();
    return rval % 103 == 0;
}

void s_listall(const struct Stock *stk) {
    // TODO: Finish this function
}

void w_add_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares) {
    if (w == NULL || stk == NULL) {
        return;
    }

    struct Portfolio *pf = w->portfolio;
    struct PortfolioStock **new_port_stocks;

    if (pf == NULL) {
        return;
    } else if (pf->port_size == pf->port_cap) { // if portfolio is FULL
        unsigned np_size = pf->port_cap * 2;
        new_port_stocks = (struct PortfolioStock **) malloc(sizeof(struct PortfolioStock *) * np_size);
        w_copy_port(w, new_port_stocks, np_size);
        pf_delete_stocks(pf); // Delete old portfolio stocks
        pf->stocks = new_port_stocks;
    }

    pf_add_stocks(pf);
}

void w_buy(struct Wallet *w, const struct Market *m, const char *sym, const unsigned shares) {
    if (w == NULL || m == NULL) {
        return;
    } else if (w->bal <= 0) {
        return;
    }

    struct Stock *m_stk = m_find_stock(m, sym);

    if (m_stk == NULL) {
        return;
    } else if (shares > m_stk->avail_shares) {
        return;
    }

    double cost = shares * m_stk->val;          // Calculate price
    struct Stock *w_stk = pf_find_stock(w->portfolio, sym); // Find in wallet portfolio

    if (w_stk == NULL) {
        w_add_stock(w, m_stk, shares);                  // Add stock to portfolio if not found
    } else {
        w_update_stock(w, w_stk, shares);               // Otherwise update existing portfolio stock
    }

    // TODO: Finish this function
}

void pf_copy(struct Portfolio *pf, struct PortfolioStocks **new_port_stocks, const unsigned np_size) {
    if (pf == NULL) {
        return;
    } else if (pf->stocks == NULL || new_port_stocks == NULL) {
        return;
    } else if (np_size < pf->port_size) {
        return;
    }

    for (unsigned i = 0, s = pf->port_size; i < s; ++i) {
        new_port_stocks[i] = pf->stocks[i];
    }
}

void pf_add_stock(struct Portfolio *pf, const struct Stock *stk, const unsigned shares) {
    if (pf == NULL) {
        return;
    } else if (pf->stocks == NULL) {
        pf->stocks = (struct PortfolioStock **) malloc(sizeof(struct PortfolioStock *) * 2);
    } else if (pf->port_size == pf->port_cap) { // if portfolio is FULL
        struct PortfolioStock **new_port_stocks;
        unsigned np_size = pf->port_cap * 2;
    
        new_port_stocks = (struct PortfolioStock **) malloc(sizeof(struct PortfolioStock *) * np_size);
        pf_copy(pf, new_port_stocks, np_size);
        pf_delete_stocks(pf); // Delete old portfolio stocks
        pf->stocks = new_port_stocks;
    }

    struct PortfolioStock *ps = (struct PortfolioStock *) malloc(sizeof(struct PortfolioStock));
    ps->name = stk->name;
    ps->sym = stk->sym;
    ps->total_shares = stk->total_shares;
    ps->owned_shares = shares;

    pf->stocks[pf->port_size++] = ps;
}

void pf_remove_stock(struct Portfolio *pf, const char *sym) {
    if (pf == NULL) {
        return;
    }
}

void pf_delete_stocks(struct Portfolio *pf) {
    if (pf == NULL) {
        return;
    }

    for (unsigned i = 0; i < pf->port_size; ++i) {
        free(pf->stocks[i]);                        // Delete all stocks
    }

    free(pf->stocks);                               // Then free the stock array
    pf->stocks = NULL;                              // Set to NULL to avoid double free
}

void pf_delete_all(struct Portfolio *pf) {
    if (pf == NULL) {
        return;
    }

    if (pf->stocks != NULL) {
        pf_delete_stocks(pf);
    }
}