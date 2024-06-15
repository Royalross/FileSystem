
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileSystem.h"
#include "utility.h"

/* Function to display help */
void help() {
    printf("Available commands:\n");
    printf("cd: Change directory\n");
    printf("ls: List directory contents\n");
    printf("pwd: Print working directory\n");
    printf("cat: Display file contents\n");
    printf("cp: Copy file or directory\n");
    printf("mv: Move or rename file or directory\n");
    printf("rm: Remove file\n");
    printf("mkdir: Create new directory\n");
    printf("rmdir: Remove directory\n");
    printf("file: Create a new file with content\n");
    printf("search: Search for a file or directory\n");
    printf("greet: System just saying hi \n");
    printf("tree: Display the directory tree\n");
    printf("dirprint: Print directory structure\n");
    printf("help: List available commands\n");
    printf("exit: Exit the file system\n");
}

/* Function to change directory */
void cd(FileSystem *fs, const char *name) {
    if (strcmp(name, "..") == 0) {
        if (fs->current->parent != NULL) {
            fs->current = fs->current->parent;
        }
    } else {
        Node *target = find_child(fs->current, name);
        if (target == NULL) {
            printf("Directory or file not found: %s\n", name);
            return;
        }
        if (target->is_file) {
            printf("%s is a file, moving to its parent directory.\n", name);
            if (target->parent != NULL) {
                fs->current = target->parent;
                printf("Moved to parent directory: %s\n", fs->current->name);
            }
        } else {
            fs->current = target;
        }
    }
}

/* Function to display file contents */
void cat(Node *current) {
    if (current->is_file) {
        printf("%s\n", current->content);
    } else {
        printf("Not a file.\n");
    }
}

/* Function to list the contents of the current directory */
void ls(Node *node) {
    int i;
    for (i = 0; i < node->child_count; i++) {
        printf("%s%s\n", node->children[i]->name, node->children[i]->is_file ? "" : "/");
    }
}

/* Function to print the current working directory path */
void pwd(Node *node) {
    if (node->parent != NULL) {
        pwd(node->parent);
    }
    printf("/%s", node->name);
}

/* Function to add a file */
void file(Node *current, const char *name) {
    if (current->child_count < MAX_CHILDREN) {
        Node *file = create_node(name, 1, current);
        printf("Enter content for the file: ");
        getchar(); /* To consume the leftover newline character */
        fgets(file->content, MAX_CONTENT_LENGTH, stdin);
        current->children[current->child_count++] = file;
    } else {
        printf("Cannot add more files, directory is full.\n");
    }
}

/* Function to remove a file */
void rm(Node *current, const char *name) {
    Node *target = find_child(current, name);
    if (target == NULL) {
        printf("File or directory not found: %s\n", name);
        return;
    }

    if (target->is_file) {
        remove_child(current, name);
    } else {
        printf("%s is a directory, use rmdir to remove directories.\n", name);
    }
}

/* Function to create a directory */
void mkdir(Node *parent, const char *name) {
    Node *new_dir = create_node(name, 0, parent);
    add_child(parent, new_dir);
}

/* Function to remove a directory */
void rmdir(Node *node, const char *name) {
    Node *dir = find_child(node, name);
    if (dir != NULL && dir->child_count == 0) {
        remove_child(node, name);
    } else {
        printf("Directory is not empty or does not exist\n");
    }
}

/* Function to copy a node (file or directory) */
void cp(Node *current, const char *name) {
    Node *copy = (Node *)malloc(sizeof(Node));
    Node *target = find_child(current, name);
    if (target == NULL) {
        printf("File or directory not found: %s\n", name);
        return;
    }
    copy = copy_node(target, name, current->parent);
    add_child(current->parent, copy);
    free(copy);
}

/* Function to move or rename a file or directory */
void mv(Node *current, const char *new_name) {
    if (strcmp(current->name, "Root") == 0) {
        printf("You cannot rename the root directory.\n");
    } else {
        strncpy(current->name, new_name, MAX_NAME_LENGTH);
    }
}

/* Custom Command: Function to search for a file or directory */
void search(Node *current, const char *name) {
    int i;
    if (strcmp(current->name, name) == 0) {
        printf("Found: /%s\n", current->name);
        return;
    }
    for (i = 0; i < current->child_count; i++) {
        search(current->children[i], name);
    }
}

