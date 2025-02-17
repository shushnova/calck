#include "my_smartcalc.h"

#include <stdio.h>
char *func_name[] = {"sin",  "asin", "acos", "cos", "tan",
                     "atan", "mod",  "ln",   "log", "sqrt"};
char *operators[] = {"-", "+", "*", "/", "^", "(", ")"};

int my_smartcalc(char *str, double *res, double x) {
  list_leksem infix_list = {0};
  list_leksem postfix_list = {0};
  postfix_list.leksnum = -1;
  infix_list.leksnum = -1;
  int status = pars_leks(str, &infix_list, x);
  if (status == OK) {
    status = convert_to_postfix(&infix_list, &postfix_list);

    if (status == OK) {
      status = calc_postfix(&postfix_list, res);
    }
  }
  return status;
}
int pars_leks(char *str, list_leksem *list, double res) {
  leksem temp = {};
  int status = OK;
  for (; *str != '\0' && status == OK; str++) {
    if (*str == '.')
      status = ERROR;
    else if (isdigit(*str)) {
      int point = 0;
      temp.name = "num";
      temp.value = atof(str);
      temp.type = L_NUM;
      pushh(list, temp);
      while (isdigit(*str) || *str == '.') {
        if (*str == '.') point++;

        str++;
      }
      if (point > 1) {
        status = ERROR;
        break;
      }
      str--;
    } else if (isalpha(*str)) {
      if (*str == 'm' || *str == 's' || *str == 'c' || *str == 'a' ||
          *str == 't' || *str == 'l') {
        char tmp[5] = {0};
        int k = 0;
        while (*str >= 'a' && *str <= 'z' && *str != 'x') {
          if (k >= 5) status = ERROR;
          tmp[k++] = *str++;
        }
        str--;
        for (int i = 0; i < 10; i++) {
          if (strcmp(func_name[i], tmp) == 0) {
            temp.name = func_name[i];
          }
        }

        if (temp.name == NULL) status = ERROR;

        temp.value = 0;
        temp.type = L_FUNC;
        if (temp.name && strcmp(temp.name, "mod") == 0) temp.type = L_ADD;
        pushh(list, temp);
      } else if (*str == 'x') {
        temp.name = "x";
        temp.value = res;
        temp.type = L_X;
        pushh(list, temp);
      } else
        status = ERROR;
    }

    else if (strchr("+-*/^()", *str)) {
      if (*str == '+' || *str == '-') {
        if (list->leksnum == -1 || list->leksmass[list->leksnum].type == L_O_BR)
          temp.type = L_UNARY;
        else
          temp.type = L_ADD;
      }
      if (*str == '*' || *str == '/') temp.type = L_MUL;
      if (*str == '^') temp.type = L_POW;
      if (*str == '(') temp.type = L_O_BR;
      if (*str == ')') temp.type = L_C_BR;
      char tmp[2] = {*str, '\0'};
      for (int i = 0; i < 7; i++) {
        if (strcmp(operators[i], tmp) == 0) {
          temp.name = operators[i];
        }
      }
      temp.value = 0;
      pushh(list, temp);
    }

    else
      status = ERROR;
  }
  return status;
}

void pushh(list_leksem *list, leksem temp) {
  list->leksnum++;
  list->leksmass[list->leksnum].type = temp.type;
  list->leksmass[list->leksnum].value = temp.value;
  list->leksmass[list->leksnum].name = temp.name;
}

leksem popp(list_leksem *list) {
  leksem buff = {0};
  buff = list->leksmass[list->leksnum];

  list->leksnum--;
  return buff;
}

