#include <check.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#define BUFF_SIZE 512

//  s21_memcpy

START_TEST(s21_memcpy_normal) {
  char test_dest[100] = "hello world again!";
  char test_dest2[100] = "hello world again!";
  const char *test_src = "tak";
  s21_size_t test_count = 3;
  char *s21_res = s21_memcpy(test_dest, test_src, test_count);
  ck_assert_str_eq(s21_res, memcpy(test_dest2, test_src, test_count));
}
END_TEST

START_TEST(s21_memcpy_out) {
  char test_dest[100] = "hello world again!";
  char test_dest2[100] = "hello world again!";
  const char *test_src = "tak";
  s21_size_t test_count = 2;
  char *s21_res = s21_memcpy(test_dest, test_src, test_count);
  ck_assert_str_eq(s21_res, memcpy(test_dest2, test_src, test_count));
}
END_TEST

START_TEST(s21_memcpy_empty_dest) {
  char test_dest[100] = "";
  char test_dest2[100] = "";
  const char *test_src = "tak";
  s21_size_t test_count = 3;
  char *s21_res = s21_memcpy(test_dest, test_src, test_count);
  ck_assert_str_eq(s21_res, memcpy(test_dest2, test_src, test_count));
}
END_TEST

START_TEST(s21_memcpy_empty_src) {
  char test_dest[100] = "hello world";
  char test_dest2[100] = "hello world";
  const char *test_src = "";
  s21_size_t test_count = 0;
  char *s21_res = s21_memcpy(test_dest, test_src, test_count);
  ck_assert_str_eq(s21_res, memcpy(test_dest2, test_src, test_count));
}
END_TEST

//  s21_strncpy

START_TEST(s21_strncpy_normal) {
  char test_dest[100] = "Hello world gello world gellortwls";
  char test_dest2[100] = "Hello world gello world gellortwls";
  const char test_src[100] = "taktaktak";
  s21_size_t n = 5;
  char *s21_res = s21_strncpy(test_dest, test_src, n);
  ck_assert_str_eq(s21_res, strncpy(test_dest2, test_src, n));
}
END_TEST

START_TEST(s21_strncpy_out) {
  char test_dest[50] = "hello world again! and again";
  char test_dest2[50] = "hello world again! and again";
  const char test_src[100] = "taktaktak";
  s21_size_t n = 10;
  char *s21_res = s21_strncpy(test_dest, test_src, n);
  ck_assert_str_eq(s21_res, strncpy(test_dest2, test_src, n));
}
END_TEST

//  s21_insert

START_TEST(s21_insert_normal) {
  char *src = "lol cho";
  char *str = "nie rozumiem ";
  s21_size_t start_index = 4;

  char *func_result0 = s21_insert(src, str, start_index);
  ck_assert_str_eq(func_result0, "lol nie rozumiem cho");
  free(func_result0);
}
END_TEST

START_TEST(s21_insert_invalid_index) {
  char *src = "lol cho";
  char *str = "nie rozumiem";
  s21_size_t start_index1 = 1000;
  s21_size_t start_index2 = -2;

  char *func_result1 = s21_insert(src, str, start_index1);
  char *func_result2 = s21_insert(src, str, start_index2);

  ck_assert_ptr_eq(func_result1, s21_NULL);
  ck_assert_ptr_eq(func_result2, s21_NULL);
  free(func_result1);
  free(func_result2);
}
END_TEST

//  HARMONIC ****************************************

START_TEST(s21_to_upper_normal) {
  char *test_str0 = "hello world";
  char *test_str1 = "h1e2l3l4o5";

  char *func_result0 = s21_to_upper(test_str0);
  char *func_result1 = s21_to_upper(test_str1);

  ck_assert_str_eq(func_result0, "HELLO WORLD");
  ck_assert_str_eq(func_result1, "H1E2L3L4O5");
  free(func_result0);
  free(func_result1);
}
END_TEST

//  s21_to_upper
START_TEST(s21_to_upper_whith_sign) {
  char *test_str = "h!e1l/l&o.";

  char *func_result = s21_to_upper(test_str);
  ck_assert_str_eq(func_result, "H!E1L/L&O.");
  free(func_result);
}
END_TEST

START_TEST(s21_to_upper_whith_upper) {
  char *test_str = "HELLO";

  char *func_result = s21_to_upper(test_str);
  ck_assert_str_eq(func_result, test_str);
  free(func_result);
}
END_TEST

// s21_to_lower
START_TEST(s21_to_lower_normal) {
  char *test_str = "My Name Is";

  char *func_res = s21_to_lower(test_str);
  ck_assert_str_eq(func_res, "my name is");
  free(func_res);
}
END_TEST

START_TEST(s21_to_lower_sign) {
  char *test_str = "My Name 1s";

  char *func_res = s21_to_lower(test_str);
  ck_assert_str_eq(func_res, "my name 1s");
  free(func_res);
}
END_TEST

START_TEST(s21_to_lower_with_lower) {
  char *test_str = "my name is";

  char *func_res = s21_to_lower(test_str);
  ck_assert_str_eq(func_res, "my name is");
  free(func_res);
}
END_TEST

//  s21_trim
START_TEST(s21_trim_normal) {
  char *test_str = "my name is";
  char *trim_chars = "my";

  char *func_res = s21_trim(test_str, trim_chars);
  ck_assert_str_eq(func_res, " name is");
  free(func_res);
}
END_TEST

START_TEST(s21_trim_sides) {
  char *test_str = "my name is rey";
  char *trim_chars = "my";

  char *func_res = s21_trim(test_str, trim_chars);
  ck_assert_str_eq(func_res, " name is re");
  free(func_res);
}
END_TEST

START_TEST(s21_trim_empty) {
  char *test_str = " my name is rey ";
  char *trim_chars = " ";

  char *func_res = s21_trim(test_str, trim_chars);
  ck_assert_str_eq(func_res, "my name is rey");
  free(func_res);
}
END_TEST

//  s21_strtok
START_TEST(s21_strtok_normal) {
  char s21_test_str[30] = "one/two.three?four";
  char lib_test_str[30] = "one/two.three?four";
  char *step = "./?";
  char *s21_result = s21_strtok(s21_test_str, step);
  char *lib_result = strtok(lib_test_str, step);

  while (s21_result != s21_NULL && lib_result != s21_NULL) {
    ck_assert_str_eq(s21_result, lib_result);
    s21_result = s21_strtok(s21_NULL, step);
    lib_result = strtok(s21_NULL, step);
  }
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strtok_no_delimetr) {
  char s21_test_str[30] = "one/two.three?four";
  char lib_test_str[30] = "one/two.three?four";
  char *step = "$()-";
  char *s21_result = s21_strtok(s21_test_str, step);
  char *lib_result = strtok(lib_test_str, step);

  while (s21_result != s21_NULL && lib_result != s21_NULL) {
    ck_assert_str_eq(s21_result, lib_result);
    s21_result = s21_strtok(s21_NULL, step);
    lib_result = strtok(s21_NULL, step);
  }
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strtok_empty) {
  char s21_test_str[30] = "";
  char lib_test_str[30] = "";
  char *step = "$()-";
  char *s21_result = s21_strtok(s21_test_str, step);
  char *lib_result = strtok(lib_test_str, step);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

//  s21_strpbrk
START_TEST(s21_strpbrk_normal) {
  char test_str[11] = "0123456789";
  char symb[4] = "345";

  char *s21_result = s21_strpbrk(test_str, symb);
  char *lib_result = strpbrk(test_str, symb);

  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strpbrk_no_symb) {
  char test_str[11] = "0123456789";
  char symb[2] = "a";

  char *s21_result = s21_strpbrk(test_str, symb);
  char *lib_result = strpbrk(test_str, symb);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strpbrk_empty_symb) {
  char test_str[11] = "0123456789";
  char *symb = "";

  char *s21_result = s21_strpbrk(test_str, symb);
  char *lib_result = strpbrk(test_str, symb);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strpbrk_empty_str) {
  char *test_str = "";
  char symb[4] = "123";

  char *s21_result = s21_strpbrk(test_str, symb);
  char *lib_result = strpbrk(test_str, symb);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

//  memset
START_TEST(s21_memset_normal) {
  char s21_test_str[10] = "Hello";
  s21_memset(s21_test_str, 'c', 3);
  char lib_test_str[10] = "Hello";
  memset(lib_test_str, 'c', 3);

  ck_assert_str_eq(s21_test_str, lib_test_str);
}
END_TEST

START_TEST(s21_memset_null) {
  char *s21_test_str = (char *)calloc(12, sizeof(char));
  char *lib_test_str = (char *)calloc(12, sizeof(char));

  s21_memset(s21_test_str, '\0', 11);
  memset(lib_test_str, '\0', 11);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_memset_sign) {
  char s21_test_str[10] = "Hello";
  char lib_test_str[10] = "Hello";
  s21_memset(s21_test_str, 0, 5);
  memset(lib_test_str, 0, 5);
  ck_assert_str_eq(s21_test_str, lib_test_str);
}
END_TEST

//  strerror
START_TEST(s21_strerror_normal) {
  char *s21_test_str = s21_strerror(1);
  char *lib_test_str = strerror(1);

  ck_assert_str_eq(s21_test_str, lib_test_str);
}
END_TEST

START_TEST(s21_strerror_unknown) {
  char *s21_test_str = s21_strerror(109);
  char *lib_test_str = strerror(109);

  ck_assert_str_eq(s21_test_str, lib_test_str);
}
END_TEST

START_TEST(s21_strerror_unknown_2) {
  char *s21_test_str = s21_strerror(-114);
  char *lib_test_str = strerror(-114);

  ck_assert_str_eq(s21_test_str, lib_test_str);
}
END_TEST

START_TEST(s21_strerror_0) {
  char *s21_test_str = s21_strerror(0);
  char *lib_test_str = strerror(0);

  ck_assert_str_eq(s21_test_str, lib_test_str);
}
END_TEST

//  sprintf
START_TEST(s21_sprintf_d) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%d>|<%-3.d>|<%5.7d>|<%10d>|<%#d>|<%-d>|<%+d>|<%ld>|<% .d>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_nan_inf) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "%f %f %F %F %g %g %G %G %e %e %E %E";
  float f1 = INFINITY;
  float f2 = NAN;
  int res1 =
      sprintf(str1, str3, f1, f2, f1, f2, f1, f2, f1, f2, f1, f2, f1, f2);
  int res2 =
      s21_sprintf(str2, str3, f1, f2, f1, f2, f1, f2, f1, f2, f1, f2, f1, f2);
  ck_assert_int_eq(res1, res2);

  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_e) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "<%#e>|<%#.e>|<%#5.e>|<%#.0e>|<%#0.0e> %%";
  double num = -665695342471359.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_c) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "<%6.4c>|<%-6.4c>|<%4.10lc>|<%-4.10lc>|<%-0lc>";
  int a = 10;
  unsigned long int b = 10;
  unsigned long int c = 10;
  ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                   s21_sprintf(str2, str3, a, a, b, c, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_E) {
  char str1[300] = "";
  char str2[300] = "";
  double num1 = .3529373967;
  double num2 = .0003529373967;
  double num3 = 0.00000003529373967;
  char *str3 = "<% 30.1E>|<% 30.E>|<%030.0E>";
  ck_assert_int_eq(sprintf(str1, str3, num1, num2, num3),
                   s21_sprintf(str2, str3, num1, num2, num3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_i) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%i><%3.i><%5.7i><%10i><%#i><%-i><%+i><%.i><% .i>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val,
                  val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_on) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "text %o %n  %o%n";
  int val = 012;
  int val2 = 017;
  int valn1 = 0, valn2 = 0, valn3 = 0, valn4 = 0;
  ck_assert_int_eq(sprintf(str1, str3, val, &valn1, val2, &valn3),
                   s21_sprintf(str2, str3, val, &valn2, val2, &valn4));
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(valn1, valn2);
  ck_assert_int_eq(valn3, valn4);
}
END_TEST

