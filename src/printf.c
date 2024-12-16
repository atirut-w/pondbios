#include <stdarg.h>
#include <stdio.h>

int putint(int n) {
  int ret = 0;
  if (n < 0) {
    putchar('-');
    n = -n;
    ret++;
  }

  if (n >= 10) {
    ret += putint(n / 10);
  }

  putchar('0' + n % 10);
  return ret + 1;
}

int puthex(unsigned int n, const char *lookup) {
  int ret = 0;
  if (n >= 16) {
    ret += puthex(n / 16, lookup);
  }

  putchar(lookup[n % 16]);
  return ret + 1;
}

int printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int ret = 0;

  while (*format) {
    if (*format == '%') {
      format++;

      switch (*format) {
      case 's': {
        const char *s = va_arg(args, const char *);
        while (*s) {
          putchar(*s);
          s++;
          ret++;
        }
        break;
      }
      case 'd': {
        int n = va_arg(args, int);
        ret += putint(n);
        break;
      }
      case 'x':
      case 'X': {
        int n = va_arg(args, int);
        ret += puthex(n, *format == 'x' ? "0123456789abcdef" : "0123456789ABCDEF");
        break;
      }
      }

      format++;
    } else {
      putchar(*format);
      format++;
      ret++;
    }
  }

  va_end(args);
  return ret;
}
