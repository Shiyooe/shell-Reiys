#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>


#define MAX_INPUT 1024
#define MAX_ARGS 64

void print_prompt() {
    printf("\033[1;35mreiys🌌 > \033[0m");
    fflush(stdout);
}
void print_banner() {
    printf("\033[1;36m");
    printf("  ██████╗ ███████╗██╗██╗   ██╗███████╗\n");
    printf("  ██╔══██╗██╔════╝██║╚██╗ ██╔╝██╔════╝\n");
    printf("  ██████╔╝█████╗  ██║ ╚████╔╝ ███████╗\n");
    printf("  ██╔══██╗██╔══╝  ██║  ╚██╔╝  ╚════██║\n");
    printf("  ██║  ██║███████╗██║   ██║   ███████║\n");
    printf("  ╚═╝  ╚═╝╚══════╝╚═╝   ╚═╝   ╚══════╝\n");
    printf("\033[0m\n");

    printf("  \033[1;35mShell\033[0m   : shel-reiys\n");
    printf("  \033[1;35mMode\033[0m    : Celestial\n");
    printf("  \033[1;35mAuthor\033[0m  : Akrom\n");
    printf("  \033[1;35mDistro\033[0m  : Arch Linux\n");
    printf("  \033[1;35mStatus\033[0m  : Online 🌌\n\n");
}
void print_sysinfo() {
    struct utsname sys;
    struct sysinfo info;

    uname(&sys);
    sysinfo(&info);

    printf("  \033[1;35mkernel\033[0m : %s\n", sys.release);
    printf("  \033[1;35muptime\033[0m : %ld mins\n", info.uptime / 60);
    printf("  \033[1;35mmem\033[0m    : %ld MB free\n",
           info.freeram / 1024 / 1024);
    printf("  \033[1;35mshell\033[0m  : shel-reiys\n\n");
}

int main() {
    print_banner();
    print_sysinfo();
    
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {
        print_prompt();

        if (!fgets(input, MAX_INPUT, stdin)) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;

        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            printf("Leaving the celestial realm...\n");
            break;
        }

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("reiys");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}
