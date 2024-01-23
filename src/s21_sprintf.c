#include <stdio.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *s_start = str;
  va_list arguments;
  va_start(arguments, format);
  while (*format) {
    if (*format == '%') {
      format++;
      options opt = {0};
      if (*format == '%') {
        *str = (char)37;
        str++;
      } else {
        opt.sustem_type = 10;  // по умолчанию десятичная система счисления
        format = set_specs(&opt, format, &arguments);
        while (!s21_strchr("cdieEfFgGosuxXpn", *format)) {
          format++;
        }
        str = parser(str, s_start, format, &opt, &arguments);
      }
    } else {
      *str = *format;
      str++;
    }
    format++;
  }
  *str = '\0';
  va_end(arguments);
  return (str - s_start);
}

char *parser(char *str, char *s_start, const char *format, options *opt,
             va_list *arguments) {
  opt->specificator = *format;
  if (*format == 'n') {
    process_n(s_start, arguments);
  } else if (*format == 'd' || *format == 'i') {
    str = print_decimal(str, opt, arguments);
  } else if (*format == 'p') {
    str = print_pointer(str, opt, arguments);
  } else if (*format == 'x' || *format == 'X' || *format == 'u' ||
             *format == 'o') {
    if (*format == 'X') opt->uppercase = 1;
    str = print_unsigned(str, opt, arguments, format);
  } else if (*format == 's') {
    str = print_string(str, opt, arguments);
  } else if (*format == 'c') {
    str = print_diff_for_char(str, opt, arguments);
  } else if (*format == 'f' || *format == 'F') {
    if (*format == 'F') opt->uppercase = 1;
    str = print_float(&str, opt, arguments);
  } else if (*format == 'e' || *format == 'E') {
    if (*format == 'E') opt->uppercase = 1;
    str = print_e(&str, opt, arguments);
  } else if (*format == 'g' || *format == 'G') {
    if (*format == 'G') opt->uppercase = 1;
    str = print_g(&str, opt, arguments);
  }
  return str;
}

const char *set_specs(options *opt, const char *format, va_list *arguments) {
  format = get_specs(format, opt);
  format = get_width(format, &(opt->width), arguments);  // ширина

  // точность
  if (*format == '.') {
    opt->is_precision = 1;
    opt->dot = 1;
    format += 1;
    format = get_width(format, &(opt->prec), arguments);
  }
  if (*format == 'L') {  //понять есть ли расширения лог или шорт
    opt->type_qualifier = 'L';
  } else if (*format == 'l') {
    opt->type_qualifier = 'l';
  } else if (*format == 'h') {
    opt->type_qualifier = 'h';
  }
  if (opt->type_qualifier != 0) {
    format += 1;
  }
  if (opt->width < 0) {
    opt->width = -opt->width;  // этот иф является проверкой на всякий случай
    opt->minus = 1;
  }
  return format;
}

// заносим в структуру информацию о приколах форматной строки
const char *get_specs(const char *format, options *opt) {
  while (format) {
    if (*format == '+')
      opt->plus = 1;
    else if (*format == '-')
      opt->minus = 1;
    else if (*format == '#')
      opt->notation = 1;
    else if (*format == ' ')
      opt->space = 1;
    else if (*format == '0')
      opt->zero = 1;
    else
      break;
    format++;
  }
  if (opt->plus == 1) opt->space = 0;  //взаимоисключения
  if (opt->minus == 1) opt->zero = 0;
  return format;
}

const char *get_width(const char *format, int *width,
                      va_list *arguments) {  //проверяем ширину или наличие *
  *width = 0;
  if (*format == '*') {
    *width = va_arg(*arguments, int);
    format++;
  }
  while (format) {
    if ('0' <= *format && *format <= '9') {
      *width *= 10;
      *width += *format - '0';
    } else {
      break;
    }
    format++;
  }
  return format;
}

// выделение памяти
char *print_decimal(char *str, options *opt, va_list *arguments) {
  long int nun = 0;
  if (opt->type_qualifier == 'l') {
    nun = (long int)va_arg(*arguments, long int);  // смотрим есть ли l h
  } else if (opt->type_qualifier == 'h') {
    nun = (short)va_arg(*arguments, int);
  } else {
    nun = (int)va_arg(*arguments,
                      int);  //обычный аргумент
  }
  s21_size_t size_to_decimal =
      get_size_to_decimal(opt, &nun);  // выясняем размер строки форматной
  char str_nun[BUFSIZE] = {'\0'};
  int p = 0;
  int o = decimal_to_string(opt, &nun, str_nun, size_to_decimal);
  for (int j = o - 1; j >= 0; j--) {
    *str = str_nun[j];
    str++;
  }
  while (p < opt->width - o) {
    *str = ' ';
    str++;
    p++;
  }
  return str;
}

