#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
}

int printList() {
    FILE *file = fopen("tasks.txt", "r");

    if(file == NULL) {
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    if(size == 0) {
        printf("File has no tasks.\n");
        return 0;
    }

    char line[256];

    printf("To Do List: \n");

    while(fgets(line, sizeof(line), file)) {
        printf("- %s", line);
    }

    fclose(file);

    return 0;
}

int newTask() {
    printf("\nNew task: ");
    char task[256] = "";
    fgets(task, sizeof(task), stdin);

    // remove trailing newline if it exists
    size_t len = strcspn(task, "\n");
    task[len] = 0;

    if(len == 0) {
        printf("Task cannot be empty!\n");
        return 0;
    }

    FILE *file = fopen("tasks.txt", "a");

    if(file == NULL) {
        return 1;
    }

    fprintf(file, "%s\n", task);

    fclose(file);

    printf("\n");
    printList();

    return 0;
}

int routeInput() {
    char input[10] = "";
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if(strcmp(input, "r") == 0) {
        printf("\n");
        printList();
        return 0;
    }
    else if(strcmp(input, "c") == 0) {
        clearScreen();
        printList();
        return 0;
    }
    else if(strcmp(input, "w") == 0){
        newTask();
        return 0;
    }
    else if(strcmp(input, "q") == 0) {
        return 1;
    }
    else {
        printf("Invalid input, try again.\n");
        return 0;
    }
}

int menu() {
    while(1) {
        printf("\n");
        printf("Choose an option:\n");
        printf("r - Reload file\n");
        printf("c - Clear screen\n");
        printf("w - Add new task\n");
        printf("q - Quit\n");
    
        if(routeInput() == 1) {
            return 1;
        }
    }
}

int createTasksFile() {
    FILE *filePointer;
    const char *filename = "tasks.txt";
    filePointer = fopen(filename, "w");

    if(filePointer == NULL) {
        return 1;
    }
    fclose(filePointer);
    return 0;
}

int main() {
    if(printList() == 1) {
        printf("ERROR: task.txt does not exist\n");
        printf("Create one? [y/n]: ");
        char input[10] = "";
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if(strcmp(input, "y") == 0) {
            if(createTasksFile() == 1) {
                printf("ERROR: Could not create tasks.txt");
                return 0;
            }
        }
        else if(strcmp(input, "n") == 0) {
            return 0;
        }
    }

    if(menu() == 1) {
        return 0;
    }
}
