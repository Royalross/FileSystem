
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileSystem.h"
#include "utility.h"
#include "commands.h"

/* Function to initialize the file system */
FileSystem* initialize_file_system() {
    FileSystem* fs = (FileSystem*)malloc(sizeof(FileSystem));
    fs->root = create_node("Root", 0, NULL);
    fs->current = fs->root;
    return fs;
}


/* Function to check for duplicate names in the current directory */
int has_duplicate_name(Node *current, const char *name) {
    int i;
    for (i = 0; i < current->child_count; i++) {
        if (strcmp(current->children[i]->name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Function to create files in the root directory based on a given list of file names */
void create_files_from_list(FileSystem *fs, const char *file_list) {
    char name[MAX_NAME_LENGTH];
    const char *ptr = file_list;
    
    while (*ptr != '\0') {
        int len = 0;
        while (*ptr != ',' && *ptr != '\0') {
            name[len++] = *ptr++;
        }
        name[len] = '\0';
        if (!has_duplicate_name(fs->root, name)) {
            Node *file = create_node(name, 1, fs->root);
            strcpy(file->content, "Dummy content");
            add_child(fs->root, file);
            printf("Created file: %s\n", file->name);
        }
        if (*ptr == ',') {
            ptr++;
        }
    }
}

/* Main function to demonstrate usage */
int main(int argc, char *argv[]) {
    char command[100];
    char *token;
    char *cmd;
    char *arg;
    FileSystem* fs = initialize_file_system();
    printf("File system initialized. Root directory: %s\n", fs->root->name);

    if (argc > 1) {
        create_files_from_list(fs, argv[1]);
    }

    help();

    while (1) {
        printf("\nEnter Your Command: ");
        if (fgets(command, sizeof(command), stdin) != NULL) {
            command[strcspn(command, "\n")] = 0;

            /* Returns first token */
            token = strtok(command, " ");
            cmd = token;

            /* Get the second token */
            token = strtok(NULL, " ");
            arg = token;

            if (cmd == NULL) {
                printf("No command entered.\n");
                continue;
            }

            if (strcmp(cmd, "cd") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                cd(fs, arg);
            } else if (strcmp(cmd, "ls") == 0) {
                ls(fs->current);
            } else if (strcmp(cmd, "pwd") == 0) {
                pwd(fs->current);
            } else if (strcmp(cmd, "cat") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command, Give the Name of File: %s\n", cmd);
                    continue;
                }
                if (find_child(fs->current, arg) != NULL) {
                    cat(find_child(fs->current, arg));
                } else {
                    printf("File not found: %s\n", arg);
                }
            } else if (strcmp(cmd, "cp") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                cp(fs->current, arg);
            } else if (strcmp(cmd, "mv") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                mv(fs->current, arg);
            } else if (strcmp(cmd, "rm") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                rm(fs->current, arg);
            } else if (strcmp(cmd, "mkdir") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                if (has_duplicate_name(fs->current, arg)) {
                    printf("Directory already exists: %s\n", arg);
                } else {
                    mkdir(fs->current, arg);
                }
            } else if (strcmp(cmd, "rmdir") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                rmdir(fs->current, arg);
            } else if (strcmp(cmd, "file") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                if (has_duplicate_name(fs->current, arg)) {
                    printf("File already exists: %s\n", arg);
                } else {
                    file(fs->current, arg);
                }
            } else if (strcmp(cmd, "search") == 0) {
                if (arg == NULL) {
                    printf("Argument missing for command: %s\n", cmd);
                    continue;
                }
                search(fs->current, arg);
            } else if (strcmp(cmd, "greet") == 0) {
                greet_human();
            } else if (strcmp(cmd, "tree") == 0) {
                tree(fs->root, 0);
            } else if (strcmp(cmd, "dirprint") == 0) {
                dirprint(fs);
            } else if (strcmp(cmd, "help") == 0) {
                help();
            } else if (strcmp(cmd, "exit") == 0) {
                printf("Exiting the file system.\n");
                break;
            } else {
                printf("%s is not a command we have created. Sorry, don't fail me.\n", cmd);
            }
        }
    }

    return 0;
}