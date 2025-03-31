#ifndef _STKSIM_H
#define _STKSIM_H

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

constexpr int NAME_MAX = 20;
constexpr int STOCK_SYMBOL_MAX = 5;
constexpr double MAX_BALANCE = DBL_MAX;
constexpr int LOAN_MAX = 32767;

struct Wallet;
struct Stock;
struct Portfolio;
struct PortfolioStock;
struct Market;
struct Loan;

struct Wallet *wallets;

double generate_value();

// Market
struct Market * m_init(struct Stock *avail_stocks, unsigned n_stocks, const int u_speed);
void m_display_ticker(const struct Market *m);
void m_add_stock(struct Market *m, struct Stock *stk);
void m_remove_stock(struct Market *m, const char *sym);
void m_update_stock(struct Market *m, const struct Stock *stk_src);
struct Stock * m_find_stock(const struct Market *m, const char *sym);

// Stock
struct Stock * s_init(const char *name, const char *sym, const double val,
                      const int status, const unsigned avail_shares, const unsigned total_shares);
void s_update(struct Stock *stk_dest, const struct Stock *stk_src);
double s_calc_diff(const double prev, const double curr);
int s_bad_event(struct Stock *stk);
int s_good_event(struct Stock *stk);
struct Stock * s_delete(struct Stock *stk);
void s_listall(const struct Stock *stk);

// Wallet
void w_add_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares);
void w_remove_stock(struct Wallet *w, const struct Stock *stk);
void w_update_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares);
void w_buy(struct Wallet *w, const struct Market *m, const char *sym, const unsigned shares);
void w_sell(struct Wallet *w, const char *sym, const unsigned shares);
void w_sellall(struct Wallet *w, const char *sym);
void w_show_bal(struct Wallet *w);
inline double w_get_bal(struct Wallet *w);
inline void w_set_bal(struct Wallet *w, const int val);
struct Wallet * w_delete(struct Wallet *w);

// Portfolio
void pf_add_stock(struct Portfolio *pf, const struct Stock *stk, const unsigned shares);
void pf_remove_stock(struct Portfolio *pf, const char *sym);
struct PortfolioStock * pf_find_stock(const struct Portfolio *pf, const char *sym);
void pf_update_stock(struct Portfolio *pf, const struct PortfolioStock *ps_src);
struct Portfolio * pf_delete_stocks(struct Portfolio *pf);
struct Portfolio * pf_delete(struct Portfolio *pf);

// PortfolioStock
struct PortfolioStock * ps_init(const char *name, const char *sym, const unsigned shares);
void ps_update_stock(struct PortfolioStock *ps_dest, const struct PortfolioStock *ps_src);
struct PortfolioStock * ps_delete(struct Portfolio *pf);

void print_err_msg(FILE *fp, const char *msg);

#endif // _STKSIM_H
