#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

struct Editor{
    char **lines;
    int size;
    int capacity;
};

void insertLine(struct Editor *e, int index, const char *text) {
    if(index < 0 || index > e->size) {
        printf("Invalid index.\n");
        return;
    }
    if(e->size == e->capacity) {
        e->capacity++;
        char **temp = realloc(e->lines, e->capacity * sizeof(char*));
        if (temp == NULL) {
            printf("Memory Reallocation Failed!\n");
    		exit(1);
        }
        e->lines = temp;
    }
    char *newLine = malloc(strlen(text) + 1);
    if (newLine == NULL) {
        printf("Memory Allocation Failed!\n");
    	exit(1);
    }
    strcpy(newLine, text);
    memmove(&e->lines[index + 1], &e->lines[index], (e->size - index) * sizeof(char*));
    e->lines[index] = newLine;
    e->size++;
}

void deleteLine(struct Editor *e, int index) {
    if(index < 0 || index >= e->size) {
        printf("Invalid index.\n");
        return;
    }
    free(e->lines[index]);
    memmove(&e->lines[index], &e->lines[index + 1], (e->size - index - 1) * sizeof(char*));
    e->size--;
}

void printAllLines(struct Editor *e) {
    if (e->size == 0) {
        printf("No lines stored.\n");
        return;
    }
    for (int i = 0; i < e->size; i++) {
        printf("Line %d: %s\n", i+1, e->lines[i]);
    }
}

void shrinkToFit(struct Editor *e) {
    if (e->capacity == e->size) {
        printf("Already shrinked.\n");
        return;
    }
    char **temp = (char **)realloc(e->lines, e->size * sizeof(char*));
    if (temp == NULL && e->size > 0) {
        printf("Memory Reallocation Failed!\n");
    	exit(1);
    }
    e->lines = temp;
    e->capacity = e->size;
}

void freeAll(struct Editor *e) {
    for (int i = 0; i < e->size; i++) {
        free(e->lines[i]);
    }
    free(e->lines);
}

void saveToFile(struct Editor *e, const char *filename) {
    FILE *fptr = fopen(filename, "w");
    if(fptr == NULL) {
        printf("ERROR! Opening File.\n");
    	exit(1);
    }
    for(int i = 0; i < e->size; i++) {
        fprintf(fptr, "%s\n", e->lines[i]);
    }
    fclose(fptr);
    printf("Saved successfully.\n");
}

void loadFromFile(struct Editor *e, const char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("ERROR! Opening File.\n");
        exit(1);
    }

    freeAll(e);
    int capacity;
    printf("Enter Capacity of Editor : ");
    scanf("%d", &capacity);
    getchar();
    e->lines = (char **) malloc(capacity * sizeof(char*));
    if (e->lines == NULL) {
        printf("Memory Allocation Failed!\n");
    	exit(1);
    }
    e->size = 0;
    e->capacity = capacity;
    char buffer[2000];
    while (fgets(buffer, sizeof(buffer), fptr)) {
        buffer[strcspn(buffer, "\n")] = 0;
        insertLine(e, e->size, buffer);
    }
    fclose(fptr);
    printf("Loaded successfully.\n");
}

int main() {
    struct Editor editor;
    int capacity;
    printf("Enter Capacity of Editor : ");
    scanf("%d", &capacity);
    getchar();
    editor.lines = (char **)malloc(capacity * sizeof(char*));
    if (editor.lines == NULL) {
        printf("Memory Allocation Failed!\n");
    	exit(1);
    }
    editor.size = 0;
    editor.capacity = capacity;
    int choice, index;
    char *text;
    char filename[100];
   do{
        printf("\n-----Minimal Line-Based Text Editor Buffer-----\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. shrinkToFit\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
	        case 1:{
	            printf("Enter index : ");
			    scanf("%d", &index);
			    getchar(); 
			    printf("Enter text : ");
			    char buffer[2000];
			    fgets(buffer, sizeof(buffer), stdin);
			    buffer[strcspn(buffer, "\n")] = 0;
			    insertLine(&editor, index, buffer);
	            break;
			}
	        case 2:{
	            printf("Enter index : ");
	            scanf("%d", &index);
	            deleteLine(&editor, index);
	            break;
			}
	        case 3:{
	            printAllLines(&editor);
	            break;
	
			}  
	        case 4:{
	            printf("Enter filename : ");
	            scanf("%s", filename);
	            saveToFile(&editor, filename);
	            break;
			}      
	        case 5:{
	            printf("Enter filename : ");  
	            scanf("%s", filename);
	            loadFromFile(&editor, filename);
	            break;
			}
	        case 6:{
	            shrinkToFit(&editor);
	            break;
			}
	        case 7:{
	            freeAll(&editor);
				break;
			}
	        default:{
	            printf("Invalid choice.\n");
				break;
	        }
		}
    }while(choice != 7);
	return 0;
}


