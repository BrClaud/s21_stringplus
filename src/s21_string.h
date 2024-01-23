#ifndef S21_STRING_H_
#define S21_STRING_H_
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#define s21_NULL ((void *)0)
typedef unsigned long long s21_size_t;
#define SPACE \
  " \n\t\v\f\r"  // \v -- вертикальная табуляция, \f -- перевод страницы, \r --
                 // возврат каретки
#define SPECIFIERS "cdieEfgGosuxXpn"
#define BUFSIZE 8100

typedef struct {
  int plus;             // показывать знак
  int minus;            // выравнивание по левому краю
  int space;            // оставить место под знак
  int notation;         // '#' для 8 и 16-ых чиселок
  int zero;             // флаг 0
  int width;            //ширина форматной строки
  char type_qualifier;  // тип спецификатора переменной
  int prec;             //точность
  int sustem_type;      //система счисления
  int sign;             //+ - или пробел в начале
  int dot;              // есть ли точка
  int g;                // если такой спецификатор есть
  int e;                //для научной записи
  int flag;
  int var_null;       // если переменная ноль
  char specificator;  // спецификатор
  int exponent;  // показатель степени при спецификаторе e после E +1.23E+03
  int is_precision;        // введена ли точность
  int negative_presicion;  // для отрицательной точности
  int negative;            // отрицительное ли число
  int uppercase;           // заглавные буквы
} options;

typedef struct {
  int width;
  char type_qualifier;  // l L h
  int skip;             //для звездочки
  int base;             //система счисления
  int float_fail;
  int dot;
} options_for_sscanf;

/*-------string.h------- */
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *dest, s21_size_t ch, s21_size_t n);
char *s21_strncat(char *dst, const char *src, s21_size_t n);
char *s21_strcat(char *dest,
                 const char *src);  // понадобилась для float sprintf
char *s21_strncpy(char *dst, const char *src, s21_size_t n);
char *s21_strtok(char *s, const char *delim);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strspn(const char *str1,
                      const char *str2);  //понадобилась для sscanf
char *s21_strrchr(const char *str, int c);

s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strerror(int errnum);

/*-------c#_func------- */
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

/*-------sprintf------- */
int s21_sprintf(char *str, const char *format, ...);
char *parser(char *str, char *s_start, const char *format, options *opt,
             va_list *arguments);
const char *set_specs(options *opt, const char *format, va_list *arguments);
const char *get_specs(const char *format, options *opt);
const char *get_width(const char *format, int *width, va_list *arguments);

char *print_decimal(char *str, options *opt, va_list *arguments);
s21_size_t get_size_to_decimal(options *opt, long int *nun);
int decimal_to_string(options *opt, long int *nun, char *str_nun,
                      s21_size_t size_to_decimal);
void flag_0_decimal(options *opt, s21_size_t *size_to_decimal, char *str_nun,
                    int *i, int *flag);
void write_decimal_to_char(options *opt, long int *cp_nun,
                           s21_size_t *size_to_decimal, int *i, char *str_nun,
                           long int *nun);
void flag_space_plus_minus_decimal(options *opt, s21_size_t *size_to_decimal,
                                   char *str_nun, int *i, long int *nun);
void is_freespace(options *opt, char *str_nun, int *i,
                  s21_size_t *size_to_decimal);

char *print_pointer(char *str, options *opt, va_list *arguments);
char *print_unsigned(char *str, options *opt, va_list *arguments,
                     const char *format);
char *int_to_hex(long int buff_num, char *pointer, options *opt);
char *unsignedint_to_char(long int number, char *buff_number, options *opt);
char *int_to_oct(long int number, char *buff_number, options *opt);
void rewrite(int *i, char sum, s21_size_t size_to_decimal, char *str_nun);
char *print_diff_for_char(char *str, options *opt, va_list *arguments);
char *print_diff(char *str, options *opt, int dif);
s21_size_t get_size_u(options *opt, int i);
char *print_diff_for_u(char *str, options *opt, s21_size_t *dif,
                       s21_size_t *siz, s21_size_t *number);

char *print_char(char *str, va_list *arguments);
char *print_string(char *str, options *opt, va_list *arguments);
void process_width_prec_for_string(char **str, options *opt, int *prec_temp,
                                     int *width_temp, int *diff,
                                     int *len_of_string);
void process_n(char *str, va_list *arguments);

void prec_for_g_spec(options *opt, long double *var_double);
s21_size_t string_to_number(const char *start, int number_of_symbols);
char *print_float(char **str, options *opt, va_list *arguments);
void itoa_and_precision_for_f(char *buf, options *opt, long double var_double);
void s21_itoa(char *buf, options *opt, long int var);
void add_width(char *buf, options *opt);
void save_buf_in_str(char **str, char *buf);
char *print_e(char **str, options *opt, va_list *arguments);
void normilize(long double *var_double, options *opt);
void itoa_and_precision_for_e(char *buf, options *opt, long double var_double);
void prec_settings(options *opt, long double *var_double);
char *print_g(char **str, options *opt, va_list *arguments);
void check_gG_precision(options *opt, long double *var_double);

/*------- sscanf------- */
int s21_sscanf(const char *str, const char *format, ...);
int flags_parse(char **format, options_for_sscanf *opt);
void sscanf_length(options_for_sscanf *opt, char **format);
void sscanf_width(int *width, char **format);
int specificator_parser(options_for_sscanf *opt, char **str_pointer,
                        va_list arguments, char **format_pointer,
                        char **str_start);
char *spaces_skip(char *str);
int save_char(options_for_sscanf *opt, va_list arguments, char **str_pointer,
              char **format_pointer);
int save_n(options_for_sscanf *opt, va_list arguments, char **str_pointer,
           char **format_pointer, char **str_start);
int save_pointer(options_for_sscanf *opt, va_list arguments, char **str_pointer,
                 char **format_pointer);
int save_string(options_for_sscanf *opt, va_list arguments, char **str_pointer,
                char **format_pointer);
int save_hex(options_for_sscanf *opt, va_list arguments, char **str_pointer,
             char **format_pointer);
void length_save(va_list arguments, options_for_sscanf *opt, long int *result);
int save_oct(options_for_sscanf *opt, va_list arguments, char **str_pointer,
             char **format_pointer);
int save_u_d(options_for_sscanf *opt, va_list arguments, char **str_pointer,
             char **format_pointer);
long parse_number(options_for_sscanf *opt, char **str_pointer);
int save_i(options_for_sscanf *opt, va_list arguments, char **str_pointer,
           char **format_pointer);
int save_float(options_for_sscanf *opt, va_list arguments, char **str_pointer,
               char **format_pointer);
long scan_float_num(char **str_pointer, options_for_sscanf *opt,
                    int *symbols_counter, int sign);
void length_save_float(va_list arguments, options_for_sscanf *opt,
                       long double *result);
int process_float(char **str_pointer, options_for_sscanf *opt,
                  va_list arguments);
int process_e(char **str_pointer, long double *result, int *symbols_counter,
              options_for_sscanf *opt);
int is_nan_or_inf(char **str_pointer, long double *result, int sign);
void check_skip(options_for_sscanf *opt, char **format);

#endif