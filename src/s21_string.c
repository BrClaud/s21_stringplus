#include "s21_string.h"

/*Функции Дани*/

// копирование в сроку dest n байт из строки str
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = dest;  // нужно для изменения ячейки памяти
  const char *s = src;  // наш указатель на ячейку в памяти изначальной сроки
  while (n--)
    *d++ = *s++;  // присваивание изменяемой ячейки памяти значения копируемой
                  // строки
  return dest;
}

// заполнение перввых n элементов строки заданным значением
void *s21_memset(void *dest, s21_size_t ch, s21_size_t n) {
  unsigned char *ptr = dest;  // указатель на ячейку памяти
  while (n-- > 0)  // цекл до тех пор пока не закончится заявленная длина
    *ptr++ = ch;  // присваивание ячейки памяти нужного нам значения
  return dest;
}

// копирование в конец строки dst n символов из строки str
char *s21_strncat(char *dst, const char *src, s21_size_t n) {
  if (n != 0) {
    char *d = dst;  // указатель на элемент результирующей строки куда мы пишем
    const char *s = src;  // указатель на элемент в копируемой строке
    while (*d != 0)
      d++;  // перевод указателя в конец, можно заменить на d +=
            // s21_strlen(dst);
    while (n != 0) {
      if ((*d = *s++) == 0) {  // присваивание + проверка на ошиюку присваивания
                               // в случае ошибки заполняем все нулями
        while (--n != 0) *d++ = 0;
        break;
      }
      d++;
      n--;
    }
    *d = 0;  // завершение строки нулем
  }
  return (dst);
}

// копирование в начало строки dst n символов из строки str
char *s21_strncpy(char *dst, const char *src, s21_size_t n) {
  if (n != 0) {
    char *d = dst;  // указатель на элемент результирующей строки куда мы пишем
    const char *s = src;  // указатель на элемент в копируемой строке

    while (n != 0) {
      if ((*d++ = *s++) == 0) {
        // в случае ошибки заполняем все нулями
        while (--n != 0) *d++ = 0;
        break;
      }
      n--;
    }
  }
  return (dst);
}

static char *olds;

char *s21_strtok(char *s, const char *delim) {
  char *token = s21_NULL;
  // проверка на первое или последущие разделения
  if (s == s21_NULL) s = olds;
  if (s != s21_NULL) {
    // пропуск ведущих разделителей
    while (s21_strpbrk(s, delim) - s == 0) {
      s++;
    }
    // в случае когда строка закончена возвращаем нул
    if (*s == '\0') {
      olds = s;
      return s21_NULL;
    }
    /* поиск места где заканчивается строка до разделителя */
    token = s;
    s = s21_strpbrk(token, delim);  // TODO заменить на s21_strprbk
    if (s == s21_NULL) /* это последний кусочек текста  */
      olds = s21_strpbrk(token, "\0");
    else {
      /*  завершаем кусочек текста и записываем остаток в olds  */
      *s = '\0';
      olds = s + 1;
    }
  }
  return token;
}

//функция для спринтфа для флота
/*Функция strcat добавляет в строку, на которую указывает аргумент dest, строку,
на которую указывает аргумент src. Символ конца строки помещается в конце
объединенных строк.*/
char *s21_strcat(char *dest, const char *src) {
  char *a = dest;
  while (*a) a++;
  while ((*a++ = *src++)) continue;
  return dest;
}

/*Функции Ксюши*/

/*Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
 * байтах строки, на которую указывает аргумент str.*/
void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = s21_NULL;
  unsigned char *buffer = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (buffer[i] == c) {
      res = &buffer[i];
      break;
    }
  }
  return res;
}

/*Сравнивает первые n байтов str1 и str2.*/
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  char *buffer_1 = (char *)str1;
  char *buffer_2 = (char *)str2;
  int res = 0;
  for (s21_size_t i = 0; i < n && !res; i++) {
    res = *(buffer_1 + i) - *(buffer_2 + i);
  }
  return res;
}

/*Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
 * которую указывает аргумент str.*/
char *s21_strchr(const char *str, int c) {
  while (*str != c && *str) str++;
  return *str == c ? (char *)str : s21_NULL;
}

/*Сравнивает не более первых n байтов str1 и str2.*/
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int flag = 0;
  int result = 0;
  if (n == 0) {
    flag = 1;
    result = 0;
  }
  if (!flag) {
    s21_size_t i = 0;
    while (*(str1 + i) && *(str2 + i) && i < n - 1 &&
           *(str1 + i) == *(str2 + i))
      i++;
    if (*(str1 + i) != *(str2 + i))
      result = *(unsigned char *)(str1 + i) - *(unsigned char *)(str2 + i);
  }
  return result;
}

/*Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов, не входящих в str2..*/
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t index = 0;
  for (s21_size_t i = 0; *(str1 + i) != '\0'; i++, ++index) {
    if (s21_strchr(str2, str1[i]) != s21_NULL) {
      break;
    }
  }
  return index;
}

/*Для sscanf: определяет наибольшую длину начального участка строки, на которую
 * указывает аргумент str, содержащего только символы строки, на которую
 * указывает аргумент sym.*/
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  if ((str1 != s21_NULL) && (str2 != s21_NULL)) {
    while (*str1 != '\0') {
      if (s21_strchr(str2, *str1) == s21_NULL) {
        break;
      } else {
        str1++;
        len++;
      }
    }
  }
  return len;
}

/*Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
 * которую указывает аргумент str. */
char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  do {
    if (*str == c) result = (char *)str;
  } while (*str++);

  return result;
}

//функции Шушаны

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  for (; str[length]; length++) {
  }
  return length;
}