START_TEST(s21_sprintf_o) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%o><%3.o><%5.7o><%10o %#o %-o %+o %.o % .o>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_p) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%0p><%06p><%05.7p><%0.7p Oof %0.p>";
  char *val = "32";
  char *val2 = "8899";
  char *val3 = "91918";
  char *val4 = "32311";
  char *val5 = "8894";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_s) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<% s><% 3.s><% 5.7s><% 10s GOD %.s>";
  char *val = "WHAT IS THIS>";
  char *val2 = "i don't care anymore, really";
  char *val3 = "PPAP";
  char *val4 = "I don't feel so good";
  char *val5 = "What is lovin'?!";
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_u) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%u><%3.u><%5.7u><%10u><%#u><%-u><%+u><%.u><% .u>";
  unsigned int val = 0;
  sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_f) {
  char str1[400] = "";
  char str2[400] = "";
  char *str3 = "<%Lf>|<%.Lf>|<%+-#Lf>|<%+#.Lf>|<%-#.Lf>";
  long double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_g) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%g>|<%.0g>|<%4.2g>|<%4.g>|<%5.10g>";
  double num = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_x) {
  char str1[200] = "";
  char str2[200] = "";
  char *str3 = "<%x><%3.x><%5.7x><%10x><%#x><%-x><%+x><%.x><% .x>";
  int val = 0;
  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_h) {
  char *s21_test_str = (char *)calloc(256, sizeof(char));
  char *lib_test_str = (char *)calloc(256, sizeof(char));

  short e = 0;
  short f = 32767;
  unsigned short b = 65535;
  int lib_res = sprintf(lib_test_str, "|%hi| |%hd| |%hu|", e, f, b);
  int s21_res = s21_sprintf(s21_test_str, "|%hi| |%hd| |%hu|", e, f, b);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_l) {
  char *s21_test_str = (char *)calloc(256, sizeof(char));
  char *lib_test_str = (char *)calloc(256, sizeof(char));
  long i = INT_MAX;
  long a = INT_MIN;
  unsigned long b = 4294967295;
  int lib_res = sprintf(lib_test_str, "|%li| |%ld| |%lu|", i, a, b);
  int s21_res = s21_sprintf(s21_test_str, "|%li| |%ld| |%lu|", i, a, b);

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_sprintf_empty) {
  char *s21_test_str = (char *)calloc(512, sizeof(char));
  char *lib_test_str = (char *)calloc(512, sizeof(char));

  int lib_res = sprintf(lib_test_str, "%c", '\0');
  int s21_res = s21_sprintf(s21_test_str, "%c", '\0');

  ck_assert_str_eq(s21_test_str, lib_test_str);
  ck_assert_int_eq(s21_res, lib_res);

  free(s21_test_str);
  free(lib_test_str);
}
END_TEST

