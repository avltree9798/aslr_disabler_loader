#include<stdio.h>
#include<stdlib.h>
#include<spawn.h>
#include<string.h>

// https://opensource.apple.com/source/lldb/lldb-76/tools/darwin-debug/darwin-debug.cpp.auto.html
#ifndef _POSIX_SPAWN_DISABLE_ASLR
#define _POSIX_SPAWN_DISABLE_ASLR       0x0100
#endif

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stdout, "Usage: %s /path/to/binary [arg1] [arg2]\n", argv[0]);
        exit(1);
    }
    char* new_argv[] = {"/bin/sh", "-c", argv[1], NULL};
    pid_t pid;
    posix_spawnattr_t spawn_attrs;
    posix_spawnattr_init(&spawn_attrs);
    posix_spawnattr_setflags(&spawn_attrs, _POSIX_SPAWN_DISABLE_ASLR);
    int status;
    status = posix_spawnp(&pid, "/bin/sh", NULL, &spawn_attrs, new_argv, NULL);
    if(status != 0) {
        fprintf(stderr, "[-] Error on posix_spawn: %s\n", strerror(status));
        exit(1);
    }
    fprintf(stdout, "[+] Process launched without ASLR\n");
    return 0;
}