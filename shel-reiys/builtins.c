#include "shell.h"

int builtin_cd(char **args) {
    if (strcmp(args[0], "cd") != 0) return -1;

    if (args[1] == NULL) {
        chdir(getenv("HOME"));
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
    return 0;
}

int builtin_pwd(char **args) {
    if (strcmp(args[0], "pwd") != 0) return -1;

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
    return 0;
}

int builtin_echo(char **args) {
    if (strcmp(args[0], "echo") != 0) return -1;

    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 0;
}

int builtin_clear(char **args) {
    if (strcmp(args[0], "clear") != 0) return -1;

    printf("\033[2J\033[H");
    return 0;
}