START_TEST(s21_strlen_normal) {
  // Arrange
  char *test_str = "12345678";
  // Act
  int s21_result = s21_strlen(test_str);
  int lib_result = strlen(test_str);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strlen_empty) {
  char *test_str = "";

  int s21_result = s21_strlen(test_str);
  int lib_result = strlen(test_str);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

// s21_strstr
START_TEST(s21_strstr_normal) {
  char *test_haystack = "12345678";
  char *test_needle = "3";

  char *s21_result = s21_strstr(test_haystack, test_needle);
  char *lib_result = strstr(test_haystack, test_needle);

  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strstr_SF) {
  char *test_haystack = "67878";
  char *test_needle = "345";

  char *s21_result = s21_strstr(test_haystack, test_needle);
  char *lib_result = strstr(test_haystack, test_needle);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strstr_empty) {
  char *test_haystack = "123456";
  char *test_needle = "";

  char *s21_result = s21_strstr(test_haystack, test_needle);
  char *lib_result = strstr(test_haystack, test_needle);

  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strstr_all_empty) {
  char *test_haystack = "";
  char *test_needle = "";

  char *s21_result = s21_strstr(test_haystack, test_needle);
  char *lib_result = strstr(test_haystack, test_needle);

  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_equal_mid) {
  char *test_str = "12345";
  char *test_substr = "12345";
  s21_size_t n = 3;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_equal) {
  char *test_str = "12345";
  char *test_substr = "12345";
  s21_size_t n = 5;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_start_dif_plus) {
  char *test_str = "22345";
  char *test_substr = "12345";
  s21_size_t n = 7;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_start_dif_minus) {
  char *test_str = "12345";
  char *test_substr = "22345";
  s21_size_t n = 4;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_start_empty) {
  char *test_str = "22345";
  char *test_substr = "";
  s21_size_t n = 3;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_zero_n) {
  char *test_str = "22345";
  char *test_substr = "12345";
  s21_size_t n = 0;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_mid_dif) {
  char *test_str = "12345";
  char *test_substr = "13545";
  s21_size_t n = 4;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncmp_all_empty) {
  char *test_str = "";
  char *test_substr = "";
  s21_size_t n = 4;

  int s21_result = s21_strncmp(test_str, test_substr, n);
  int lib_result = strncmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_normal_equal) {
  char *test_str = "12345";
  char *test_substr = "12345";
  s21_size_t n = 5;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_zero_n) {
  char *test_str = "02345";
  char *test_substr = "12345";
  s21_size_t n = 0;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_normal_plus) {
  char *test_str = "12346";
  char *test_substr = "12345";
  s21_size_t n = 2;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_normal_minus) {
  char *test_str = "02346";
  char *test_substr = "04345";
  s21_size_t n = 2;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_all_empty) {
  char *test_str = "";
  char *test_substr = "";
  s21_size_t n = 0;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_empty_str) {
  char *test_str = "0";
  char *test_substr = "46545";
  s21_size_t n = 2;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memcmp_empty_substr) {
  char *test_str = "46426";
  char *test_substr = "1";
  s21_size_t n = 2;

  int s21_result = s21_memcmp(test_str, test_substr, n);
  int lib_result = memcmp(test_str, test_substr, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

// s_21_memchr
START_TEST(s21_memchr_normal) {
  // Arrange
  char *str = "ABCDEFG";
  char sym = 'D';
  s21_size_t n = strlen(str);
  // Act
  char *s21_result = s21_memchr(str, sym, n);
  char *lib_result = memchr(str, sym, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memchr_empty_str) {
  // Arrange
  char *str = "";
  char sym = 'D';
  s21_size_t n = strlen(str);
  // Act
  char *s21_result = s21_memchr(str, sym, n);
  char *lib_result = memchr(str, sym, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memchr_empty_sym) {
  // Arrange
  char *str = "ABCDEFG";
  char sym = '\0';
  s21_size_t n = strlen(str);
  // Act
  char *s21_result = s21_memchr(str, sym, n);
  char *lib_result = memchr(str, sym, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memchr_n_zero) {
  // Arrange
  char *str = "ABCDEFG";
  char sym = 'D';
  s21_size_t n = 0;
  // Act
  char *s21_result = s21_memchr(str, sym, n);
  char *lib_result = memchr(str, sym, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_memchr_empty_str_sym) {
  // Arrange
  char *str = "";
  char sym = '\0';
  s21_size_t n = strlen(str);
  // Act
  char *s21_result = s21_memchr(str, sym, n);
  char *lib_result = memchr(str, sym, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

// s21_strcat
START_TEST(s21_strcat_test_1) {
  char test_str[50] = {"Hello, World!"};
  char str_s21[2048] = {""};
  char str_original[2048] = {""};
  ck_assert_pstr_eq(s21_strcat(str_s21, test_str),
                    strcat(str_original, test_str));
  ck_assert_pstr_eq(str_s21, str_original);
}

// s21_strncat
START_TEST(s21_strncat_normal) {
  // Arrange
  char str_1[20] = "hello";
  char str_2[20] = "hello";
  char *str_3 = "world";
  s21_size_t n = 3;
  // Act
  char *s21_result = s21_strncat(str_1, str_3, n);
  char *lib_result = strncat(str_2, str_3, n);
  // Assert
  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncat_first_str_empty) {
  // Arrange
  char str_1[20] = "";
  char *str_2 = "world";
  s21_size_t n = 3;
  // Act
  char *s21_result = s21_strncat(str_1, str_2, n);
  char *lib_result = strncat(str_1, str_2, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncat_second_str_empty) {
  // Arrange
  char str_1[20] = "hello";
  char *str_2 = "";
  s21_size_t n = 3;
  // Act
  char *s21_result = s21_strncat(str_1, str_2, n);
  char *lib_result = strncat(str_1, str_2, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncat_both_str_empty) {
  // Arrange
  char str_1[20] = "";
  char *str_2 = "";
  s21_size_t n = 3;
  // Act
  char *s21_result = s21_strncat(str_1, str_2, n);
  char *lib_result = strncat(str_1, str_2, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncat_size_empty) {
  // Arrange
  char str_1[20] = "hello";
  char *str_2 = "world";
  s21_size_t n = 0;
  // Act
  char *s21_result = s21_strncat(str_1, str_2, n);
  char *lib_result = strncat(str_1, str_2, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncat_size_zero) {
  // Arrange
  char str_1[20] = "hello";
  char *str_2 = "world";
  s21_size_t n = 0;
  // Act
  char *s21_result = s21_strncat(str_1, str_2, n);
  char *lib_result = strncat(str_1, str_2, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strncat_all_empty) {
  // Arrange
  char str_1[20] = "";
  char *str_2 = "";
  s21_size_t n = 0;
  // Act
  char *s21_result = s21_strncat(str_1, str_2, n);
  char *lib_result = strncat(str_1, str_2, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

// s21_strchr
START_TEST(s21_strchr_normal) {
  // Arrange
  char *str_1 = "hello";
  char n = 'h';
  // Act
  char *s21_result = s21_strchr(str_1, n);
  char *lib_result = strchr(str_1, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strchr_empty_str) {
  // Arrange
  char *str_1 = "";
  char n = 'h';
  // Act
  char *s21_result = s21_strchr(str_1, n);
  char *lib_result = strchr(str_1, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strchr_empty_sym) {
  // Arrange
  char *str_1 = "hello";
  char n = '\0';
  // Act
  char *s21_result = s21_strchr(str_1, n);
  char *lib_result = strchr(str_1, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strchr_both_empty) {
  // Arrange
  char *str_1 = "";
  char n = '\0';
  // Act
  char *s21_result = s21_strchr(str_1, n);
  char *lib_result = strchr(str_1, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

// s21_strcspn
START_TEST(s21_strcspn_normal) {
  char *str = "hello, world";
  char *keys = "wl";
  // Act
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strcspn_empty_str) {
  char *str = "";
  char *keys = "wl";
  // Act
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strcspn_empty_key) {
  char *str = "hello, world";
  char *keys = "";
  // Act
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strcspn_both_key) {
  char *str = "";
  char *keys = "";
  // Act
  s21_size_t s21_result = s21_strcspn(str, keys);
  s21_size_t lib_result = strcspn(str, keys);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

// s21_strrchr
START_TEST(s21_strrchr_normal) {
  // Arrange
  char *str_1 = "hehllo";
  char n = 'h';
  // Act
  char *s21_result = s21_strrchr(str_1, n);
  char *lib_result = strrchr(str_1, n);
  // Assert
  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strrchr_empty_str) {
  // Arrange
  char *str_1 = "";
  char n = 'h';
  // Act
  char *s21_result = s21_strrchr(str_1, n);
  char *lib_result = strrchr(str_1, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strrchr_empty_sym) {
  // Arrange
  char *str_1 = "hello";
  char n = '\0';
  // Act
  char *s21_result = s21_strrchr(str_1, n);
  char *lib_result = strrchr(str_1, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strrchr_both_empty) {
  // Arrange
  char *str_1 = "";
  char n = '\0';
  // Act
  char *s21_result = s21_strrchr(str_1, n);
  char *lib_result = strrchr(str_1, n);
  // Assert
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

// s21_strspn
START_TEST(s21_strspn_normal) {
  // Arrange
  char str_1[12] = "hello world";
  char *str_2 = "world";
  // Act
  int s21_result = s21_strspn(str_1, str_2);
  int lib_result = strspn(str_1, str_2);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strspn_normal_2) {
  // Arrange
  char str_1[12] = "hello";
  char *str_2 = "hello";
  // Act
  int s21_result = s21_strspn(str_1, str_2);
  int lib_result = strspn(str_1, str_2);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strspn_first_str_empty) {
  // Arrange
  char *str_1 = "";
  char *str_2 = "world";
  // Act
  int s21_result = s21_strspn(str_1, str_2);
  int lib_result = strspn(str_1, str_2);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strspn_second_str_empty) {
  // Arrange
  char str_1[12] = "hello world";
  char *str_2 = "";
  // Act
  int s21_result = s21_strspn(str_1, str_2);
  int lib_result = strspn(str_1, str_2);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strspn_str2_not_in_str1) {
  // Arrange
  char str_1[12] = "hello world";
  char *str_2 = "mac";
  // Act
  int s21_result = s21_strspn(str_1, str_2);
  int lib_result = strspn(str_1, str_2);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_strspn_both_empty) {
  // Arrange
  char *str_1 = "";
  char *str_2 = "";
  // Act
  int s21_result = s21_strspn(str_1, str_2);
  int lib_result = strspn(str_1, str_2);
  // Assert
  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(s21_sscanf_c) {
  char format[] = "%c";
  char str[] = "\t\n\n  1 \n  \t";
  char c1, c2;

  int16_t res1 = s21_sscanf(str, format, &c1);
  int16_t res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(s21_sscanf_d) {
  char format[] = "%d";
  char str[] = "";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_d_width) {
  char format[] = "%2d %4d";
  char str[] = "87654 1234";
  int p1, p2;
  int q1, q2;

  int16_t res1 = s21_sscanf(str, format, &p1, &q1);
  int16_t res2 = sscanf(str, format, &p2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
  ck_assert_int_eq(q1, q2);
}
END_TEST

START_TEST(s21_sscanf_x_X) {
  char format[] = "%x %x";
  char str[] = "8abc 8ABC";
  int p1, p2;
  int q1, q2;

  int16_t res1 = s21_sscanf(str, format, &p1, &q1);
  int16_t res2 = sscanf(str, format, &p2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
  ck_assert_int_eq(q1, q2);
}
END_TEST

START_TEST(s21_sscanf_p) {
  char format[] = "%p";
  char str[] = "     ";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_f) {
  char format[] = "%f";
  char str[] = "\n";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_fexp) {
  char format[] = "%f %f";
  char str[] = "123e+04 123E-04";
  float p1, p2;
  float q1, q2;

  int res1 = s21_sscanf(str, format, &p1, &q1);
  int res2 = sscanf(str, format, &p2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(p1, p2);
  ck_assert_float_eq(q1, q2);
}
END_TEST

START_TEST(s21_sscanf_fexp_l) {
  char format[] = "%lf %Lf";
  char str[] = "123e+04 123e-04";
  double p1, p2;
  long double q1, q2;

  int res1 = s21_sscanf(str, format, &p1, &q1);
  int res2 = sscanf(str, format, &p2, &q2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq((float)p1, (float)p2);
  ck_assert_float_eq((float)q1, (float)q2);
}
END_TEST

START_TEST(s21_sscanf_f_n) {
  char format[] = "%f %f %n";
  char str[] = "123e+04 123e-04";

  char format2[] = "%f %f %n";
  char str2[] = "123e+04 123e-04";
  float p1, p2;
  float q1, q2;
  int n1, n2;

  int res1 = s21_sscanf(str, format, &p1, &q1, &n1);
  int res2 = sscanf(str2, format2, &p2, &q2, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(p1, p2);
  ck_assert_float_eq(q1, q2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sscanf_f_n_2) {
  char format[] = "%f %f %n";
  char str[] = "1L23e+04 123e-04";

  char format2[] = "%f %f %n";
  char str2[] = "1L23e+04 123e-04";
  float p1, p2;
  float q1, q2;
  int n1 = 0, n2 = 0;

  int res1 = s21_sscanf(str, format, &p1, &q1, &n1);
  int res2 = sscanf(str2, format2, &p2, &q2, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(p1, p2);
  ck_assert_float_eq(q1, q2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sscanf_d_n) {
  char format[] = "%d %d %n";
  char str[] = "123 125";

  char format2[] = "%d %d %n";
  char str2[] = "123 125";
  float p1, p2;
  float q1, q2;
  int n1, n2;

  int res1 = s21_sscanf(str, format, &p1, &q1, &n1);
  int res2 = sscanf(str2, format2, &p2, &q2, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(p1, p2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(s21_sscanf_inf) {
  char format[] = "%f";
  char str[] = "inf";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_nan) {
  char format[] = "%f";
  char str[] = "nan";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_o) {
  char format[] = "%o";
  char str[] = "\t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_x) {
  char format[] = "%x";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_empty) {
  char format[] = "";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_t) {
  char format[] = "\t";
  char str[] = "\t\n\n   \n  \t";
  int p1, p2;

  int16_t res1 = s21_sscanf(str, format, &p1);
  int16_t res2 = sscanf(str, format, &p2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_h) {
  char format[] = "%hi%hd%hi";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_l) {
  char format[] = "%li %li %ld";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_skip_x_variation1) {
  char format[] = "%*x %*x %*x";
  char str[] = "0x123 +04 -372f3";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_skip_x_variation2) {
  char format[] = "%*x %*x %x";
  char str[] = "0x123 +04 -372f3";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_skip_x_variation3) {
  char format[] = "%x %*x %*x";
  char str[] = "0x123 +04 -372f3";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_skip_x_variation4) {
  char format[] = "%*x %x %*x";
  char str[] = "0x123 +04 -372f3";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_skip_x_variation5) {
  char format[] = "%x %*x %x";
  char str[] = "0x123 +04 -372f3";
  unsigned int d1 = 0, d2 = 0;
  unsigned int q1 = 0, q2 = 0;
  unsigned int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_fg) {
  char format[] = "%fg %f w%fx";
  char str[] = "75g +19.8w -87.x";
  float d1, d2;
  float q1, q2;
  float z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST
// самописные
START_TEST(s21_sscanf_fg2) {
  char format[] = "%fg%% %f w%fx";
  char str[] = "75g% +19.8w -87.x";
  float d1, d2;
  float q1, q2;
  float z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(q1, q2);
  ck_assert_float_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_s) {
  char format[] = "%s";
  char str[] = "some str";
  char buf1[100] = {0};
  char buf2[100] = {0};

  int16_t res1 = s21_sscanf(str, format, buf1);
  int16_t res2 = sscanf(str, format, buf2);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s21_sscanf_cw3) {
  char format[] = "%c%c";
  char str[] = "qwerty";
  char str2[] = "qwerty";
  char c1 = 0, c2 = 0;
  char q1 = 0, q2 = 0;

  int16_t res2 = sscanf(str2, format, &c2, &q2);
  int16_t res1 = s21_sscanf(str, format, &c1, &q1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(q2, q1);
}
END_TEST

START_TEST(s21_sscanf_0x) {
  char format[] = "%x %2x w%X";
  char str[] = "0x1234 156 w789A";

  char format2[] = "%x %2x w%X";
  char str2[] = "0x1234 156 w789A";
  int d1 = 1, d2 = 1;
  int q1 = 2, q2 = 2;
  int z1 = 3, z2 = 3;
  int res2 = sscanf(str2, format2, &d2, &q2, &z2);
  int res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_0) {
  char format[] = "%o %2o w%o";
  char str[] = "01234 156 w789A";

  char format2[] = "%o %2o w%o";
  char str2[] = "01234 156 w789A";
  int d1 = 1, d2 = 1;
  int q1 = 2, q2 = 2;
  int z1 = 3, z2 = 3;
  int res2 = sscanf(str2, format2, &d2, &q2, &z2);
  int res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(q1, q2);
  ck_assert_int_eq(z1, z2);
}
END_TEST

START_TEST(s21_sscanf_u) {
  char format[] = "%u%hu%lu";
  char str[] = "123 198 87";
  unsigned int d1, d2;
  unsigned short q1, q2;
  unsigned long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST


START_TEST(test_d_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%d";
  int val = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0d";
  int val = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.d";
  int val = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.3d";
  int val = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.3d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.d";
  int val = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%10d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_13) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%10.0d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%10.15d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%*.*d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, 10, 15, val),
                   sprintf(str2, format, 10, 15, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%25.15d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%025.15d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%010d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%10d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_20) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-010d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_21) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-010.15d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_22) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-025.15d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_23) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% -025.15d";
  int val = -1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_24) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% +-025.15d";
  int val = -1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_25) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% +-025.15d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_26) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+-025.15d";
  int val = 1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_27) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+-025.15d";
  int val = -1234567;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_28) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+-025.15hd";
  int val = 12345;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_29) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+-025.15ld";
  long int val = 12345;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_30) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "This is a simple value %d";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_31) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5i";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_32) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5d";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_33) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5i";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_34) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+12d";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_35) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%012i";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_36) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0*d";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_37) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.*i";
  int val = 79;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_38) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char format[] = "%0.*i %d %4.*i %013d %d";
  int val = 79;
  ck_assert_int_eq(
      s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581),
      sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_39) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+5.31li";
  long int val = 798518581899;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_40) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16.9hi";
  short int val = 7968;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_41) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%0.*ld";
  long val = 7591365175;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_42) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.0d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_43) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_44) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hd";
  short int val = 13130;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_45) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d", 777), sprintf(str2, "%d", 777));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_46) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -888, 0, 777, -200),
                   sprintf(str2, "%d%d%d%d", -888, 0, 777, -200));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_47) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i", -0), sprintf(str2, "%i", -0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_48) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -888, 0, 777, -200),
                   sprintf(str2, "%i%i%i%i", -888, 0, 777, -200));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_49) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%10ld";

  ck_assert_int_eq(s21_sprintf(str1, format, 1), sprintf(str2, format, 1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_d_50) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.1d";

  ck_assert_int_eq(s21_sprintf(str1, format, 222), sprintf(str2, format, 222));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -u ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_u_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  unsigned int val = 13130;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15u";
  unsigned int val = 13130;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16u";
  unsigned int val = 13130;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51u";
  unsigned int val = 13130;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% 5.51u";
  unsigned int val = 13130;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%hu";
  unsigned short int val = 13130;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu";
  unsigned long int val = 938249314230;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 938249314230;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 13, 1331, 13313, 9782),
      sprintf(str2, format, val, (unsigned)13, (unsigned short)1331,
              (unsigned)13313, (unsigned)9782));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                   sprintf(str2, "%u", (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%u%u%u%u", 888, 0, 777, 300),
                   sprintf(str2, "%u%u%u%u", (unsigned)888, (unsigned)0,
                           (unsigned)777, (unsigned)300));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%6.6u";

  ck_assert_int_eq(s21_sprintf(str1, format, 12342251),
                   sprintf(str2, format, 12342251));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_u_13) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-5.15u";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-15.5u";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  unsigned val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.0u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%020.15u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_20) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#020.15u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_21) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% #020.15u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_22) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+ #020.15u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_u_23) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+ #0*.*u";
  unsigned val = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, 20, 15, val),
                   sprintf(str2, format, 20, 15, val));

  ck_assert_str_eq(str1, str2);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -o -x -X
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_ox_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-16o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#o";
  int val = 57175;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo";
  long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo, %o, %ho, %.5o, %5.o";
  long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo";
  long int val = 84518;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_13) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-10x%x%X%#x%#X%5.5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val, val, val, val, val),
                   sprintf(str2, format, val, val, val, val, val, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-5.10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#x";
  unsigned val = 18571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#hx";
  unsigned short val = 12352;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#lx";
  unsigned long val = 18571757371571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#2x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#30x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_20) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "%x", (unsigned)INT32_MIN),
                   sprintf(str2, "%x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", INT32_MAX),
                   sprintf(str2, "%x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_21) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%X", (unsigned)INT32_MIN),
                   sprintf(str2, "%X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", INT32_MAX),
                   sprintf(str2, "%X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_22) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_23) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-3x", (unsigned)INT32_MIN),
                   sprintf(str2, "%-3x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", 0), sprintf(str2, "%-3x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", INT32_MAX),
                   sprintf(str2, "%-3x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_24) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%13x", (unsigned)INT32_MIN),
                   sprintf(str2, "%13x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", 0), sprintf(str2, "%13x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", INT32_MAX),
                   sprintf(str2, "%13x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_25) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MIN),
                   sprintf(str2, "%-60X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", 0), sprintf(str2, "%-60X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MAX),
                   sprintf(str2, "%-60X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_26) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%7X", (unsigned)INT32_MIN),
                   sprintf(str2, "%7X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", 0), sprintf(str2, "%7X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", INT32_MAX),
                   sprintf(str2, "%7X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_27) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_28) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(
      s21_sprintf(str1, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_29) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MIN),
                   sprintf(str2, "%#x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", 0), sprintf(str2, "%#x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MAX),
                   sprintf(str2, "%#x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_30) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MIN),
                   sprintf(str2, "%#X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", 0), sprintf(str2, "%#X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MAX),
                   sprintf(str2, "%#X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_31) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_32) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_33) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MIN),
                   sprintf(str2, "%*x", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, 0),
                   sprintf(str2, "%*x", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MAX),
                   sprintf(str2, "%*x", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_34) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MIN),
                   sprintf(str2, "%*X", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, 0),
                   sprintf(str2, "%*X", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MAX),
                   sprintf(str2, "%*X", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_35) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#*x%*x%-12x%3x%*x", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*x%*x%-12x%3x%*x", 9, 127312897, -0, -1,
                           199, -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_36) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1, 199,
                           -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_37) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  int a = s21_sprintf(str1, "%*.6x", 11, 0);
  int b = sprintf(str2, "%*.6x", 11, 0);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_38) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  int a = s21_sprintf(str1, "%*.6X", 11, INT32_MIN);
  int b = sprintf(str2, "%*.6X", 11, (unsigned)INT32_MIN);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_39) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int a = s21_sprintf(
      str1, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
      4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
  int b = sprintf(str2, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x",
                  3, 126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9,
                  41, -41, 33);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_40) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X",
                  3, -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
                  41, -41, 33),
      sprintf(str2, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
              -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9, 41,
              -41, 33));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_41) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                   sprintf(str2, "%hx", (unsigned short)-11));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                   sprintf(str2, "%hx", (unsigned short)0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                   sprintf(str2, "%hx", (unsigned short)11));
  ck_assert_str_eq(str1, str2);
  long unsigned int val = INT32_MAX;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
  ck_assert_str_eq(str1, str2);
  long unsigned int v = 0;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_42) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                   sprintf(str2, "%hx", (unsigned short)-11));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                   sprintf(str2, "%hx", (unsigned short)0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                   sprintf(str2, "%hx", (unsigned short)11));
  ck_assert_str_eq(str1, str2);
  long unsigned int val = INT32_MAX;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
  ck_assert_str_eq(str1, str2);
  long unsigned int v = 0;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_43) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.5o";

  ck_assert_int_eq(s21_sprintf(str1, format, 12345),
                   sprintf(str2, format, 12345));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_44) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#5lX";
  long hex = 314818438141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_45) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_ox_50) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-5.15x%#-5.15o";
  unsigned val = 858158158;
  unsigned val2 = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_51) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#-15.5x%#-15.5o";
  unsigned val = 858158158;
  unsigned val2 = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_52) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%x%o";
  unsigned val = 0;
  unsigned val2 = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_53) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%o%x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_54) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.o%.x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_55) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.0o%.0x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_56) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%020.15o%020.15x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_57) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%#020.15o%#020.15x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_58) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% #020.15o% #020.15x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_59) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+ #020.15o%+ #020.15x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2),
                   sprintf(str2, format, val, val2));

  ck_assert_str_eq(str1, str2);
}

