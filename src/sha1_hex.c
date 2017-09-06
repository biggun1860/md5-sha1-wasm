#include <stddef.h>
#include "sha1.h"
#include "sha1_hex.h"
#include "to_hex.h"
#include <emscripten.h>
#include <string.h>
#include <stdio.h>

SHA1_CTX g_shactx;
char g_shabuf[SHA1_HEX_LENGTH + 1] = { 0 };

void EMSCRIPTEN_KEEPALIVE sha1_init()
{
    SHA1Init(&g_shactx);
}

void EMSCRIPTEN_KEEPALIVE sha1_update(const char *data)
{
    size_t len = strlen(data);
    SHA1Update(&g_shactx, (const unsigned char *)data, len);
}

char* EMSCRIPTEN_KEEPALIVE sha1_final()
{
    unsigned char sha1[SHA1_LENGTH];
    SHA1Final(sha1, &g_shactx);
    
    to_hex(sha1, SHA1_LENGTH, g_shabuf);
    return g_shabuf;
}