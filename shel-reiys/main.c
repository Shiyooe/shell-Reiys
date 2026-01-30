#include "shell.h"

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

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "exit") == 0) {
            printf("Leaving the celestial realm...\n");
            break;
        }
        if (builtin_cd(args) == 0) continue;
        if (builtin_pwd(args) == 0) continue;
        if (builtin_echo(args) == 0) continue;
        if (builtin_clear(args) == 0) continue;

       
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
