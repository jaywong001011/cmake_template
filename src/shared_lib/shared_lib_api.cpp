#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <static_lib_api.h>
#include "shared_lib_api.h"

void shared_library_say(const char* what)
{
    static_library_say(what);
    printf("%s: %s\n", __FUNCTION__, what);
}