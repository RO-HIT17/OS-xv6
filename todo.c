// user/todo.c

#include "types.h"
#include "stat.h"
#include "user.h"

// declare system calls
int todo_add(char *desc);
int todo_list(void);
int todo_done(int id);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: todo [add|list|done] [task]\n");
        exit();
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc != 3) {
            printf(2, "Usage: todo add \"task description\"\n");
            exit();
        }
        todo_add(argv[2]);
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