// выясняем размер
s21_size_t get_size_to_decimal(options *opt, long int *nun) {
  s21_size_t res = 0;
  long int cp_nun = *nun;
  if (cp_nun < 0) {
    cp_nun = -cp_nun;  //делаем число положительным
  }
  while (cp_nun > 0) {
    cp_nun = cp_nun / 10;  // вот это для подсчёта длины числа
    res++;
  }
  if ((cp_nun == 0 && res == 0) && (opt->prec || opt->space || opt->width)) {
    res++;  // проверка если nun = 0
  }

  if (res == 0 && cp_nun == 0 && !opt->prec && !opt->width && !opt->space &&
      !opt->dot) {
    res++;  //если ни одно из предыдущих условий не сработало и nun = 0
  }

  if ((s21_size_t)opt->prec > res) {
    res = opt->prec;  // тоже самое действие с точностью
  }
  if (opt->space || opt->plus || *nun < 0) {
    opt->sign = 1;
    res++;  // дополнительное место для + - или ' '
  }
  if ((s21_size_t)opt->width > res) {
    res = opt->width;  // если определённая подсчётом длина меньше, чем данная в
                       // форматной строке перед спецификатором, то присвоить
                       // res длину данную в форм строке
  }

  if (opt->dot == 1 && *nun == 0 && cp_nun == 0 && opt->prec == 0) {
    res = 1;
    opt->flag = 1;
  }

  return res;
}

int decimal_to_string(options *opt, long int *nun, char *str_nun,
                      s21_size_t size_to_decimal) {
  int flag = 0;
  if (*nun < 0) {
    flag = 1;  // запоминаем что число отрицательное
    *nun = -(*nun);  // нам надо взять его модуль
  }
  int i = 0;  //счетчик сколько символов записано

  long int cp_nun = *nun;
  // работаем с копией числа
  write_decimal_to_char(opt, &cp_nun, &size_to_decimal, &i, str_nun, nun);
  //если число != 0
  if (flag == 1) {
    *nun = -(*nun);
  }
  flag = 0;                 // допустим
  if (opt->prec - i > 0) {  // если точность больше ширины числа то поднимаем
                            // флаг 0 чтобы заполнить нулями место
    opt->prec -= i;
    opt->zero = 1;
  } else {
    flag = 1;  // надо думать TODO
  }
  if (size_to_decimal == 1 && opt->zero == 1 &&
      opt->sign == 1) {  // если не хватает места под нули то вырубаем флаг
    opt->zero = 0;
  }
  flag_0_decimal(opt, &size_to_decimal, str_nun, &i, &flag);
  flag_space_plus_minus_decimal(opt, &size_to_decimal, str_nun, &i, nun);
  //если осталось свободное место в строке
  is_freespace(opt, str_nun, &i, &size_to_decimal);

  return i;
}

void flag_0_decimal(options *opt, s21_size_t *size_to_decimal, char *str_nun,
                    int *i, int *flag) {
  while (opt->zero && str_nun && (*size_to_decimal - opt->sign > 0) &&
         (opt->prec > 0 || *flag)) {
    if (*size_to_decimal == 1 && opt->sign == 1) {
      break;
    }
    char sum = '0';
    str_nun[*i] = sum;
    (*i)++;
    (*size_to_decimal)--;
    opt->prec--;
  }
}

void flag_space_plus_minus_decimal(options *opt, s21_size_t *size_to_decimal,
                                   char *str_nun, int *i, long int *nun) {
  if (*nun < 0 && *size_to_decimal) {
    char sum = '-';
    str_nun[*i] = sum;
    (*i)++;
    (*size_to_decimal)--;
  }
  if (*nun >= 0 && opt->plus && *size_to_decimal) {
    char sum = '+';
    str_nun[*i] = sum;
    (*i)++;
    (*size_to_decimal)--;
  } else if (opt->space && *nun >= 0 && *size_to_decimal) {
    char sum = ' ';
    str_nun[*i] = sum;
    (*i)++;
    (*size_to_decimal)--;
  }
  opt->sign = 0;
}

