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
    struct PortfolioStock *next;
};

struct Market {
    struct Stock *avail_stocks;
    unsigned n_stocks;

    int u_speed;
};

struct Loan {
    unsigned amount;
    unsigned fulfilled;
    time_t deadline;
};

// TODO: Update into linked list
void m_display_ticker(const struct Market *m) {
    // TODO: Also put this in a file for printout
}

struct Stock * m_find_stock(const struct Market *m, const char *sym) {
    
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

void s_update(struct Stock *stk_dest, struct Stock *stk_src) {
    if (stk == NULL) {
        return;
    }

    double new_val = stk->val + generate_value();

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

    pf_add_stock(pf, stk, shares);
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
    w_update_stock(w, m_stk, shares);

    w->bal -= cost;
    m_stk->avail_shares -= shares;
}

void w_update_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares) {
    struct PortfolioStock *ps_src = ps_init(stk->name, stk->sym, shares);
    pf_update_stock(w->portfolio, ps_src);
    ps_src = ps_delete(ps_src);
}

void pf_add_stock(struct Portfolio *pf, const struct Stock *stk, const unsigned shares) {
    if (pf == NULL) {
        return;
    } else if (stk == NULL) {
        return;
    }

    struct PortfolioStock *ps = (struct PortfolioStock *) malloc(sizeof(struct PortfolioStock));

    ps->name = strdup(stk->name);
    ps->sym = strdup(stk->sym);
    ps->owned_shares = shares;
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
            --pf->port_size;
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

void pf_update_stock(struct Portfolio *pf, const struct PortfolioStock *ps_src) {
    if (pf == NULL) {
        return;
    } else if (ps_src == NULL) {
        return;
    }

    struct PortfolioStock *ps_dest = pf_find_stock(pf, ps_src->sym);
    ps_update_stock(ps_dest, ps_src);
}

void ps_update_stock(struct PortfolioStock *ps_dest, const struct PortfolioStock *ps_src) {
    if (ps_dest == NULL || ps_src == NULL) {
        return;
    }

    if (ps_dest->name != NULL) {
        free(ps_dest->name);
    }

    ps_dest->name = strdup(ps_src);

    ps_dest->owned_shares = ps_src->owned_shares;
}

struct Portfolio * pf_delete_stocks(struct Portfolio *pf) {
    if (pf == NULL) {
        return pf;
    } else if (pf->stocks == NULL) {
        return pf;
    }

    for (struct PortfolioStock *curr = pf->stocks; pf->stocks != NULL; curr = pf->stocks) {
        pf->stocks = pf->stocks->next;
        free(curr);
    }

    return pf;
}

void pf_delete(struct Portfolio *pf) {
    if (pf == NULL) {
        return;
    }
}