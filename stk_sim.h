#ifndef _STKSIM_H
#define _STKSIM_H

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define NAME_MAX 20
#define MAX_BALANCE DBL_MAX
#define LOAN_MAX 32767

struct Wallet;
struct Stock;
struct Portfolio;
struct PortfolioStock;
struct Market;
struct Loan;

struct Wallet *wallets;

double generate_value();
void m_display_ticker(const struct Market *m);
struct Stock * m_find_stock(const struct Market *m, const char *sym);

void s_update(struct Stock *stk);
double s_calc_diff(const double prev, const double curr);
int s_bad_event(struct Stock *stk);
int s_good_event(struct Stock *stk);
void s_listall(const struct Stock *stk);

void w_add_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares);
void w_remove_stock(struct Wallet *w, const struct Stock *stk);
void w_update_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares);
void w_buy(struct Wallet *w, const struct Market *m, const char *sym, const unsigned shares);
void w_copy_port(struct Wallet *w, struct PortfolioStock **new_port_stocks, const unsigned np_size);
void w_sell(struct Wallet *w, const char *sym, const unsigned shares);
void w_sellall(struct Wallet *w, const char *sym);
void w_show_bal(struct Wallet *w);
double w_get_bal(struct Wallet *w);
void w_set_bal(struct Wallet *w, const int val);
void w_delete_all(struct Wallet *w);

void pf_copy(struct Portfolio *pf, struct PortfolioStock **new_port_stocks, const unsigned np_size);
void pf_add_stock(struct Portfolio *pf, const struct Stock *stk, const unsigned shares);
void pf_remove_stock(struct Portfolio *pf, const char *sym);
struct Stock * pf_find_stock(const struct Portfolio *pf, const char *sym);
void pf_update_stock(struct Portfolio *pf);
void pf_delete_stocks(struct Portfolio *pf);
void pf_delete_all(struct Portfolio *pf);

void print_err_msg(FILE *fp, const char *msg);

#endif // _STKSIM_H