void is_freespace(options *opt, char *str_nun, int *i,
                  s21_size_t *size_to_decimal) {
  if (*size_to_decimal > 0 && opt->minus == 0) {
    while ((*size_to_decimal - opt->sign > 0) && *str_nun != 0) {
      char sum = ' ';
      str_nun[*i] = sum;
      (*i)++;
      (*size_to_decimal)--;
    }
  }
  if (opt->flag == 1) {
    *i = 0;
    if (opt->width == 0 && opt->space) {
      str_nun[*i] = ' ';
      (*i)++;
    }
  }
}

void write_decimal_to_char(options *opt, long int *cp_nun,
                           s21_size_t *size_to_decimal, int *i, char *str_nun,
                           long int *nun) {
  if ((*cp_nun == 0 &&
       (opt->prec || opt->width || opt->space)) ||  //если наше число == 0
      (*cp_nun == 0 && !opt->prec && !opt->space && !opt->dot &&
       !opt->width)) {  // смотрим оба случая(есть точность и нет точности)
    char sum = *cp_nun % opt->sustem_type + '0';  //получаем символ нуля
    str_nun[*i] = sum;  //записываем символ в буферный массив
    (*i)++;                // идём дальше по массиву
    (*size_to_decimal)--;  //уменьшаем размер строки на 1, тк символ записан
    *cp_nun = *cp_nun / 10;
  }

  while (*cp_nun && str_nun && *size_to_decimal) {
    char sum = *cp_nun % opt->sustem_type + '0';
    if (0 <= *nun && *nun <= 9) {
      sum = (char)(*nun + 48);  // 48 == '0'
    }
    str_nun[*i] = sum;
    (*i)++;
    (*size_to_decimal)--;
    *cp_nun = *cp_nun / 10;
  }
}

char *print_pointer(char *str, options *opt, va_list *arguments) {
  char pointer[BUFSIZE] = {'\0'};
  void *p = va_arg(*arguments, void *);
  s21_size_t buff_num = (s21_size_t)p;
  int_to_hex(buff_num, pointer, opt);
  int siz = s21_strlen(pointer);
  if ((opt->dot == 1 || opt->width - siz > 0) && opt->minus == 0) {
    str = print_diff(str, opt, siz);
  }
  *(str++) = '0';
  *(str++) = 'x';
  for (int j = (int)s21_strlen(pointer) - 1; j >= 0; j--) {
    *str = pointer[j];
    str++;
  }
  if (opt->width - siz > 0 && opt->minus == 1) {
    str = print_diff(str, opt, siz);
  }
  return str;
}

char *print_diff(char *str, options *opt, int dif) {
  while (opt->width - dif - 2 > 0) {
    *str = ' ';
    str++;
    opt->width--;
  }
  return str;
}

char *print_char(char *str, va_list *arguments) {
  int symbol = (int)va_arg(*arguments, int);
  *str = (char)symbol;
  str++;
  *str = '\0';
  return str;
}

char *print_diff_for_char(char *str, options *opt, va_list *arguments) {
  if (!opt->minus) {
    while (opt->width > 1) {
      *str = ' ';
      str++;
      opt->width--;
    }
    str = print_char(str, arguments);
  } else {
    str = print_char(str, arguments);
    while (opt->width > 1) {
      *str = ' ';
      str++;
      opt->width--;
    }
  }
  return str;
}

char *print_string(char *str, options *opt, va_list *arguments) {
  char *string = (char *)va_arg(*arguments, char *);
  int len_of_string = (int)s21_strlen(string);
  int i = 0, diff = 0;
  int width_temp = opt->width, prec_temp = opt->prec;
  if (opt->dot || opt->prec || opt->width) {
    process_width_prec_for_string(&str, opt, &prec_temp, &width_temp, &diff,
                                  &len_of_string);
  }

  while (i < len_of_string && (!opt->dot || (prec_temp && opt->dot))) {
    *str = string[i];  //посимвольно копируем
    str++;
    i++;
  }

  while (diff > 0 && opt->minus == 1 &&
         (!opt->dot || (prec_temp && opt->dot))) {
    *str = ' ';  // дописываем пробелы
    str++;
    diff--;
  }
  return str;
}

