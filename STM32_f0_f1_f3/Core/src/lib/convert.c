/*
 * convert.c
 *
 *  Created on: 12 июл. 2023 г.
 *      Author: r.sibgatullin
 */
#include "convert.h"
#include <stdlib.h>
#include <ctype.h>

void Uint_to_str_convert(uint32_t value, char *str, uint8_t radix) {
	utoa(value, str, radix);
}
//-------------------------------------------------------
void Int_to_str_convert(int32_t value, char str[], uint8_t radix) {
	itoa(value, str, radix);
}

int str_to_uint_convert(char *s)
{
    int i, n;
    n = 0;
    for (i = 0; isdigit(s[i]); ++i){
        n = 10 * n + (s[i] - '0');
    }
    return n;
}
