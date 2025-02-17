#include "my_smartcalc.h"

void count_credit_annuity(double sum, double rate, int term, double* res) {
  double monthly_rate = rate / 100 / 12;
  *res = sum * (monthly_rate * pow(1 + monthly_rate, term)) /
         (pow(1 + monthly_rate, term) - 1);
}
// int calc_term_months(int term, int term_period) { return term * term_period;
// }

void count_credit_difference(double sum, double rate, int term, double* res,
                             double* first_pay, double* last_pay) {
  double monthly_rate = rate / 100 / 12;
  double monthly_pay = sum / term;
  *first_pay = 0;
  *last_pay = 0;
  *res = 0;
  for (int i = 0; i < term; i++) {
    double principal_rate = sum * monthly_rate;
    if (i == 0) *first_pay = monthly_pay + principal_rate;
    if (i == term - 1) *last_pay = monthly_pay + principal_rate;
    *res += monthly_pay + principal_rate;
    sum -= monthly_pay;
  }
}