void process_width_prec_for_string(char **str, options *opt, int *prec_temp,
                                   int *width_temp, int *diff,
                                   int *len_of_string) {
  // если ширина меньше длины строки, то ширина становится длиной строки и не
  // 15% (не только ширина)
  if (opt->width < *len_of_string && opt->dot) {
    if (!(opt->prec > 0 && opt->width == 0)) {
      *len_of_string = opt->width;
    }
  }
  // если не 15% (не только ширина)
  if (!(opt->width && !opt->dot && !opt->prec)) {
    if (opt->prec <= *len_of_string) {
      *len_of_string = opt->prec;
    }
  }
  // чтобы знать скок пробелов печатать
  *diff = opt->width - *len_of_string;
  if (opt->prec == 0) {
    opt->prec = opt->width;
  } else {
    if (opt->prec < *width_temp) {
      *diff = *width_temp - opt->prec;
      // если точность меньше ширины, то кол-во пробелов равно их разнице
    }
  }
  // если есть точка, ширина и нет точности (то есть 4.)
  while (opt->dot && *width_temp && !*prec_temp) {
    **str = ' ';
    (*str)++;
    (*width_temp)--;
  }
  // если есть разница и НЕТ выравнивания по левому краю
  while (*diff > 0 && opt->minus == 0 &&
         (!opt->dot || (*prec_temp && opt->dot))) {
    **str = ' ';
    (*str)++;
    (*diff)--;
  }
  // если нет ширины но есть точность (.5)
  if (*prec_temp > 0 && *width_temp == 0) {
    // если длина строки больше точности то печатаем по точности, а если
    // меньше, то печатаем сколько есть символов (проблеами не дополняем)
    if (*prec_temp <= *len_of_string) *len_of_string = *prec_temp;
  }
}

void process_n(char *str, va_list *arguments) {
  int *pointer_int = va_arg(*arguments, int *);
  *pointer_int = s21_strlen(str);
}

char *print_unsigned(char *str, options *opt, va_list *arguments,
                     const char *format) {
  s21_size_t number = va_arg(*arguments, s21_size_t);
  if (opt->type_qualifier == 'h') {
    number = (unsigned short int)number;
  } else if (opt->type_qualifier == 'l' || *format == 'o')
    number = (unsigned long int)number;
  else
    number = (unsigned int)number;

  char buff_number[BUFSIZE] = {'\0'};
  if (!number) opt->var_null = 1;  // для нуля
  s21_size_t z = 0;
  if (*format == 'x' || *format == 'X')
    int_to_hex(number, buff_number, opt);
  else if (*format == 'u')
    unsignedint_to_char(number, buff_number, opt);
  else if (*format == 'o')
    int_to_oct(number, buff_number, opt);
  if (opt->notation && opt->specificator != 'u' && number != 0 &&
      opt->minus ==
          1) {  //добавила тут условие с opt->minus для того, чтобы когда у нас
                //нет данного условия НЕ печатало так: 0x    234
    *(str++) = '0';
    if (opt->specificator == 'o') z++;  //для теста 50 и 51
    if (*format == 'x' || *format == 'X') {
      *(str++) = opt->uppercase ? 'X' : 'x';
    }
  }
  // размер строки изначальный "123" == 3
  z += (s21_size_t)s21_strlen(buff_number);
  // размер строки учитывая точность ширину и прочее
  s21_size_t siz = get_size_u(opt, z);
  if (opt->minus == 0 ||
      (((int)opt->prec - (int)s21_strlen(buff_number) > 0 || opt->zero) &&
       opt->minus))
    str = print_diff_for_u(
        str, opt, &z, &siz,
        &number);  //в гс объясняла, добавила еще number, чтобы проверить для 0x
  // в цикле записывается наше число
  if (!(opt->is_precision && opt->prec == 0 && opt->width == 0) ||
      !opt->var_null) {
    for (int i = (int)s21_strlen(buff_number) - 1; i >= 0; i--) {
      *str = buff_number[i];
      str++;
    }
  }
  if (opt->minus == 1) {
    if (opt->specificator == 'o' &&
        (opt->notation && opt->specificator != 'u' && number != 0 &&
         opt->minus == 1)) {
      z--;  // для теста 50 и 51
    }
    str = print_diff_for_u(str, opt, &z, &siz, &number);
  }
  return str;
}

/*Вывод разницы для однознакогового числа, dif - длина числа, siz - общаяя длина
 * буфера*/
