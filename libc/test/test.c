#include <test/test.h>
#include <string.h>

void cpy(char* str) {
    char buffer[16];
    memcpy(buffer, str, strlen(str));
}