#include "shell.h"

void print_prompt(void) {
    char cwd[1024];
    char hostname[256];
    char *username = getenv("USER");

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        strcpy(cwd, "?");
    }
    gethostname(hostname, sizeof(hostname));

    // Ambil hanya nama folder terakhir
    char *last_dir = strrchr(cwd, '/');
    if (last_dir == NULL || *(last_dir + 1) == '\0') {
        last_dir = cwd;
    } else {
        last_dir++;
    }

    // Prompt aesthetic ala ricer
    printf("\033[1;34m%s@%s\033[0m ", username ? username : "guest", hostname);
    printf("\033[1;36m%s\033[0m ", last_dir);
    printf("\033[1;35m🌌 reiys > \033[0m");
    fflush(stdout);
}