START_TEST(test_ox_60) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+ #0*.*o%+ #0*.*x";
  unsigned val = 123450;
  unsigned val2 = 123450;
  ck_assert_int_eq(s21_sprintf(str1, format, 20, 15, val, 20, 15, val2),
                   sprintf(str2, format, 20, 15, val, 20, 15, val2));

  ck_assert_str_eq(str1, str2);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_c_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%c";
  unsigned val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%c";
  char val = 'X';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.5c";
  char val = 'n';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% -5c";
  char val = 'n';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15c";
  char val = 'n';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c%c%c%c%c Hello! WORLD";
  char val = 'n';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                   sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-5.3c";
  char val = 'n';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'N', 'n'),
                   sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'N', 'n'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'),
                   sprintf(str2, "%-8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'M', 'm'),
      sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'M', 'm'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_13) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%8.3c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+5.5d hello";

  int val = 10000;
  int a = s21_sprintf(str1, format, val);
  int b = sprintf(str2, format, val);
  ck_assert_int_eq(a, b);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_c_16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "This is a simple wide char %5c";
  char w = 'w';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -s ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_s_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.15s";
  char *val = "HAPPY NEW YEAR 2024!";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15s";
  char *val = "8 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%-15.9s";
  char *val = "8 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val = "8 IS MY FAVORITE NUMBER. I LIVE IN MOSCOW";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s%s%s%s";
  char *val = "I LIVE IN MOSCOW";
  char *s1 = "";
  char *s2 = "123456789 123456789 123456789";
  char *s3 = "hello world";
  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *val = "abcdefgjklmn";
  char *format = "%120s";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%s";
  char *val = "Happy New Year and Merry Christmas!";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%s", "Hello my fiends"),
                   sprintf(str2, "%s", "Hello my fiends"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%s%s%s%s%s", "Hello", " ", "World", " ",
                               "I am from school21"),
                   sprintf(str2, "%s%s%s%s%s", "Hello", " ", "World", " ",
                           "I am from school21"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.4s";

  ck_assert_int_eq(s21_sprintf(str1, format, "hello world"),
                   sprintf(str2, format, "hello world"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s";

  ck_assert_int_eq(s21_sprintf(str1, format, "hello world"),
                   sprintf(str2, format, "hello world"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_13) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% s% c";

  ck_assert_int_eq(s21_sprintf(str1, format, "", 's'),
                   sprintf(str2, format, "", 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%210s";

  ck_assert_int_eq(s21_sprintf(str1, format, "AHHAHAHA\0AHHAHAHAH"),
                   sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_s_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-115s";

  ck_assert_int_eq(s21_sprintf(str1, format, "Hello World"),
                   sprintf(str2, format, "Hello World"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -p ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_p_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_p_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%15p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_p_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%5p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST
/*
// мак <0x0> линукс <(nil)>
START_TEST(test_p_nil) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%p";
  char *ptr = NULL;
  ck_assert_int_eq(s21_sprintf(str1, format, ptr), sprintf(str2, format, ptr));

  ck_assert_str_eq(str1, str2);
}
END_TEST
*/
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -f ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_f_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 1.1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 1.9;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 0.0001;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  ck_assert_int_eq(s21_sprintf(str1, format, 0.0001),
                   sprintf(str2, format, 0.0001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 505.010237890;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f%f%f%f";
  float val = 101.0000001;
  float val2 = 101.0000005;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, val2, 101.0000001, 101.0000005),
      sprintf(str2, format, val, val2, 101.0000001, 101.0000005));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f%f";
  float val = 101.0000006;
  ck_assert_int_eq(s21_sprintf(str1, format, val, 101.0000006),
                   sprintf(str2, format, val, 101.0000006));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f%f%f%f";
  float val = 0.00000001;
  float val2 = 0.00000008;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2, 0.00000001, 0.00000008),
                   sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.f%.f%.f%.f";
  float val = 0.000139;
  float val2 = 55.17;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2, 0.000139, 55.17),
                   sprintf(str2, format, val, val2, 0.000139, 55.17));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f%f%f%f";
  float val = -0.000139;
  float val2 = -55.17;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2, -0.000139, -55.17),
                   sprintf(str2, format, val, val2, -0.000139, -55.17));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f%f%f%f%f%f";
  float val = -0.0000001;
  float val2 = -0.0000005;
  float val3 = -0.0000007;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val2, val3, -0.0000001,
                               -0.0000005, -0.0000007),
                   sprintf(str2, format, val, val2, val3, -0.0000001,
                           -0.0000005, -0.0000007));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.f %.0f %#.f %#.0f";
  ck_assert_int_eq(s21_sprintf(str1, format, 0.3, 55.12, 533.0485, 32.0),
                   sprintf(str2, format, 0.3, 55.12, 533.0485, 32.0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#.9f %#.2f %#f";
  ck_assert_int_eq(s21_sprintf(str1, format, 0.3, 55.12, 444.444),
                   sprintf(str2, format, 0.3, 55.12, 444.444));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-0f % +10f % +10.2f";
  ck_assert_int_eq(s21_sprintf(str1, format, 4.05, 21.09, 444.444),
                   sprintf(str2, format, 4.05, 21.09, 444.444));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%Lf %#Lf %15.8Lf";
  long double num1 = 4.05;
  long double num2 = 21.09;
  long double num3 = 444.444;

  ck_assert_int_eq(s21_sprintf(str1, format, num1, num2, num3),
                   sprintf(str2, format, num1, num2, num3));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  long double num1 = 123.456789;
  long double num2 = -987654.321;
  long double num3 = 0.000123456789;
  long double num4 = 9999.9999;

  char format[] = "Num1: %Lf, Num2: %.2Lf, Num3: %#.10Lf, Num4: %Lf";
  ck_assert_int_eq(s21_sprintf(str1, format, num1, num2, num3, num4),
                   sprintf(str2, format, num1, num2, num3, num4));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_20) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_21) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 12.34;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_22) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5f";
  float val = 12.34;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_23) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%13f";
  float val = 12.34;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_24) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_25) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%13f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_26) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-13f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_27) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-14f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_28) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-13f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_29) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-#13.f";
  float val = 0112345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_30) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-13.f";
  float val = 0112345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_31) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-#13.f";
  float val = 012345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_32) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-#13.0f";
  float val = -012345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_33) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-0#13.0f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_34) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.0f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_35) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_36) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.1f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_37) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.7f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_38) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.15f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_39) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#25.15f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_40) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#25.15f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_41) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0#25.15f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_42) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0#25.15f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_43) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% +0#25.15f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_44) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#25.15f";
  float val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_45) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% +0#25.15f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_46) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#25.15f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_47) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#*.*f";
  float val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, 25, 12, val),
                   sprintf(str2, format, 25, 12, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_48) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#*.*Lf";
  long double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, 25, 12, val),
                   sprintf(str2, format, 25, 12, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_49) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#*.*lf";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, 25, 12, val),
                   sprintf(str2, format, 25, 12, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_50) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%f";
  float val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_51) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_52) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%10Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_53) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_54) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_55) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_56) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Lf";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_57) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Lf";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_58) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_59) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0f %.lf %Lf %f %lf %Lf";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 9851.51351;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_60) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                   sprintf(str2, "%f", 0.0001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_61) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  ck_assert_int_eq(
      s21_sprintf(str1, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001),
      sprintf(str2, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_62) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%1.1f";

  ck_assert_int_eq(s21_sprintf(str1, format, 1.1), sprintf(str2, format, 1.1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_63) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%7.7f";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.123456),
                   sprintf(str2, format, 11.123456));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_64) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 121.123),
                   sprintf(str2, format, 121.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_65) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.111),
                   sprintf(str2, format, 111.111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_f_66) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.Lf";
  long double a = 7.9418438184;

  ck_assert_int_eq(s21_sprintf(str1, format, a), sprintf(str2, format, a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -e ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_e_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e";
  double val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e";
  double val = 12.34;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5e";
  double val = 12.34;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%13e";
  double val = 12.34;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_5) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%13e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-13e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-14e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-13e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-#13.e";
  double val = 0112345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-13.e";
  double val = 0112345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-#13.e";
  double val = 012345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_13) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-#13.0e";
  double val = -012345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-#13.0e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%-0#13.0e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.0e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_17) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_18) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.1e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_19) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.7e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_20) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#13.15e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST


