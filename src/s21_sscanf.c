#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  char *format_pointer = (char *)format;
  char *str_pointer = (char *)str;
  char *start = str_pointer;
  int res = *str ? 0 : -1;  //если строка существует, то 0, если нет -- -1
  va_list arguments;
  va_start(arguments, format);
  while (*format_pointer && res != -1) {
    if (*format_pointer == '%') {
      format_pointer++;
      options_for_sscanf opt = {0};
      opt.base = 10;
      if (*format_pointer == '%') {
        if (*str_pointer == '%') {
          str_pointer++;
          format_pointer++;
        } else
          res = -1;
      } else {
        if (flags_parse(&format_pointer, &opt) == 0) res = -1;
        if (res != -1) {
          if (s21_strspn(format_pointer, SPECIFIERS)) {
            if (specificator_parser(&opt, &str_pointer, arguments,
                                    &format_pointer, &start) == -1)
              res = -1;
            else if (!opt.skip && *(format_pointer - 1) != 'n' &&
                     !opt.float_fail)
              res++;
            if (opt.float_fail) break;
          } else
            break;
        }
      }
    } else {
      if (s21_strchr(SPACE, *format_pointer) != s21_NULL) {
        format_pointer = spaces_skip(format_pointer);
        str_pointer = spaces_skip(str_pointer);
      } else if (*str_pointer == *format_pointer) {
        str_pointer++;
        format_pointer++;
      } else
        break;
    }
  }
  va_end(arguments);
  return res;
}

int flags_parse(char **format, options_for_sscanf *opt) {
  int result = 1;
  check_skip(opt, format);
  sscanf_width(&(opt->width), format);
  check_skip(opt, format);
  sscanf_length(opt, format);
  return result;
}

void check_skip(options_for_sscanf *opt, char **format) {
  if (**format == '*') {
    opt->skip = 1;
    (*format)++;
  }
}

void sscanf_length(options_for_sscanf *opt, char **format) {
  switch (**format) {
    case 'h':
      opt->type_qualifier = 'h';
      (*format)++;
      break;
    case 'l':
      opt->type_qualifier = 'l';
      (*format)++;
      break;
    case 'L':
      opt->type_qualifier = 'L';
      (*format)++;
      break;
    default:
      break;
  }
}

void sscanf_width(int *width, char **format) {
  *width = 0;
  while (**format >= '0' && **format <= '9') {
    *width = *(width)*10 + **format - '0';
    (*format)++;
  }
}

//парсер буквы спецификатора
int specificator_parser(options_for_sscanf *opt, char **str_pointer,
                        va_list arguments, char **format_pointer,
                        char **str_start) {
  int res = 0;
  if (str_pointer) {
    if (**format_pointer == 'c')
      res = save_char(opt, arguments, str_pointer, format_pointer);
    else if (**format_pointer == 'n')
      res = save_n(opt, arguments, str_pointer, format_pointer, str_start);
    else if (**format_pointer == 'u' || **format_pointer == 'd') {
      *str_pointer = spaces_skip(*str_pointer);
      res = save_u_d(opt, arguments, str_pointer, format_pointer);
    } else if (**format_pointer == 'p') {
      *str_pointer = spaces_skip(*str_pointer);
      res = save_pointer(opt, arguments, str_pointer, format_pointer);
    } else if (**format_pointer == 's') {
      (*str_pointer) = spaces_skip(*str_pointer);
      res = save_string(opt, arguments, str_pointer, format_pointer);
    } else if (**format_pointer == 'x' || **format_pointer == 'X') {
      *str_pointer = spaces_skip(*str_pointer);
      res = save_hex(opt, arguments, str_pointer, format_pointer);
    } else if (**format_pointer == 'o') {
      *str_pointer = spaces_skip(*str_pointer);
      res = save_oct(opt, arguments, str_pointer, format_pointer);
    } else if (**format_pointer == 'i') {
      *str_pointer = spaces_skip(*str_pointer);
      res = save_i(opt, arguments, str_pointer, format_pointer);
    } else if (**format_pointer == 'f' || **format_pointer == 'e' ||
               **format_pointer == 'E' || **format_pointer == 'g' ||
               **format_pointer == 'G') {
      *str_pointer = spaces_skip(*str_pointer);
      res = save_float(opt, arguments, str_pointer, format_pointer);
    }
  }
  return res;
}

