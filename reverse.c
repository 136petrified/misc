#include <string.h>

#include "reverse.h"

char* reverse(char *dest, const char *src) {
    int len = strlen(src);

    for (int i = len - 1; i >= 0; --i) {
        dest[len - 1 - i] = src[i];
    }

    dest[len] = '\0';

    return dest;
}