char *print_diff_for_u(char *str, options *opt, s21_size_t *dif,
                       s21_size_t *siz, s21_size_t *number) {
  int d = (*siz) -
          *dif;  // разница между полным и тем что мы имеем "000123" например
  if (d < 0) {
    d = 0;
  }

  if (*siz == 1 && opt->zero == 1 && opt->sign == 1)
    opt->zero = 0;  // для флага ноль - страховка

  int dif_width_prec = opt->width - opt->prec;
  if (opt->notation && opt->specificator != 'u' && *number != 0) {
    if (dif_width_prec > 0) {
      d -= 1;
      *siz -= 1;
      if (opt->specificator == 'X' || opt->specificator == 'x') {
        d -= 1;
        *siz -= 1;
        dif_width_prec -= 2;
      }
    }
  }  //для 0x, чтобы лишние пробелы не записывал
  while (dif_width_prec > 0 && d > 0) {  // сделала d>0, было просто : d, из-за
                                         // этого при d<0 заходило в цикл
    *str = ' ';
    str++;
    d--;
    (*siz)--;
    dif_width_prec--;
  }

  if (opt->notation && opt->specificator != 'u' && *number != 0 &&
      opt->minus == 0) {
    // можно вынести в функцию мб, добавила чтобы сначала пробелы печатались, а
    // потом 0x
    *(str++) = '0';
    if (opt->specificator == 'x' || opt->specificator == 'X') {
      *(str++) = opt->uppercase ? 'X' : 'x';
    }
  }

  while ((opt->zero && d > 0) ||
         (opt->prec - *dif > 0 && d > 0)) {  // сделала d>0
    if (*siz == 1 && opt->sign == 1) {
      break;
    }
    char sum = '0';
    *str = sum;
    str++;
    d--;
    (*dif)++;  // так как сколько напечатает символов 0 связано с этой
               // переменной
    (*siz)--;
  }

  if (opt->zero == 0) {
    while (d > 0) {
      *str = ' ';
      str++;
      d--;
      (*siz)--;
    }
  }
  return str;
}

char *int_to_hex(long int number, char *buff_number, options *opt) {
  int i = 0;
  if (number == 0) {
    if (opt->is_precision && opt->prec == 0)
      buff_number[i] = ' ';
    else
      buff_number[i] = '0';
  }
  while (number > 0) {
    int remainder = number % 16;  //остаток от деления
    buff_number[i++] =
        (remainder < 10)
            ? remainder + '0'
            : (!opt->uppercase ? remainder + 'a' - 10 : remainder + 'A' - 10);
    number /= 16;
  }
  return buff_number;
}

s21_size_t get_size_u(options *opt, int i) {
  s21_size_t res = i;  // ответ сколько чисел в итоге
  if (opt->width == 0 && opt->prec == 0 && opt->is_precision) {
    if (opt->var_null) res = 0;
  } else {
    if (opt->is_precision) {
      if (opt->prec == 0) {
        res = ((s21_size_t)opt->width > res) ? (s21_size_t)opt->width : res;
      } else {
        res = ((s21_size_t)opt->width > res) ? (s21_size_t)opt->width : res;
        res = ((s21_size_t)opt->prec > res) ? (s21_size_t)opt->prec : res;
      }
    } else {
      res = ((s21_size_t)opt->width > res) ? (s21_size_t)opt->width : res;
    }
  }
  return res;
}

char *unsignedint_to_char(long int number, char *buff_number, options *opt) {
  int i = 0;

  if (number == 0) {
    if (opt->is_precision && opt->prec == 0)
      buff_number[i] = ' ';
    else
      buff_number[i] = '0';
  }
  while (number > 0) {
    int remainder = number % 10;
    buff_number[i++] = remainder + '0';
    number /= 10;
  }
  return buff_number;
}

char *int_to_oct(long int number, char *buff_number, options *opt) {
  int i = 0;
  if (number == 0) {
    if (opt->is_precision && opt->prec == 0)
      buff_number[i] = ' ';
    else
      buff_number[i] = '0';
  }
  while (number > 0) {
    int remainder = number % 8;
    buff_number[i++] = remainder + '0';
    number /= 8;
  }
  return buff_number;
}

char *print_float(char **str, options *opt, va_list *arguments) {
  long double num = 0;
  // определяем размерность
  if (opt->type_qualifier == 'L') {
    num = (long double)va_arg(*arguments, long double);
  } else {
    num = (double)va_arg(*arguments, double);
    // num = (float)num;
  }
  // если переменная ноль
  if (!num) opt->var_null = 1;

  char buf[BUFSIZE] = {0};
  if (!isnan(num) && !isinf(num)) {
    itoa_and_precision_for_f(buf, opt, num);
    add_width(buf, opt);        // устаналвиаем ширину
    save_buf_in_str(str, buf);  // сохраняем буфер в строку
  } else if (isnan(num)) {
    s21_strcat(buf, opt->specificator == 'F' ? "NAN" : "nan");
    save_buf_in_str(str, buf);
  } else if (isinf(num)) {
    s21_strcat(buf, opt->specificator == 'F' ? "FNI" : "fni");
    s21_strcat(buf, num > 0 ? "" : "-");
    save_buf_in_str(str, buf);
  }
  return *str;
}