int save_char(options_for_sscanf *opt, va_list arguments, char **str_pointer,
              char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    if (opt->skip != 1)
      *(va_arg(arguments, char *)) = **str_pointer;
    else
      (*str_pointer)++;

    (*format_pointer)++;
    if (!opt->width) opt->width = 1;
    for (int i = 0; i < opt->width; i++) (*str_pointer)++;
  } else
    res = -1;
  return res;
}

//ищет первый индекс, который не равен дефайну SPACE (пробел, перенос строки...)
char *spaces_skip(char *str) {
  str += s21_strspn(str, SPACE);
  return str;
}

int save_n(options_for_sscanf *opt, va_list arguments, char **str_pointer,
           char **format_pointer, char **str_start) {
  int res = 0;
  char *adress = s21_NULL;
  if (*str_pointer) {
    if (opt->skip != 1) {
      adress = va_arg(arguments, char *);
      (*(int *)adress) = *str_pointer - *str_start;
    }
    (*format_pointer)++;
  } else
    res = -1;
  return res;
}

int save_string(options_for_sscanf *opt, va_list arguments, char **str_pointer,
                char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    //если ширина не задана, то снимаем ограничение
    if (opt->width == 0) opt->width = INT_MAX;
    if (!opt->skip) {
      char *string = (char *)va_arg(arguments, char *);
      //до тех пор пока позволяет ширина и не пробел перезаписываем посимвольно
      while (opt->width > 0 && s21_strchr(SPACE, **str_pointer) == s21_NULL) {
        *string++ = **str_pointer;
        (*str_pointer)++;
        opt->width--;
      }
      *string = '\0';
    } else {
      //в случае если %*s, то просто посимвольно скипаем
      while (s21_strchr(SPACE, **str_pointer) == s21_NULL && opt->width--)
        (*str_pointer)++;
    }
    (*format_pointer)++;
  } else {
    res = -1;
  }

  return res;
}

int save_pointer(options_for_sscanf *opt, va_list arguments, char **str_pointer,
                 char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    if (opt->skip != 1) {
      if (!opt->width) opt->width = INT_MAX;
      opt->base = 16;
      long decimal = parse_number(opt, str_pointer);
      void **dest = (va_arg(arguments, void **));
      *dest = (void *)(0x0 + decimal);
    } else
      while (s21_strchr(SPACE, **str_pointer) == s21_NULL) (*str_pointer)++;
    (*format_pointer)++;
  } else
    res = -1;
  return res;
}

int save_hex(options_for_sscanf *opt, va_list arguments, char **str_pointer,
             char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    if (opt->skip != 1) {
      if (!opt->width) opt->width = INT_MAX;
      opt->base = 16;
      long decimal = parse_number(opt, str_pointer);
      length_save(arguments, opt, &decimal);
    } else
      while (s21_strchr(SPACE, **str_pointer) == s21_NULL) (*str_pointer)++;
    (*format_pointer)++;
  } else
    res = -1;
  return res;
}

int save_oct(options_for_sscanf *opt, va_list arguments, char **str_pointer,
             char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    if (opt->skip != 1) {
      if (!opt->width) opt->width = INT_MAX;
      opt->base = 8;
      long decimal = parse_number(opt, str_pointer);
      length_save(arguments, opt, &decimal);
    } else
      while (s21_strchr(SPACE, **str_pointer) == s21_NULL) (*str_pointer)++;
    (*format_pointer)++;
  } else
    res = -1;
  return res;
}

int save_u_d(options_for_sscanf *opt, va_list arguments, char **str_pointer,
             char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    if (opt->skip != 1) {
      if (!opt->width) opt->width = INT_MAX;
      long decimal = parse_number(opt, str_pointer);
      length_save(arguments, opt, &decimal);
    } else
      while (s21_strchr(SPACE, **str_pointer) == s21_NULL) (*str_pointer)++;
    (*format_pointer)++;
  } else
    res = -1;
  return res;
}

