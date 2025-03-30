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
    struct PortfolioStock *stocks;
    unsigned port_size;
};

struct PortfolioStock {
    char *name;
    char *sym;
    unsigned owned_shares;
    unsigned total_shares;
    struct PortfolioStock *next;
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

    if (pf == NULL) {
        return;
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

void pf_add_stock(struct Portfolio *pf, const struct Stock *stk, const unsigned shares) {
    if (pf == NULL) {
        return;
    } else if (stk == NULL) {
        return;
    }

    struct PortfolioStock *ps = (struct PortfolioStock *) malloc(sizeof(struct PortfolioStock));

    ps->name = stk->name;
    ps->sym = stk->sym;
    ps->owned_shares = shares;
    ps->total_shares = stk->total_shares;
    ps->next = pf->stocks; // pf->stocks is NULL initially

    pf->stocks = ps;
    ++pf->port_size;
}

void pf_remove_stock(struct Portfolio *pf, const char *sym) {
    if (pf == NULL) {
        return;
    } else if (sym == NULL) {
        return;
    } else if (pf->stocks == NULL) {
        return;
    }

    for (struct PortfolioStock *prev = NULL, *curr = pf->stocks; curr != NULL; curr = curr->next) {
        if (strcmp(sym, curr->sym) == 0) {
            prev->next = curr->next;
            free(curr);
            return;
        }

        prev = curr;
    }
}

struct PortfolioStock * pf_find_stock(const struct Portfolio *pf, const char *sym) {
    if (pf == NULL) {
        return;
    } else if (sym == NULL) {
        return;
    } else if (pf->stocks == NULL) {
        return;
    }

    for (struct PortfolioStock *curr = pf->stocks; curr != NULL; curr = curr->next) {
        if (strcmp(sym, curr->sym) == 0) {
            return curr;
        }
    }

    return NULL;
}

void pf_delete_stocks(struct Portfolio *pf) {
    if (pf == NULL) {
        return;
    } else if (pf->stocks == NULL) {
        return;
    }

    for (struct PortfolioStock *curr = pf->stocks; pf->stocks != NULL; curr = pf->stocks) {
        pf->stocks = pf->stocks->next;
        free(curr);
    }
}

void pf_delete_all(struct Portfolio *pf) {
    if (pf == NULL) {
        return;
    }
}