char *print_e(char **str, options *opt, va_list *arguments) {
  long double var_double = 0;
  if (opt->type_qualifier == 'L') {
    var_double = (long double)va_arg(*arguments, long double);
  } else {
    var_double = (double)va_arg(*arguments, double);
  }
  char buf[BUFSIZE] = {0};
  if (!isnan(var_double) && !isinf(var_double)) {
    itoa_and_precision_for_e(buf, opt, var_double);
    add_width(buf, opt);
    save_buf_in_str(str, buf);

  } else if (isnan(var_double)) {
    s21_strcat(buf, opt->specificator == 'E' ? "NAN" : "nan");
    save_buf_in_str(str, buf);
  } else if (isinf(var_double)) {
    s21_strcat(buf, opt->specificator == 'E' ? "FNI" : "fni");
    s21_strcat(buf, var_double > 0 ? "" : "-");
    save_buf_in_str(str, buf);
  }
  return *str;
}

char *print_g(char **str, options *opt, va_list *arguments) {
  long double var_double = 0;
  if (opt->type_qualifier == 'L') {
    var_double = (long double)va_arg(*arguments, long double);
  } else {
    var_double = (double)va_arg(*arguments, double);
  }
  char buf[BUFSIZE] = {0};
  // проверка на недопустимое значение NAN INFINITY
  if (!isnan(var_double) && !isinf(var_double)) {
    // проверяет отрицательное ли число, и переводит в положительное
    opt->negative = var_double < 0 ? 1 : 0;
    var_double = var_double < 0 ? -var_double : var_double;

    // приводит число с плав. точкой к виду 1<=f<10 и записывает степень в
    // opt->exponent
    long double var_double_2 = var_double;
    normilize(&var_double_2, opt);

    // в зависимости от степени, определяем в каком виде обрабатывать e или f
    // где e - научная нотация (степень < -4 или >5), f - число с плавающей
    // точкой (-4<=f<=5)
    if (opt->exponent < -4 || opt->exponent > 5) {
      opt->exponent = 0;
      itoa_and_precision_for_e(buf, opt, var_double);
    } else {
      // opt->exponent = 0;
      itoa_and_precision_for_f(buf, opt, var_double);
    }
    add_width(buf, opt);        // устанавливаем ширину
    save_buf_in_str(str, buf);  // сохраняем буфер в строку

    // если считываемое число не определено или
  } else if (isnan(var_double)) {
    s21_strcat(buf, opt->specificator == 'G' ? "NAN" : "nan");
    save_buf_in_str(str, buf);
  } else if (isinf(var_double)) {
    s21_strcat(buf, opt->specificator == 'G' ? "FNI" : "fni");
    s21_strcat(buf, var_double > 0 ? "" : "-");
    save_buf_in_str(str, buf);
  }
  return *str;
}

/*Приводит число с точкой к виду 1<=f<10, записывает степень в opt->exponent*/
void normilize(long double *var_double, options *opt) {
  if (*var_double >= 10.0) {
    while (*var_double > 10.0) {
      *var_double /= 10.0;
      opt->exponent++;
    }
  } else if (*var_double < 1.0 && *var_double) {
    while (*var_double < 1.0) {
      *var_double *= 10.0;
      opt->exponent--;
    }
  }
}

