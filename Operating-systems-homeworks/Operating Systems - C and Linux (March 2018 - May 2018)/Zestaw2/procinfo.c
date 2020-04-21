#include <stdio.h>      /* funkcja printf */
#include <sys/types.h>  /* biblioteka używana przez wszystkie funkcje getuid itd. */
#include <unistd.h>     /* biblioteka używana przez wszystkie funkcje getuid itd. */
#include "procinfo.h"

/*implementacja funkcji procinfo */
int procinfo(const char* name) {
    printf("Name: %s UID: %d GID: %d PID: %d PPID: %d i PGID: %d\n", name, (int)getuid(), (int)getgid(), (int)getpid(), (int)getppid(), (int)getpgrp());
    return 0;
}