void greet_human() {
    char command[3];
    printf("Hello There thank you for using me, Hope I will be a great help");
    printf(" You are Human right?\n");
    
    /* Check the first letter only because that tells all we need to know */
    printf("Please enter Y for Yes or N for No: ");
    scanf("%s", command);

    /* These took a while , credit: https://ascii.co.uk/art/doors && https://www.asciiart.eu/weapons/shields*/
    
    if (command[0] == 'N' || command[0] == 'n') {
        printf("I do not serve Robots, only humans\n");
        printf("I will now self-destruct\n");
        printf("                /¯¯\\\n");
        printf("               \\__/\n");
        printf("                 ||\n");
        printf("                 ||\n");
        printf("                |  |\n");
        printf("                |  |\n");
        printf("                |  |\n");
        printf("                |  |\n");
        printf("                |  |\n");
        printf("                |  |\n");
        printf("  .         --.----.--.\n");
        printf("          .-----\\__/-----.\n");
        printf("   ___---¯¯////¯¯|\\/|¯¯\\\\\\\\---___\n");
        printf("/¯¯ __O_--////   |  |   \\\\\\\\--_O__ ¯¯\\\n");
        printf("| O?¯      ¯¯¯    |  |    ¯¯¯      ¯?O |\n");
        printf("|  '    _.-.      |  |      .-._    '  |\n");
        printf("|O|    ?..?      ./  \\.      ?..?    |O|\n");
        printf("| |     '?. .-.  | /\\ |  .-. .?'     | |\n");
        printf("| ---__  ¯?__?  /|\\¯¯/|\\  ?__?¯  __--- |\n");
        printf("|O     \\         ||\\/ |         /     O|\n");
        printf("|       \\  /¯?_  ||   |  _?¯\\  /       |\n");
        printf("|       / /    - ||   | -    \\ \\       |\n");
        printf("|O   __/  | __   ||   |   __ |  \\__   O|\n");
        printf("| ---     |/  -_/||   |\\_-  \\|     --- |\n");
        printf("|O|            \\ ||   | /            |O|\n");
        printf("\\ '              ||   |        ^~DLF ' /\n");
        printf(" \\O\\    _-¯?.    ||   |    .?¯-_    /O/\n");
        printf("  \\ \\  /  /¯¯¯?  ||   |  ?¯¯¯\\  \\  / /\n");
        printf("   \\O\\/   |      ||   |      |   \\/O/\n");
        printf("    \\     |      ||   |      |     /\n");
        printf("     '.O  |_     ||   |     _|  O.'\n");
        printf("        '._O'.__/||   |\\__.O_.\n");
        printf("           '._ O ||   | O _.'\n");
        printf("              '._||   |_.\n");
        printf("                 ||   |\n");
        printf("                 ||   |\n");
        printf("                 | \\/ |\n");
        printf("                 |  | |\n");
        printf("                  \\ |/\n");
        printf("                   \\/\n");
    } else {
        printf("Good good Just checking\n");
        printf(" You Can Enter\n");
        printf("   /|\n");
        printf("  / |\n");
        printf(" /__|___\n");
        printf("|       |\n");
        printf("|       |\n");
        printf("|       |\n");
        printf("|       +`\n");
        printf("|       |\n");
        printf("|_______|\n");
    }
}



/* Custom Command: Function to display the directory tree */
void tree(Node *node, int level) {
    int i,j;
    for (i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s%s\n", node->name, node->is_file ? "" : "/");
    for (j = 0; j < node->child_count; j++) {
        tree(node->children[j], level + 1);
    }
}

/* Custom Command: Function to print directory structure */
void dirprint(FileSystem *fs) {
    int i;
    Node *current = fs->current;
    Node *parent = current->parent;

    printf("Current Directory: %s\n", current->name);
    printf("Parent Directory: %s\n", parent ? parent->name : "None");
    printf("Siblings: ");
    if (parent) {
        for (i = 0; i < parent->child_count; i++) {
            if (parent->children[i] != current) {
                printf("%s ", parent->children[i]->name);
            }
        }
    }
    printf("\nPath to root:\n");
    pwd(current);
    printf("\n");
}