void itoa_and_precision_for_e(char *buf, options *opt, long double var_double) {
  // отрицательное ли число, для спецификаторов gG у нас проверяется отдельно
  if (!s21_strchr("gG", opt->specificator))
    opt->negative = var_double < 0 ? 1 : 0;
  var_double = var_double < 0 ? -var_double : var_double;

  normilize(&var_double, opt);
  prec_settings(opt, &var_double);

  // разделяем число на целую и дробную часть, left - целая, right - дробная
  long double left = 0;
  long double right = modfl(var_double, &left);
  long long lleft = left;
  char left_str[BUFSIZE] = {'\0'}, right_str[BUFSIZE] = {'\0'};

  // для установления точности числа, вначале переводим его в целую часть, до
  // указанной точности
  for (int i = 0; i < opt->prec; i++) right *= 10;

  long long rright =
      roundl(right);  // roundl - округление до ближайшего целого, чтобы
  if (rright)
    s21_itoa(right_str, opt, rright);  // записывает правую часть в строку

  // дописываем нули при точности большей чем длина после точки
  while (opt->prec != -1 && (int)s21_strlen(right_str) < opt->prec) {
    right_str[s21_strlen(right_str)] = '0';
  }

  // переводим левую часть в строку
  s21_itoa(left_str, opt, lleft);

  // переводим opt->exponent в буфер
  s21_itoa(buf, opt, opt->exponent);
  // дописываем ноль, если e от 0 до 9, потому что вид 1e+03 c двумя нулями
  if (s21_strlen(buf) == 1) {
    buf[1] = '0';
  }
  // дописываем знак +- и Е
  s21_strcat(buf, opt->exponent >= 0 ? "+" : "-");
  s21_strcat(buf, opt->uppercase ? "E" : "e");

  // переводим все в буфер, склеиваем строку
  if (s21_strlen(right_str)) {
    s21_strcat(buf, right_str);
    s21_strcat(buf, ".");
  }
  if (!s21_strlen(right_str) && opt->notation) {
    s21_strcat(buf, ".");
  }
  s21_strcat(buf, left_str);
}

void prec_settings(options *opt, long double *var_double) {
  // для точности -1, остается только целая часть
  if ((opt->prec <= 0 && opt->is_precision) ||
      (opt->prec <= 1 && s21_strchr("gG", opt->specificator) &&
       opt->is_precision))
    *var_double = roundl(*var_double);

  // если не введена точность, то по умолчанию 6
  if (!opt->is_precision) opt->prec = 6;

  // для специфиатора gG точность на один меньше
  if (opt->specificator == 'g' || opt->specificator == 'G') {
    opt->prec--;
  }
}

void save_buf_in_str(char **str, char *buf) {
  long long int len = s21_strlen(buf);
  // переворачиваем buf и записываем в str
  while (len-- > 0) {
    *((*str)++) = (char)buf[len];
  }
  // дописываем конец строки в str
  **str = 0;
}

/*Вставляем пробелы если отсуствует в конце buf    '-' - minis*/
void work_minus(options *opt, char *buf, long int *len) {
  if (!opt->minus) {
    (*len) = s21_strlen(buf);
    long int deff = opt->width - (*len);
    while (deff-- > 0) {
      buf[(*len)++] = ' ';
    }
  }

  // вставляем пробелы и сдвигаем текст при выравнивании слева minus
  if (opt->minus && opt->width > (*len)) {
    (*len) = s21_strlen(buf);

    long int len_cop = (*len);
    int width_cop = opt->width;

    long int deff_la = opt->width - (*len);

    while (len_cop > 0) {
      buf[--width_cop] = buf[--len_cop];
    }
    (*len) = 0;
    while ((*len) < deff_la) {
      buf[(*len)] = ' ';
      (*len)++;
    }
  }
}

/*Устанавливаем ширину*/
void add_width(char *buf, options *opt) {
  long int len = s21_strlen(buf);
  // если у нас стоит флаг '0' - zero, то мы дополняем ширину 0
  if ((opt->zero && !opt->prec) ||
      (opt->zero && s21_strchr("sfFgGeE", opt->specificator))) {
    long int def = opt->width - len;
    while (def-- > 0) {
      if ((def == 0 && ((opt->plus || opt->negative || opt->space) ||
                        (opt->notation && opt->sustem_type == 16))) ||
          (def == 1 && (opt->notation && opt->sustem_type == 16)))
        continue;
      buf[len] = '0';
      len++;
    }
  }

  len = s21_strlen(buf);

  // вставляем знак
  if (opt->negative) {
    buf[len] = '-';
  } else if (opt->plus) {
    buf[len] = opt->negative ? '-' : '+';
  } else if (opt->space) {
    buf[len] = ' ';
  }

  // вставляем 0x для спецификаторов xX
  if (opt->notation && opt->sustem_type == 16 && !opt->var_null) {
    len = s21_strlen(buf);
    s21_strcat(buf, opt->specificator == 'x' ? "x0" : "X0");
  }
  // вставляем пробелы если отсуствует в конце buf    '-' - minis
  work_minus(opt, buf, &len);
}

