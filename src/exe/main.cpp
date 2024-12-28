#include <stdio.h>
#include <stdlib.h>
#include <shared_lib_api.h>

void exe_say(const char* what)
{
    shared_library_say(what);
    printf("%s: %s\n", __FUNCTION__, what);
}

int main(int argc, char** argv)
{
    exe_say("Hello World!\n");
    return 0;
}