/* Находит первый символ в строке str1, который
 соответствует любому символу, указанному в str2.*/
char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t str_len = s21_strlen(str1);
  s21_size_t shift = 0;
  int symbol_founded = 0;

  for (shift = 0; symbol_founded == 0 && shift < str_len; shift += 1) {
    if (s21_strchr(str2, str1[shift])) symbol_founded = 1;
  }

  return (char *)(symbol_founded ? (str1 + shift - 1) : s21_NULL);
}

/*Функция strstr ищет первое вхождение строки (за исключением
 признак конца строки), на которую указывает аргумент haystack, в строку
, на которую указывает аргумент needle. Если строка haystack имеет нулевую
длину, то функция вернет указатель на начало строки needle.
 вхождение haystack в needle*/
char *s21_strstr(const char *haystack, const char *needle) {
  const char *buf;
  int flag = 0;

  if (haystack == s21_NULL || needle == s21_NULL) {
    buf = s21_NULL;
  } else {
    int len = 0;
    while (*(needle + len)) len++;

    if (len == 0) {
      buf = haystack;
      flag = 1;
    } else {
      while (*haystack) {
        if (*haystack == *needle) {
          int j = 0;
          while (*haystack == *(needle + j) && *(needle + j) != '\0') {
            j++;
            haystack++;
          }
          if (j == len) {
            flag = 1;
            haystack = haystack - len;
            break;
          }
        } else {
          haystack++;
        }
      }
      buf = haystack;
    }
  }

  if (!flag) buf = s21_NULL;

  return (char *)buf;
}

/*Возвращает новую строку, в которой указанная строка (str) вставлена в
указанную позицию (start_index) в данной строке (src). В случае какой-либо
ошибки следует вернуть значение NULL*/
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = (char *)s21_NULL;
  s21_size_t src_length = (src == NULL) ? 0 : s21_strlen(src);
  s21_size_t str_length = (str == NULL) ? 0 : s21_strlen(str);
  s21_size_t res_length = src_length + str_length;

  if (src != s21_NULL &&
      start_index <= src_length) {  // если строка непустая и ее длина больше
                                    // стартового индекса
    new_str = calloc(res_length + 1, sizeof(char));  // пробуем выделить память
    if (new_str != s21_NULL) {
      if (str == s21_NULL)
        s21_strncpy(new_str, src, src_length);
      else {
        // Копируем часть src до start_index в new_str
        s21_strncpy(new_str, src, start_index);
        // Перемещаем указатель new_str на конец скопированной части
        new_str = new_str + start_index;
        // Перемещаем указатель src на символ после start_index
        src = src + start_index;
        // Копируем строку str в new_str
        s21_strncpy(new_str, str, str_length);
        // Перемещаем указатель new_str на  конец вставленной строки
        new_str = new_str + str_length;
        // Копируем оставшуюся часть строки src в new_str
        s21_strncpy(new_str, src, src_length - start_index);
        new_str = new_str - str_length - start_index;
        // Возвращаем указатель new_str на начало выделенной области памяти
      }
    }
  }
  return new_str;
}

/*Возвращает новую строку, в которой удаляются все начальные и конечные
вхождения набора заданных символов (trim_chars) из данной строки (src).
В случае какой-либо ошибки следует вернуть значение NULL*/
void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = s21_NULL;
  if (src) {
    // Если символы для обрезки не заданы, используем символы по умолчанию
    if (!trim_chars || !(*trim_chars)) {
      trim_chars = " \n\t\r\x0B\f";
    }
    //Задаем адрес начала и конца в переменные
    s21_size_t src_len = s21_strlen(src);
    const char *start = src;
    const char *end = src + src_len - 1;
    // Обрезаем символы обрезки в начале строки до тех пор пока есть вхождения
    while (*start && s21_strchr(trim_chars, *start)) {
      start++;
    }
    // Обрезаем символы обрезки в конце строки до тех пор пока есть вхождения
    while (end > start && s21_strchr(trim_chars, *end)) {
      end--;
    }
    /*С помощью memcpy копируем с нового старта в new_str
    нужное количество символов для копирования считаем в trimmed_len*/
    s21_size_t trimmed_len = end - start + 1;
    new_str = (char *)calloc(trimmed_len + 1, sizeof(char));
    if (new_str) {
      s21_memcpy(new_str, start, trimmed_len);
    }
  }
  return new_str;
}

/*Возвращает копию строки (str), преобразованной в верхний регистр.
 В случае какой-либо ошибки следует вернуть значение NULL*/
//Если обрабатываемый символ – буква в нижнем регистре, то -32
void *s21_to_upper(const char *str) {
  char *new_str = s21_NULL;
  if (str) {
    s21_size_t str_len = s21_strlen(str);
    new_str = calloc(str_len + 1, sizeof(char));
    if (new_str) {
      for (s21_size_t i = 0; i < str_len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          new_str[i] = str[i] - 32;
        } else {
          new_str[i] = str[i];
        }
      }
    }
  }
  return new_str;
}

/*Возвращает копию строки (str), преобразованной в нижний регистр.
 В случае какой-либо ошибки следует вернуть значение NULL*/
//Если обрабатываемый символ – буква в верхнем регистре, то +32
void *s21_to_lower(const char *str) {
  char *new_str = s21_NULL;
  if (str) {
    s21_size_t str_len = s21_strlen(str);
    new_str = calloc(str_len + 1, sizeof(char));
    if (new_str) {
      for (s21_size_t i = 0; i < str_len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          new_str[i] = str[i] + 32;
        } else {
          new_str[i] = str[i];
        }
      }
    }
  }
  return new_str;
}