/*Уточнение для спецификатора Gg*/
void check_gG_precision(options *opt, long double *var_double) {
  // отрицательное ли число, для спецификаторов gG у нас проверяется отдельно
  if (!s21_strchr("gG", opt->specificator))
    opt->negative = *var_double < 0 ? 1 : 0;
  *var_double = *var_double < 0 ? -(*var_double) : *var_double;

  // для спецификаторов g у нас выводится 6 цифр вместе с точкой или столько
  // цифр сколько указано в точности пример: %g 123.45678 выведется 123.456
  // или %g 123457.5678 вывод 123458 то есть без 0
  if (s21_strchr("gG", opt->specificator)) {
    int precis_g = 5;
    if (opt->is_precision) precis_g = opt->prec - 1;
    if (opt->exponent >= 0) {
      opt->is_precision = 1;
      opt->prec = precis_g - opt->exponent;
    } else {
      opt->is_precision = 1;
      opt->prec = -(-precis_g + opt->exponent);
    }
  }
}

/*Для спецификатора gG убираем лишние нули после запятой, то есть выводим
 * кратчайшую запись*/
void clear_G_zero(options *opt, long double *rrright, long double *lllleft) {
  if (s21_strchr("gG", opt->specificator)) {
    int count = 0;
    // для этого раздеяем на дробную и целую часть и смотрим не равна ли у нас
    // дробная часть 0, 1e-6 - используется потому что машинный ноль
    // воспринимается не точно, а с границами относительной погрешности
    while (modfl((*rrright), lllleft) >= 1e-6) {
      (*rrright) *= 10;
      count++;
    }

    if (opt->prec > count) opt->prec = count;
  }
}

void itoa_and_precision_for_f(char *buf, options *opt, long double var_double) {
  check_gG_precision(opt, &var_double);

  // для точности -1, округляем все число до целой части
  if ((opt->prec <= 0 && opt->is_precision)) var_double = roundl(var_double);

  // если не введена точность, то по умолчанию 6
  if (!opt->is_precision) opt->prec = 6;

  // разделяем число на целую и дробную часть, left - целая, right - дробная
  long double left = 0;
  long double right = modfl(var_double, &left);
  long long lleft = left;
  char left_str[BUFSIZE] = {'\0'};
  char right_str[BUFSIZE] = {'\0'};
  long double rrright = right;
  long double lllleft;
  clear_G_zero(opt, &rrright, &lllleft);
  // для установления точности числа, вначале переводим его в целую часть, до
  // указанной точности
  for (int i = 0; i < opt->prec; i++) {
    right *= 10;
  }
  // округляем правую часть под указанную точность
  long long rright =
      roundl(right);  // roundl - округление до ближайшего целого, чтобы
  if (rright) {
    // записывает в буфер правую часть
    s21_itoa(right_str, opt, rright);
  }
  // дописываем нули при точности большей чем длина после точки
  while (opt->prec != -1 && (int)s21_strlen(right_str) < opt->prec) {
    right_str[s21_strlen(right_str)] = '0';
  }
  // если точность равна нулю но есть #
  if (!s21_strlen(right_str) && opt->notation) {
    s21_strcat(buf, ".");
  }
  // переводим левую часть в строку
  s21_itoa(left_str, opt, lleft);
  // переводим все в буфер, склеиваем строку
  if (s21_strlen(right_str)) {
    s21_strcat(buf, right_str);
    s21_strcat(buf, ".");
  }
  s21_strcat(buf, left_str);
}

void s21_itoa(char *buf, options *opt, long int var) {
  // определяем отрицательное число, не нужно для флагов с плавающей точкой,
  // там по другому!
  if (!s21_strchr("fFgGeE", opt->specificator)) opt->negative = var < 0 ? 1 : 0;
  // это нужно для unsigned
  if (s21_strchr("oxXu", opt->specificator)) {
    opt->negative = 0;
  }

  int i = 0;
  var = var < 0 ? -var : var;
  if (var == 0) {
    // для 0 подаваемую через спецификатор d c тончостью 0
    if (!(!opt->prec && s21_strchr("diuxXo", opt->specificator) &&
          opt->is_precision))
      // если передаваемая переменная 0
      buf[i++] = '0';
  } else {
    while (var > 0) {
      buf[i] = "0123456789abcdef"[var % opt->sustem_type];
      // если X большое, то и буквы в 16ти ричной системе большие
      if (opt->specificator == 'X' && ((var % opt->sustem_type) >= 10) &&
          ((var % opt->sustem_type) <= 15)) {
        buf[i] -= 32;
      }
      var /= opt->sustem_type;
      i++;
    }
  }
  buf[i] = 0;
}