int save_i(options_for_sscanf *opt, va_list arguments, char **str_pointer,
           char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    if (opt->skip != 1) {
      if (!opt->width) opt->width = INT_MAX;
      int sign = (**str_pointer == '+' || **str_pointer == '-') ? 1 : 0;
      if (*(*str_pointer + sign) == '0') {
        if (*(*str_pointer + 1 + sign) == 'x' ||
            *(*str_pointer + 1 + sign) == 'X')
          opt->base = 16;
        else
          opt->base = 8;
      }
      long decimal = parse_number(opt, str_pointer);
      length_save(arguments, opt, &decimal);
    } else
      while (s21_strchr(SPACE, **str_pointer) == s21_NULL) (*str_pointer)++;
    (*format_pointer)++;
  } else
    res = -1;
  return res;
}

long parse_number(options_for_sscanf *opt, char **str_pointer) {
  int temp = 0;
  long decimal = 0;
  int res = 0;
  int sign = 1;
  //определяем знак
  sign = (**str_pointer == '-') ? -1 : 1;
  opt->width -= (**str_pointer == '-' || **str_pointer == '+') ? 1 : 0;
  (*str_pointer) += (**str_pointer == '-' || **str_pointer == '+') ? 1 : 0;
  //определяем систему счисления
  if (**str_pointer == '0' &&
      ((opt->base == 16 &&
        ((*(*str_pointer + 1) == 'x') || (*(*str_pointer + 1) == 'X'))) ||
       opt->base == 8)) {
    (*str_pointer) += (opt->base == 16) ? 2 : 1;
    (opt->width -= (opt->base == 16) ? 2 : 1);
  }
  //обрабатываем число
  while (str_pointer && s21_strchr(SPACE, **str_pointer) == s21_NULL &&
         opt->width > 0 && !res) {
    if ((**str_pointer >= '0' && **str_pointer <= '7') ||
        (**str_pointer >= '8' && **str_pointer <= '9' && (opt->base >= 10))) {
      temp = **str_pointer - 48;
    } else if (opt->base == 16) {
      if (**str_pointer >= 'a' && **str_pointer <= 'f') {
        temp = **str_pointer - 87;  // декодируем a-f как 10-15
      } else if (**str_pointer >= 'A' && **str_pointer <= 'F') {
        temp = **str_pointer - 55;  // декодируем A-F как 10-15
      } else
        res = -1;
    } else
      res = -1;
    if (res != -1) {
      decimal = decimal * opt->base + temp;
      (*str_pointer)++;
      opt->width--;
    }
  }
  return decimal * sign;
}

/*функция вааржит нам переменные нужного размера и сохраняет туда
 переданный результат*/
void length_save(va_list arguments, options_for_sscanf *opt, long int *result) {
  if (opt->type_qualifier == '\0') {
    int *destination = va_arg(arguments, int *);
    *destination = (int)*result;
  } else if (opt->type_qualifier == 'h') {
    short *destination = va_arg(arguments, short *);
    *destination = (short)*result;
  } else if (opt->type_qualifier == 'l') {
    long *destination = va_arg(arguments, long *);
    *destination = (long)*result;
  }
}

int save_float(options_for_sscanf *opt, va_list arguments, char **str_pointer,
               char **format_pointer) {
  int res = 0;
  if (*str_pointer && **str_pointer != '\0') {
    if (opt->width == 0) opt->width = INT_MAX;
    if (opt->skip != 1) {
      res = process_float(str_pointer, opt, arguments);
    } else {
      //учитываем ширину при скипе
      while (s21_strchr(SPACE, **str_pointer) == s21_NULL && opt->width--)
        (*str_pointer)++;
    }
    (*format_pointer)++;
  } else
    res = -1;
  return res;
}

