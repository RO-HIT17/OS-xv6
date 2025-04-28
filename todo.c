#include "types.h"
#include "stat.h"
#include "user.h"

// Declare system calls
int todo_add(char *desc);
int todo_list(void);
int todo_done(int id);

// Custom strcat implementation
void strcat(char *dest, const char *src) {
    while (*dest) {  
        dest++;
    }
    while (*src) {  
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: todo [add|list|done] [task]\n");
        exit();
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            printf(2, "Usage: todo add <description>\n");
            exit();
        }

        char desc[512];
        desc[0] = '\0';  // Start with empty string

        for (int i = 2; i < argc; i++) {
            strcat(desc, argv[i]);
            if (i != argc - 1) {
                strcat(desc, " ");  // Add space between words
            }
        }

        todo_add(desc);
    } else if (strcmp(argv[1], "list") == 0) {
        todo_list();
    } else if (strcmp(argv[1], "done") == 0) {
        if (argc != 3) {
            printf(2, "Usage: todo done <task_id>\n");
            exit();
        }
        todo_done(atoi(argv[2]));
    } else {
        printf(2, "Unknown command.\n");
    }

    exit();
}