START_TEST(test_e_22) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%0#25.15e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_23) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0#25.15e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_24) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0#25.15e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_25) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% +0#25.15e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_26) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#25.15e";
  double val = -12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_27) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% +0#25.15e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_28) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#25.15e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_29) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#*.*e";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, 25, 12, val),
                   sprintf(str2, format, 25, 12, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_30) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#*.*Le";
  long double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, 25, 12, val),
                   sprintf(str2, format, 25, 12, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_31) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+0#*.*le";
  double val = 12345.6789;
  ck_assert_int_eq(s21_sprintf(str1, format, 25, 12, val),
                   sprintf(str2, format, 25, 12, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_32) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E";
  double val = 12.34;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_33) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E";
  double val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_34) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%Le";
  long double val = 123 * pow(10, 98);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_35) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.0Le";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_36) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.Le";
  long double val = 15.000009121;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_37) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Le";
  long double val = 0.000000000000000123;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_38) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%.15Le";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_39) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%Le";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_40) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%015E";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_41) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "%15e";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_42) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char *format = "% .0e %.le %Le %e %le %Le";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 0.094913941;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_43) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e";
  double x = 111;
  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_44) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e%e%e%e";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.111, 222.2222, 666., -555.125),
                   sprintf(str2, format, 11.111, 222.2222, 666., -555.125));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_45) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%Le";
  long double x = 122.1231;

  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_46) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%.10e";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.184314818),
                   sprintf(str2, format, 111.184314818));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_47) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.3e%3.2e%lf";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.000111, 111.555, 1.999),
                   sprintf(str2, format, 0.000111, 111.555, 1.999));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_48) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.666666),
                   sprintf(str2, format, 0.666666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_49) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%E%E%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.0000999, 111.9999, 6.666),
                   sprintf(str2, format, 0.0000999, 111.9999, 6.666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_50) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%e ABOBA %Lf %Lf %Le";
  long double c = 848181;
  long double a = 0.00000001;
  long double b = 1111111.11;
  ck_assert_int_eq(s21_sprintf(str1, format, 123.123, a, b, c),
                   sprintf(str2, format, 123.123, a, b, c));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_e_51) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%#e Floppa %#E%#f";

  ck_assert_int_eq(s21_sprintf(str1, format, 123.111, 0.0000999, 0.555),
                   sprintf(str2, format, 123.111, 0.0000999, 0.555));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags -g ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_g_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = 1234;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = -1234;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = 123.12;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = -123.12;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST



