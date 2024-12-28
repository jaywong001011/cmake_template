#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "static_lib_api.h"

void static_library_say(const char* what)
{
    printf("%s: %s\n", __FUNCTION__, what);
}