int process_float(char **str_pointer, options_for_sscanf *opt,
                  va_list arguments) {
  int all_symbols_counter = 0;
  int res = 0;
  int sign = 1;
  sign = (**str_pointer == '-') ? -1 : 1;
  opt->width -= (**str_pointer == '-' || **str_pointer == '+') ? 1 : 0;
  (*str_pointer) += (**str_pointer == '-' || **str_pointer == '+') ? 1 : 0;
  long double result = 0;
  if (is_nan_or_inf(str_pointer, &result, sign)) {  // обработка nan inf
    (*str_pointer) += 3;
  } else {  // обработка обычного числа
    long double left_part =
        scan_float_num(str_pointer, opt, &all_symbols_counter, sign);
    result = left_part;
    if (**str_pointer ==
        '.') {  //если считали . то записываем отдельно то что после неё
      opt->width--;
      opt->dot = 1;
      (*str_pointer)++;
      int right_part_symbols_counter = 0;
      long double right_part =
          scan_float_num(str_pointer, opt, &right_part_symbols_counter, sign);
      all_symbols_counter += right_part_symbols_counter + 1;
      for (int i = right_part_symbols_counter; i > 0; i--)
        right_part /= 10;  //делаем правую часть по настоящему правой
      if (!left_part && !right_part && sign == -1)
        result = -0.0;
      else {
        result += right_part;  //слепливаем 2 части
      }
    }
    if (**str_pointer == 'e' || **str_pointer == 'E') {  //если считали е
      if (opt->width == 1) {
        (*str_pointer)++;
      } else {
        process_e(str_pointer, &result, &all_symbols_counter, opt);
      }
    }
  }
  length_save_float(arguments, opt, &result);
  return res;
}

int is_nan_or_inf(char **str_pointer, long double *result, int sign) {
  int nan_inf = 0;
  if (s21_strncmp(*str_pointer, "inf", 3) == 0 ||
      s21_strncmp(*str_pointer, "INF", 3) == 0) {
    *result = sign * INFINITY;
    nan_inf = 1;
  }
  if (s21_strncmp(*str_pointer, "nan", 3) == 0 ||
      s21_strncmp(*str_pointer, "NAN", 3) == 0) {
    *result = (sign == -1) ? -NAN : NAN;
    nan_inf = 1;
  }
  return nan_inf;
}

/*данная функция парсит число до точки, после точки и цифру после е е+ е-*/
long scan_float_num(char **str_pointer, options_for_sscanf *opt,
                    int *symbols_counter, int sign) {
  long scanned_num = 0;
  if ((**str_pointer >= '0' && **str_pointer <= '9') || opt->dot) {
    while (**str_pointer >= '0' && **str_pointer <= '9' && opt->width-- &&
           s21_strchr(SPACE, **str_pointer) == s21_NULL) {
      scanned_num = scanned_num * 10 + (**str_pointer - '0');
      (*str_pointer)++;
      (*symbols_counter)++;
    }
  } else
    opt->float_fail = 1;
  return scanned_num * sign;
}

/*функция вааржит нам переменные нужного размера и сохраняет туда
 переданный результат*/
void length_save_float(va_list arguments, options_for_sscanf *opt,
                       long double *result) {
  if (opt->type_qualifier == 'l') {
    double *destination = va_arg(arguments, double *);
    *destination = (double)*result;
  } else if (opt->type_qualifier == 'L') {
    long double *destination = va_arg(arguments, long double *);
    *destination = (long double)*result;
  } else {
    float *destination = va_arg(arguments, float *);
    *destination = (float)*result;
  }
}

/*функция применяет е+ е- и e к нашей получившейся цифре в %f*/
int process_e(char **str_pointer, long double *result, int *symbols_counter,
              options_for_sscanf *opt) {
  (*str_pointer)++;  //тут мы на букве е, надо сдвинуться
  int sign = 1;
  //иф элс ниже обрабатывает у нас 2 случая - если есть знак и если нету
  if (**str_pointer == '+' ||
      ((**str_pointer - 1) >= '0' && (**str_pointer - 1) <= '9')) {
    sign = 1;
    if (!((**str_pointer) >= '0' && (**str_pointer) <= '9'))
      (*str_pointer)++;  //двигаем указатель ток если е+
  } else if (**str_pointer == '-') {
    sign = -1;
    (*str_pointer)++;
  }
  opt->width--;
  int e_symbols_counter = 1;
  //парсим степень после е:
  int pow_e = scan_float_num(str_pointer, opt, &e_symbols_counter, 1);
  //допустим степень 5 тогда изменяем переданный результат *10^5:
  if (sign == 1) {
    while (pow_e--) *result *= 10.0;
  } else if (sign == -1) {
    while (pow_e--) *result /= 10.0;
  }
  *symbols_counter += e_symbols_counter;
  return e_symbols_counter;
}