START_TEST(test_g_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = 12345.0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_8) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = -12345.0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_9) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = 123456789.123456789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_10) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = -123456789.123456789;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_11) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%Lg";
  long double val = 123456789 * pow(10, 98);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_12) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%Lg";
  long double val = -123456789 * pow(10, 98);
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_13) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_14) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double val = -0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_15) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.50300;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_g_16) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 5131.43141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  const char *format = "Value: %% and Number: %d";
  int number = 42;

  ck_assert_int_eq(s21_sprintf(str1, format, number),
                   sprintf(str2, format, number));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ tests flags mix ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

START_TEST(test_mix_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%li%ld%lu";

  ck_assert_int_eq(s21_sprintf(str1, format, 777777777777, 888, 333),
                   sprintf(str2, format, 777777777777, 888, 333));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_mix_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%hi%hd%hu";

  ck_assert_int_eq(s21_sprintf(str1, format, 777, -888, 111),
                   sprintf(str2, format, 777, -888, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_mix_3) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+li%+lu%+d%+lf";

  ck_assert_int_eq(s21_sprintf(str1, format, -123, 321, -5555, -1213.123),
                   sprintf(str2, format, -123, 321, -5555, -1213.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_mix_4) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "% 0.0li% 0.0lu% 0.0ld % 0.0lf";

  ck_assert_int_eq(s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232),
                   sprintf(str2, format, 1, 222, 33333333333, -166513.1232));

  ck_assert_str_eq(str1, str2);
}
END_TEST


START_TEST(test_mix_6) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%+2.1c%+4.2d%+5.4i%+10.2f%+55.55s%+1.1u";

  ck_assert_int_eq(s21_sprintf(str1, format, 'f', 21, 42, 777.777,
                               "Happy New Year and Merry Christmas!", 11),
                   sprintf(str2, format, 'f', 21, 42, 777.777,
                           "Happy New Year and Merry Christmas!", 11));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_mix_7) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int n1;
  int n2;
  int a = s21_sprintf(str1, "%d%n", 123, &n1);
  int b = sprintf(str2, "%d%n", 123, &n2);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_string_suite() {
  Suite *s;
  TCase *tc_insert, *tc_trim, *tc_strerror, *tc_sprintf, *tc_strncpy,
      *tc_memcpy, *tc_to_upper, *tc_strtok, *tc_strpbrk, *tc_memset, *tc_strlen,
      *tc_strstr, *tc_strncmp, *tc_memcmp, *tc_memchr, *tc_strncat, *tc_strcat,
      *tc_strchr, *tc_strcspn, *tc_strrchr, *tc_strspn, *tc_to_lower,
      *tc_sscanf;
  TCase *tc = tcase_create("sprintf_tc");

  s = suite_create("s21_string");

  tc = tcase_create("sprintf_new");
  tcase_add_test(tc, test_d_1);
  tcase_add_test(tc, test_d_2);
  tcase_add_test(tc, test_d_3);
  tcase_add_test(tc, test_d_4);
  tcase_add_test(tc, test_d_5);
  tcase_add_test(tc, test_d_6);
  tcase_add_test(tc, test_d_7);
  tcase_add_test(tc, test_d_8);
  tcase_add_test(tc, test_d_9);
  tcase_add_test(tc, test_d_10);
  tcase_add_test(tc, test_d_11);
  tcase_add_test(tc, test_d_12);
  tcase_add_test(tc, test_d_13);
  tcase_add_test(tc, test_d_14);
  tcase_add_test(tc, test_d_15);
  tcase_add_test(tc, test_d_16);
  tcase_add_test(tc, test_d_17);
  tcase_add_test(tc, test_d_18);
  tcase_add_test(tc, test_d_19);
  tcase_add_test(tc, test_d_20);
  tcase_add_test(tc, test_d_21);
  tcase_add_test(tc, test_d_22);
  tcase_add_test(tc, test_d_23);
  tcase_add_test(tc, test_d_24);
  tcase_add_test(tc, test_d_25);
  tcase_add_test(tc, test_d_26);
  tcase_add_test(tc, test_d_27);
  tcase_add_test(tc, test_d_28);
  tcase_add_test(tc, test_d_29);
  tcase_add_test(tc, test_d_30);
  tcase_add_test(tc, test_d_31);
  tcase_add_test(tc, test_d_32);
  tcase_add_test(tc, test_d_33);
  tcase_add_test(tc, test_d_34);
  tcase_add_test(tc, test_d_35);
  tcase_add_test(tc, test_d_36);
  tcase_add_test(tc, test_d_37);
  tcase_add_test(tc, test_d_38);
  tcase_add_test(tc, test_d_39);
  tcase_add_test(tc, test_d_40);
  tcase_add_test(tc, test_d_41);
  tcase_add_test(tc, test_d_42);
  tcase_add_test(tc, test_d_43);
  tcase_add_test(tc, test_d_44);
  tcase_add_test(tc, test_d_45);
  tcase_add_test(tc, test_d_46);
  tcase_add_test(tc, test_d_47);
  tcase_add_test(tc, test_d_48);
  tcase_add_test(tc, test_d_49);
  tcase_add_test(tc, test_d_50);
  tcase_add_test(tc, test_u_1);
  tcase_add_test(tc, test_u_2);
  tcase_add_test(tc, test_u_3);
  tcase_add_test(tc, test_u_4);
  tcase_add_test(tc, test_u_5);
  tcase_add_test(tc, test_u_6);
  tcase_add_test(tc, test_u_7);
  tcase_add_test(tc, test_u_8);
  tcase_add_test(tc, test_u_9);
  tcase_add_test(tc, test_u_10);
  tcase_add_test(tc, test_u_11);
  tcase_add_test(tc, test_u_12);
  tcase_add_test(tc, test_u_13);
  tcase_add_test(tc, test_u_14);
  tcase_add_test(tc, test_u_15);
  tcase_add_test(tc, test_u_16);
  tcase_add_test(tc, test_u_17);
  tcase_add_test(tc, test_u_18);
  tcase_add_test(tc, test_u_19);
  tcase_add_test(tc, test_u_20);
  tcase_add_test(tc, test_u_21);
  tcase_add_test(tc, test_u_22);
  tcase_add_test(tc, test_u_23);
  tcase_add_test(tc, test_ox_1);
  tcase_add_test(tc, test_ox_2);
  tcase_add_test(tc, test_ox_3);
  tcase_add_test(tc, test_ox_4);
  tcase_add_test(tc, test_ox_5);
  tcase_add_test(tc, test_ox_6);
  tcase_add_test(tc, test_ox_7);
  tcase_add_test(tc, test_ox_8);
  tcase_add_test(tc, test_ox_9);
  tcase_add_test(tc, test_ox_10);
  tcase_add_test(tc, test_ox_11);
  tcase_add_test(tc, test_ox_12);
  tcase_add_test(tc, test_ox_13);
  tcase_add_test(tc, test_ox_14);
  tcase_add_test(tc, test_ox_15);
  tcase_add_test(tc, test_ox_16);
  tcase_add_test(tc, test_ox_17);
  tcase_add_test(tc, test_ox_18);
  tcase_add_test(tc, test_ox_19);
  tcase_add_test(tc, test_ox_20);
  tcase_add_test(tc, test_ox_21);
  tcase_add_test(tc, test_ox_22);
  tcase_add_test(tc, test_ox_23);
  tcase_add_test(tc, test_ox_24);
  tcase_add_test(tc, test_ox_25);
  tcase_add_test(tc, test_ox_26);
  tcase_add_test(tc, test_ox_27);
  tcase_add_test(tc, test_ox_28);
  tcase_add_test(tc, test_ox_29);
  tcase_add_test(tc, test_ox_30);
  tcase_add_test(tc, test_ox_31);
  tcase_add_test(tc, test_ox_32);
  tcase_add_test(tc, test_ox_33);
  tcase_add_test(tc, test_ox_34);
  tcase_add_test(tc, test_ox_35);
  tcase_add_test(tc, test_ox_36);
  tcase_add_test(tc, test_ox_37);
  tcase_add_test(tc, test_ox_38);
  tcase_add_test(tc, test_ox_39);
  tcase_add_test(tc, test_ox_40);
  tcase_add_test(tc, test_ox_41);
  tcase_add_test(tc, test_ox_42);
  tcase_add_test(tc, test_ox_43);
  tcase_add_test(tc, test_ox_44);
  tcase_add_test(tc, test_ox_45);
  tcase_add_test(tc, test_ox_50);
  tcase_add_test(tc, test_ox_51);
  tcase_add_test(tc, test_ox_52);
  tcase_add_test(tc, test_ox_53);
  tcase_add_test(tc, test_ox_54);
  tcase_add_test(tc, test_ox_55);
  tcase_add_test(tc, test_ox_56);
  tcase_add_test(tc, test_ox_57);
  tcase_add_test(tc, test_ox_58);
  tcase_add_test(tc, test_ox_59);
  tcase_add_test(tc, test_ox_60);
  tcase_add_test(tc, test_c_1);
  tcase_add_test(tc, test_c_2);
  tcase_add_test(tc, test_c_3);
  tcase_add_test(tc, test_c_4);
  tcase_add_test(tc, test_c_5);
  tcase_add_test(tc, test_c_6);
  tcase_add_test(tc, test_c_7);
  tcase_add_test(tc, test_c_8);
  tcase_add_test(tc, test_c_9);
  tcase_add_test(tc, test_c_10);
  tcase_add_test(tc, test_c_11);
  tcase_add_test(tc, test_c_12);
  tcase_add_test(tc, test_c_13);
  tcase_add_test(tc, test_c_14);
  tcase_add_test(tc, test_c_15);
  tcase_add_test(tc, test_c_16);
  tcase_add_test(tc, test_s_1);
  tcase_add_test(tc, test_s_2);
  tcase_add_test(tc, test_s_3);
  tcase_add_test(tc, test_s_4);
  tcase_add_test(tc, test_s_5);
  tcase_add_test(tc, test_s_6);
  tcase_add_test(tc, test_s_7);
  tcase_add_test(tc, test_s_8);
  tcase_add_test(tc, test_s_9);
  tcase_add_test(tc, test_s_10);
  tcase_add_test(tc, test_s_11);
  tcase_add_test(tc, test_s_12);
  tcase_add_test(tc, test_s_13);
  tcase_add_test(tc, test_s_14);
  tcase_add_test(tc, test_s_15);
  tcase_add_test(tc, test_p_1);
  tcase_add_test(tc, test_p_2);
  tcase_add_test(tc, test_p_3);
  tcase_add_test(tc, test_f_1);
  tcase_add_test(tc, test_f_2);
  tcase_add_test(tc, test_f_3);
  tcase_add_test(tc, test_f_4);
  tcase_add_test(tc, test_f_5);
  tcase_add_test(tc, test_f_6);
  tcase_add_test(tc, test_f_7);
  tcase_add_test(tc, test_f_8);
  tcase_add_test(tc, test_f_9);
  tcase_add_test(tc, test_f_10);
  tcase_add_test(tc, test_f_11);
  tcase_add_test(tc, test_f_12);
  tcase_add_test(tc, test_f_14);
  tcase_add_test(tc, test_f_15);
  tcase_add_test(tc, test_f_17);
  tcase_add_test(tc, test_f_18);
  tcase_add_test(tc, test_f_19);
  tcase_add_test(tc, test_f_20);
  tcase_add_test(tc, test_f_21);
  tcase_add_test(tc, test_f_22);
  tcase_add_test(tc, test_f_23);
  tcase_add_test(tc, test_f_24);
  tcase_add_test(tc, test_f_25);
  tcase_add_test(tc, test_f_26);
  tcase_add_test(tc, test_f_27);
  tcase_add_test(tc, test_f_28);
  tcase_add_test(tc, test_f_29);
  tcase_add_test(tc, test_f_30);
  tcase_add_test(tc, test_f_31);
  tcase_add_test(tc, test_f_32);
  tcase_add_test(tc, test_f_33);
  tcase_add_test(tc, test_f_34);
  tcase_add_test(tc, test_f_35);
  tcase_add_test(tc, test_f_36);
  tcase_add_test(tc, test_f_37);
  tcase_add_test(tc, test_f_38);
  tcase_add_test(tc, test_f_39);
  tcase_add_test(tc, test_f_40);
  tcase_add_test(tc, test_f_41);
  tcase_add_test(tc, test_f_42);
  tcase_add_test(tc, test_f_43);
  tcase_add_test(tc, test_f_44);
  tcase_add_test(tc, test_f_45);
  tcase_add_test(tc, test_f_46);
  tcase_add_test(tc, test_f_47);
  tcase_add_test(tc, test_f_48);
  tcase_add_test(tc, test_f_49);
  tcase_add_test(tc, test_f_50);
  tcase_add_test(tc, test_f_51);
  tcase_add_test(tc, test_f_52);
  tcase_add_test(tc, test_f_53);
  tcase_add_test(tc, test_f_54);
  tcase_add_test(tc, test_f_55);
  tcase_add_test(tc, test_f_56);
  tcase_add_test(tc, test_f_57);
  tcase_add_test(tc, test_f_58);
  tcase_add_test(tc, test_f_59);
  tcase_add_test(tc, test_f_60);
  tcase_add_test(tc, test_f_61);
  tcase_add_test(tc, test_f_62);
  tcase_add_test(tc, test_f_63);
  tcase_add_test(tc, test_f_64);
  tcase_add_test(tc, test_f_65);
  tcase_add_test(tc, test_f_66);
  tcase_add_test(tc, test_e_1);
  tcase_add_test(tc, test_e_2);
  tcase_add_test(tc, test_e_3);
  tcase_add_test(tc, test_e_4);
  tcase_add_test(tc, test_e_5);
  tcase_add_test(tc, test_e_6);
  tcase_add_test(tc, test_e_7);
  tcase_add_test(tc, test_e_8);
  tcase_add_test(tc, test_e_9);
  tcase_add_test(tc, test_e_10);
  tcase_add_test(tc, test_e_11);
  tcase_add_test(tc, test_e_12);
  tcase_add_test(tc, test_e_13);
  tcase_add_test(tc, test_e_14);
  tcase_add_test(tc, test_e_15);
  tcase_add_test(tc, test_e_16);
  tcase_add_test(tc, test_e_17);
  tcase_add_test(tc, test_e_18);
  tcase_add_test(tc, test_e_19);
  tcase_add_test(tc, test_e_20);
  tcase_add_test(tc, test_e_22);
  tcase_add_test(tc, test_e_23);
  tcase_add_test(tc, test_e_24);
  tcase_add_test(tc, test_e_25);
  tcase_add_test(tc, test_e_26);
  tcase_add_test(tc, test_e_27);
  tcase_add_test(tc, test_e_28);
  tcase_add_test(tc, test_e_29);
  tcase_add_test(tc, test_e_30);
  tcase_add_test(tc, test_e_31);
  tcase_add_test(tc, test_e_32);
  tcase_add_test(tc, test_e_33);
  tcase_add_test(tc, test_e_34);
  tcase_add_test(tc, test_e_35);
  tcase_add_test(tc, test_e_36);
  tcase_add_test(tc, test_e_37);
  tcase_add_test(tc, test_e_38);
  tcase_add_test(tc, test_e_39);
  tcase_add_test(tc, test_e_40);
  tcase_add_test(tc, test_e_41);
  tcase_add_test(tc, test_e_42);
  tcase_add_test(tc, test_e_43);
  tcase_add_test(tc, test_e_44);
  tcase_add_test(tc, test_e_45);
  tcase_add_test(tc, test_e_46);
  tcase_add_test(tc, test_e_47);
  tcase_add_test(tc, test_e_48);
  tcase_add_test(tc, test_e_49);
  tcase_add_test(tc, test_e_50);
  tcase_add_test(tc, test_e_51);
  tcase_add_test(tc, test_mix_1);
  tcase_add_test(tc, test_mix_2);
  tcase_add_test(tc, test_mix_3);
  tcase_add_test(tc, test_mix_4);
  tcase_add_test(tc, test_mix_6);
  tcase_add_test(tc, test_mix_7);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_g_1);
  tcase_add_test(tc, test_g_2);
  tcase_add_test(tc, test_g_3);
  tcase_add_test(tc, test_g_4);
  tcase_add_test(tc, test_g_7);
  tcase_add_test(tc, test_g_8);
  tcase_add_test(tc, test_g_9);
  tcase_add_test(tc, test_g_10);
  tcase_add_test(tc, test_g_11);
  tcase_add_test(tc, test_g_12);
  tcase_add_test(tc, test_g_13);
  tcase_add_test(tc, test_g_14);
  tcase_add_test(tc, test_g_15);
  tcase_add_test(tc, test_g_16);
  suite_add_tcase(s, tc);

  tc_memcpy = tcase_create("s21_memcpy");
  tcase_add_test(tc_memcpy, s21_memcpy_normal);
  tcase_add_test(tc_memcpy, s21_memcpy_out);
  tcase_add_test(tc_memcpy, s21_memcpy_empty_dest);
  tcase_add_test(tc_memcpy, s21_memcpy_empty_src);
  suite_add_tcase(s, tc_memcpy);

  tc_strncpy = tcase_create("s21_strncpy");
  tcase_add_test(tc_strncpy, s21_strncpy_normal);
  tcase_add_test(tc_strncpy, s21_strncpy_out);
  suite_add_tcase(s, tc_strncpy);

  tc_strtok = tcase_create("s21_strtok");
  tcase_add_test(tc_strtok, s21_strtok_normal);
  tcase_add_test(tc_strtok, s21_strtok_no_delimetr);
  tcase_add_test(tc_strtok, s21_strtok_empty);
  suite_add_tcase(s, tc_strtok);

  tc_strpbrk = tcase_create("s21_strpbrk");
  tcase_add_test(tc_strpbrk, s21_strpbrk_normal);
  tcase_add_test(tc_strpbrk, s21_strpbrk_no_symb);
  tcase_add_test(tc_strpbrk, s21_strpbrk_empty_symb);
  tcase_add_test(tc_strpbrk, s21_strpbrk_empty_str);
  suite_add_tcase(s, tc_strpbrk);

  tc_memset = tcase_create("s21_memset");
  tcase_add_test(tc_memset, s21_memset_normal);
  tcase_add_test(tc_memset, s21_memset_null);
  tcase_add_test(tc_memset, s21_memset_sign);
  suite_add_tcase(s, tc_memset);

  tc_strerror = tcase_create("s21_strerror");
  tcase_add_test(tc_strerror, s21_strerror_normal);
  tcase_add_test(tc_strerror, s21_strerror_unknown);
  tcase_add_test(tc_strerror, s21_strerror_unknown_2);
  tcase_add_test(tc_strerror, s21_strerror_0);
  suite_add_tcase(s, tc_strerror);

  tc_strlen = tcase_create("s21_strlen");
  tcase_add_test(tc_strlen, s21_strlen_normal);
  tcase_add_test(tc_strlen, s21_strlen_empty);
  suite_add_tcase(s, tc_strlen);

  tc_strstr = tcase_create("s21_strstr");
  tcase_add_test(tc_strstr, s21_strstr_normal);
  tcase_add_test(tc_strstr, s21_strstr_SF);
  tcase_add_test(tc_strstr, s21_strstr_empty);
  tcase_add_test(tc_strstr, s21_strstr_all_empty);
  suite_add_tcase(s, tc_strstr);

  tc_strncmp = tcase_create("s21_strncmp");
  tcase_add_test(tc_strncmp, s21_strncmp_all_empty);
  tcase_add_test(tc_strncmp, s21_strncmp_start_empty);
  tcase_add_test(tc_strncmp, s21_strncmp_start_dif_minus);
  tcase_add_test(tc_strncmp, s21_strncmp_start_dif_plus);
  tcase_add_test(tc_strncmp, s21_strncmp_mid_dif);
  tcase_add_test(tc_strncmp, s21_strncmp_equal);
  tcase_add_test(tc_strncmp, s21_strncmp_equal_mid);
  tcase_add_test(tc_strncmp, s21_strncmp_zero_n);
  suite_add_tcase(s, tc_strncmp);

  tc_memcmp = tcase_create("s21_memcmp");
  tcase_add_test(tc_memcmp, s21_memcmp_normal_equal);
  tcase_add_test(tc_memcmp, s21_memcmp_normal_minus);
  tcase_add_test(tc_memcmp, s21_memcmp_normal_plus);
  tcase_add_test(tc_memcmp, s21_memcmp_zero_n);
  tcase_add_test(tc_memcmp, s21_memcmp_all_empty);
  tcase_add_test(tc_memcmp, s21_memcmp_empty_str);
  tcase_add_test(tc_memcmp, s21_memcmp_empty_substr);
  suite_add_tcase(s, tc_memcmp);

  tc_memchr = tcase_create("s21_memchr");
  tcase_add_test(tc_memchr, s21_memchr_normal);
  tcase_add_test(tc_memchr, s21_memchr_empty_str);
  tcase_add_test(tc_memchr, s21_memchr_empty_sym);
  tcase_add_test(tc_memchr, s21_memchr_n_zero);
  tcase_add_test(tc_memchr, s21_memchr_empty_str_sym);
  suite_add_tcase(s, tc_memchr);

  tc_strncat = tcase_create("s21_strncat");
  tcase_add_test(tc_strncat, s21_strncat_normal);
  tcase_add_test(tc_strncat, s21_strncat_first_str_empty);
  tcase_add_test(tc_strncat, s21_strncat_second_str_empty);
  tcase_add_test(tc_strncat, s21_strncat_both_str_empty);
  tcase_add_test(tc_strncat, s21_strncat_size_empty);
  tcase_add_test(tc_strncat, s21_strncat_size_zero);
  tcase_add_test(tc_strncat, s21_strncat_all_empty);
  suite_add_tcase(s, tc_strncat);

  tc_strcat = tcase_create("s21_strcat");
  tcase_add_test(tc_strncat, s21_strcat_test_1);
  suite_add_tcase(s, tc_strcat);

  tc_strchr = tcase_create("s21_strchr");
  tcase_add_test(tc_strchr, s21_strchr_normal);
  tcase_add_test(tc_strchr, s21_strchr_empty_str);
  tcase_add_test(tc_strchr, s21_strchr_empty_sym);
  tcase_add_test(tc_strchr, s21_strchr_both_empty);
  suite_add_tcase(s, tc_strchr);

  tc_strcspn = tcase_create("s21_strcspn");
  tcase_add_test(tc_strcspn, s21_strcspn_normal);
  tcase_add_test(tc_strcspn, s21_strcspn_empty_str);
  tcase_add_test(tc_strcspn, s21_strcspn_empty_key);
  tcase_add_test(tc_strcspn, s21_strcspn_both_key);
  suite_add_tcase(s, tc_strcspn);

  tc_strrchr = tcase_create("s21_strrchr");
  tcase_add_test(tc_strrchr, s21_strrchr_normal);
  tcase_add_test(tc_strrchr, s21_strrchr_empty_str);
  tcase_add_test(tc_strrchr, s21_strrchr_empty_sym);
  tcase_add_test(tc_strrchr, s21_strrchr_both_empty);
  suite_add_tcase(s, tc_strrchr);

  tc_strspn = tcase_create("s21_strspn");
  tcase_add_test(tc_strspn, s21_strspn_normal);
  tcase_add_test(tc_strspn, s21_strspn_normal_2);
  tcase_add_test(tc_strspn, s21_strspn_first_str_empty);
  tcase_add_test(tc_strspn, s21_strspn_second_str_empty);
  tcase_add_test(tc_strspn, s21_strspn_str2_not_in_str1);
  tcase_add_test(tc_strspn, s21_strspn_both_empty);
  suite_add_tcase(s, tc_strspn);

  tc_to_lower = tcase_create("s21_to_lower");
  tcase_add_test(tc_to_lower, s21_to_lower_normal);
  tcase_add_test(tc_to_lower, s21_to_lower_sign);
  tcase_add_test(tc_to_lower, s21_to_lower_with_lower);
  suite_add_tcase(s, tc_to_lower);

  tc_trim = tcase_create("s21_trim");
  tcase_add_test(tc_trim, s21_trim_normal);
  tcase_add_test(tc_trim, s21_trim_sides);
  tcase_add_test(tc_trim, s21_trim_empty);
  suite_add_tcase(s, tc_trim);

  tc_to_upper = tcase_create("s21_to_upper");
  tcase_add_test(tc_to_upper, s21_to_upper_normal);
  tcase_add_test(tc_to_upper, s21_to_upper_whith_sign);
  tcase_add_test(tc_to_upper, s21_to_upper_whith_upper);
  suite_add_tcase(s, tc_to_upper);

  tc_insert = tcase_create("s21_insert");
  tcase_add_test(tc_insert, s21_insert_normal);
  tcase_add_test(tc_insert, s21_insert_invalid_index);
  suite_add_tcase(s, tc_insert);

  tc_sprintf = tcase_create("s21_sprintf");
  tcase_add_test(tc_sprintf, s21_sprintf_d);
  tcase_add_test(tc_sprintf, s21_sprintf_u);
  tcase_add_test(tc_sprintf, s21_sprintf_x);
  tcase_add_test(tc_sprintf, s21_sprintf_g);
  tcase_add_test(tc_sprintf, s21_sprintf_p);
  tcase_add_test(tc_sprintf, s21_sprintf_o);
  tcase_add_test(tc_sprintf, s21_sprintf_on);
  tcase_add_test(tc_sprintf, s21_sprintf_x);
  tcase_add_test(tc_sprintf, s21_sprintf_e);
  tcase_add_test(tc_sprintf, s21_sprintf_E);
  tcase_add_test(tc_sprintf, s21_sprintf_c);
  tcase_add_test(tc_sprintf, s21_sprintf_f);
  tcase_add_test(tc_sprintf, s21_sprintf_i);
  tcase_add_test(tc_sprintf, s21_sprintf_s);
  tcase_add_test(tc_sprintf, s21_sprintf_h);
  tcase_add_test(tc_sprintf, s21_sprintf_l);
  tcase_add_test(tc_sprintf, s21_sprintf_empty);
  tcase_add_test(tc_sprintf, s21_sprintf_nan_inf);

  suite_add_tcase(s, tc_sprintf);

  tc_sscanf = tcase_create("s21_sscanf");
  tcase_add_test(tc_sscanf, s21_sscanf_c);
  tcase_add_test(tc_sscanf, s21_sscanf_cw3);
  tcase_add_test(tc_sscanf, s21_sscanf_d);
  tcase_add_test(tc_sscanf, s21_sscanf_p);
  tcase_add_test(tc_sscanf, s21_sscanf_o);
  tcase_add_test(tc_sscanf, s21_sscanf_f);
  tcase_add_test(tc_sscanf, s21_sscanf_x);
  tcase_add_test(tc_sscanf, s21_sscanf_h);
  tcase_add_test(tc_sscanf, s21_sscanf_fg);
  tcase_add_test(tc_sscanf, s21_sscanf_fg2);
  tcase_add_test(tc_sscanf, s21_sscanf_empty);
  tcase_add_test(tc_sscanf, s21_sscanf_t);
  tcase_add_test(tc_sscanf, s21_sscanf_l);
  tcase_add_test(tc_sscanf, s21_sscanf_skip_x_variation1);
  tcase_add_test(tc_sscanf, s21_sscanf_skip_x_variation2);
  tcase_add_test(tc_sscanf, s21_sscanf_skip_x_variation3);
  tcase_add_test(tc_sscanf, s21_sscanf_skip_x_variation4);
  tcase_add_test(tc_sscanf, s21_sscanf_skip_x_variation5);
  tcase_add_test(tc_sscanf, s21_sscanf_s);
  tcase_add_test(tc_sscanf, s21_sscanf_0x);
  tcase_add_test(tc_sscanf, s21_sscanf_0);
  tcase_add_test(tc_sscanf, s21_sscanf_inf);
  tcase_add_test(tc_sscanf, s21_sscanf_nan);
  tcase_add_test(tc_sscanf, s21_sscanf_u);
  tcase_add_test(tc_sscanf, s21_sscanf_fexp);
  tcase_add_test(tc_sscanf, s21_sscanf_f_n);
  tcase_add_test(tc_sscanf, s21_sscanf_f_n_2);
  tcase_add_test(tc_sscanf, s21_sscanf_fexp_l);
  tcase_add_test(tc_sscanf, s21_sscanf_d_width);
  tcase_add_test(tc_sscanf, s21_sscanf_d_n);
  tcase_add_test(tc_sscanf, s21_sscanf_x_X);

  suite_add_tcase(s, tc_sscanf);

  return s;
}

int main() {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = s21_string_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
