#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define EPS 0.0000001

enum leksem_type {
  L_NUM = 1,
  L_X,
  L_O_BR,
  L_ADD,
  L_MUL,
  L_POW,
  L_FUNC,
  L_UNARY,
  L_C_BR,
  L_ALL
};
enum status { OK, ERROR };

typedef struct {
  int type;
  double value;
  char *name;
} leksem;

typedef struct {
  leksem leksmass[255];
  int leksnum;
} list_leksem;

int my_smartcalc(char *str, double *res, double x);
int pars_leks(char *str, list_leksem *list, double res);
int convert_to_postfix(list_leksem *list, list_leksem *postfix);
void pushh(list_leksem *list, leksem);
leksem popp(list_leksem *list);
int calc_postfix(list_leksem *postfix, double *res);
void count_credit_annuity(double sum, double rate, int term, double *res);
void count_credit_difference(double sum, double rate, int term, double *res,
                             double *first_pay, double *last_pay);
