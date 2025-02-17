#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_smartcalc.h"

int main() {
  double res = 0.0;
  double x = 1.0;
  char *str = "xsin";

  list_leksem infix_list = {0};
  list_leksem postfix_list = {0};
  postfix_list.leksnum = -1;
  infix_list.leksnum = -1;
  // double first_pay = 0.0;
  // double last_pay = 0.0;
  // count_credit_annuity(100000, 10, 36, &res);
  // printf("result %lf\n", res);
  // count_credit_difference(100000, 10, 36, &res, &first_pay, &last_pay);
  // printf("result %lf %lf %lf\n", res, first_pay, last_pay);
  int status = pars_leks(str, &infix_list, x);
  printf("status1 %d\n", status);
  if (status == OK) status = convert_to_postfix(&infix_list, &postfix_list);
  printf("status2 %d\n", status);
  if (status == OK) status = calc_postfix(&postfix_list, &res);
  printf("status3 %d\n", status);
  for (int i = 0; i <= infix_list.leksnum; i++) {
    //     printf("value %lf\n", infix_list.leksmass[i].value);
    //     printf("name %s\n", infix_list.leksmass[i].name);
    //     printf("type %d\n\n", infix_list.leksmass[i].type);

    printf("%lf\n", postfix_list.leksmass[i].value);
    printf("%s\n", postfix_list.leksmass[i].name);
    printf("%d\n\n", postfix_list.leksmass[i].type);
  }

  // // printf ("tugjbjb%s , %d\n", infix_list.leksmass[0].value,
  // infix_list.leksmass[0].type);
  //   printf("status_main %d\n", status);
  printf("result %lf", res);
  return 0;
}