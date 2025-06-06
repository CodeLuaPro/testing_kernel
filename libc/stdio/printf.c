#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd') {
			format++;
			int num = va_arg(parameters, int);
			int numCopy = num;
			int numDigits = 0;
			while (num > 0) {
				numDigits++;
				num /= 10;
			}

			int counter = 0;
			num = numCopy;
			char digitStr[numDigits];

			while (num > 0) {
				int ascii = 0;
				int digit = num % 10;
				switch(digit) {
					case 0:
						ascii = 48;
						break;
					case 1:
						ascii = 49;
						break;
					case 2:
						ascii = 50;
						break;
					case 3:
						ascii = 51;
						break;
					case 4:
						ascii = 52;
						break;
					case 5:
						ascii = 53;
						break;
					case 6:
						ascii = 54;
						break;
					case 7:
						ascii = 55;
						break;
					case 8:
						ascii = 56;
						break;
					case 9:
						ascii = 57;
						break;
				}
				digitStr[counter] = (char)ascii;
				num /= 10;
			}

			if (!print(digitStr, sizeof(digitStr))) {
				return -1;
			}
			written += strlen(digitStr);

		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
