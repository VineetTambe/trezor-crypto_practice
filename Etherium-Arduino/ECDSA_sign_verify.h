#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ecdsa.h"

uint8_t hex_to_dec(uint8_t);
void hex_string_to_byte_array(const char *, uint32_t , uint8_t *);
void gen_pub_sig();