int convert_to_postfix(list_leksem *list, list_leksem *postfix) {
  list_leksem temp = {0};
  temp.leksnum = -1;
  int status = OK;

  for (int i = 0; i <= list->leksnum && status == OK; i++) {
    if (list->leksmass[i].type == L_NUM || list->leksmass[i].type == L_X) {
      if (list->leksmass[i + 1].type == L_FUNC) {
        status = ERROR;
      }

      else
        pushh(postfix, list->leksmass[i]);
    }

    if (list->leksmass[i].type == L_ADD || list->leksmass[i].type == L_MUL ||
        list->leksmass[i].type == L_POW || list->leksmass[i].type == L_UNARY) {
      while (list->leksmass[i].type <= temp.leksmass[temp.leksnum].type &&
             temp.leksnum != -1) {
        if (list->leksmass[i].type == L_POW &&
            (temp.leksmass[temp.leksnum].type == L_POW ||
             temp.leksmass[temp.leksnum].type == L_UNARY)) {
          break;
        }
        pushh(postfix, popp(&temp));
      }
      pushh(&temp, list->leksmass[i]);
    }

    if (list->leksmass[i].type == L_O_BR &&
        list->leksmass[i + 1].type == L_C_BR) {
      status = ERROR;
    }
    if (list->leksmass[i].type == L_O_BR || list->leksmass[i].type == L_FUNC) {
      pushh(&temp, list->leksmass[i]);
    }

    if (list->leksmass[i].type == L_C_BR && status == OK) {
      while (temp.leksmass[temp.leksnum].type != L_O_BR && temp.leksnum != -1) {
        pushh(postfix, popp(&temp));
      }
      if (temp.leksnum == -1) {
        status = ERROR;
      } else {
        popp(&temp);
        if (list->leksmass[i].type == L_FUNC) {
          pushh(postfix, popp(&temp));
        }
      }
    }
  }
  while (temp.leksnum != -1) {
    if (temp.leksmass[temp.leksnum].type == L_O_BR) {
      status = ERROR;
    }

    pushh(postfix, popp(&temp));
  }

  return status;
}
int calc_postfix(list_leksem *postfix, double *res) {
  list_leksem temp = {0};
  temp.leksnum = -1;
  int status = OK;
  double x_1, x_2;
  leksem temp_leksem = {L_NUM, 0, NULL};
  for (int i = 0; i <= postfix->leksnum; i++) {
    if (postfix->leksmass[i].type == L_NUM ||
        postfix->leksmass[i].type == L_X) {
      pushh(&temp, postfix->leksmass[i]);
    }
    if (postfix->leksmass[i].type == L_ADD ||
        postfix->leksmass[i].type == L_MUL ||
        postfix->leksmass[i].type == L_POW) {
      if (temp.leksnum == -1) {
        status = ERROR;
      } else {
        x_2 = popp(&temp).value;
      }
      if (temp.leksnum == -1 && status == OK) {
        status = ERROR;
      } else {
        x_1 = popp(&temp).value;
      }
      if (strcmp(postfix->leksmass[i].name, "+") == 0) *res = x_1 + x_2;
      if (strcmp(postfix->leksmass[i].name, "-") == 0) *res = x_1 - x_2;
      if (strcmp(postfix->leksmass[i].name, "*") == 0) *res = x_1 * x_2;
      if (strcmp(postfix->leksmass[i].name, "/") == 0) *res = x_1 / x_2;
      if (strcmp(postfix->leksmass[i].name, "^") == 0) *res = pow(x_1, x_2);
      if (strcmp(postfix->leksmass[i].name, "mod") == 0) *res = fmod(x_1, x_2);
      temp_leksem.value = *res;
      pushh(&temp, temp_leksem);
    }
    if (postfix->leksmass[i].type == L_UNARY ||
        postfix->leksmass[i].type == L_FUNC) {
      if (temp.leksnum == -1)
        status = ERROR;
      else
        x_1 = popp(&temp).value;
      if (strcmp(postfix->leksmass[i].name, "-") == 0) *res = -x_1;
      if (strcmp(postfix->leksmass[i].name, "+") == 0) *res = x_1;
      if (strcmp(postfix->leksmass[i].name, "sin") == 0) *res = sin(x_1);
      if (strcmp(postfix->leksmass[i].name, "cos") == 0) *res = cos(x_1);
      if (strcmp(postfix->leksmass[i].name, "tan") == 0) *res = tan(x_1);
      if (strcmp(postfix->leksmass[i].name, "sqrt") == 0) *res = sqrt(x_1);
      if (strcmp(postfix->leksmass[i].name, "ln") == 0) *res = log(x_1);
      if (strcmp(postfix->leksmass[i].name, "log") == 0) *res = log10(x_1);
      if (strcmp(postfix->leksmass[i].name, "acos") == 0) *res = acos(x_1);
      if (strcmp(postfix->leksmass[i].name, "asin") == 0) *res = asin(x_1);
      if (strcmp(postfix->leksmass[i].name, "atan") == 0) *res = atan(x_1);
      temp_leksem.value = *res;
      pushh(&temp, temp_leksem);
    }
  }
  if (temp.leksnum == -1) {
    status = ERROR;
  } else
    *res = popp(&temp).value;
  if (temp.leksnum != -1) status = ERROR;
  return status;
}
