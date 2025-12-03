#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int studentID;
    char fullName[100];
    char batch[50];
    char membership[10];
    char regDate[20];
    char dob[20];
    char interest[10];
};

void loadDatabase(const char *filename, struct Student **database, int *total) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error!Opening File.\n");
        exit(1);
    }
    struct Student temp;
    while (fread(&temp, sizeof(struct Student), 1, fptr)) {
        *database = realloc(*database, (*total + 1) * sizeof(struct Student));
        (*database)[*total] = temp;
        (*total)++;
    }
    fclose(fptr);
}

void saveDatabase(const char *filename, struct Student *database, int total) {
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error!Opening File.\n");
        exit(1);
    }

    for (int i = 0; i < total; i++) {
        fwrite(&database[i], sizeof(struct Student), 1, fptr);
    }

    fclose(fptr);
}

int findStudent(int id, struct Student *database, int total) {
    for (int i = 0; i < total; i++) {
        if (database[i].studentID == id)
            return i;
    }
    return -1;
}

void addStudent(const char *filename, struct Student **database, int *total) {
    struct Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);
    if (findStudent(s.studentID, *database, *total) != -1) {
        printf("Student ID already exists!\n");
        return;
    }
    printf("Enter Full Name: ");
    getchar();
    fgets(s.fullName, 100, stdin);
    s.fullName[strcspn(s.fullName, "\n")] = 0;
    printf("Enter Batch [CS/SE/AI/Cyber Security]: ");
    fgets(s.batch, 50, stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;
    printf("Enter Membership [IEEE/ACM] : ");
    fgets(s.membership, 10, stdin);
    s.membership[strcspn(s.membership, "\n")] = 0;
    printf("Enter Registration Date [DD-MM-YYYY] : ");
    fgets(s.regDate, 20, stdin);
    s.regDate[strcspn(s.regDate, "\n")] = 0;
    printf("Enter Date of Birth [DD-MM-YYYY] : ");
    fgets(s.dob, 20, stdin);
    s.dob[strcspn(s.dob, "\n")] = 0;
    printf("Enter Interest [IEEE/ACM/Both] : ");
    fgets(s.interest, 10, stdin);
    s.interest[strcspn(s.interest, "\n")] = 0;
    *database = realloc(*database, (*total + 1) * sizeof(struct Student));
    (*database)[*total] = s;
    (*total)++;
    saveDatabase(filename, *database, *total);
    printf("Student Added Successfully!\n");
}

void updateStudent(const char *filename, struct Student *database, int total) {
    int id;
    printf("Enter Student ID to update : ");
    scanf("%d", &id);
    int pos = findStudent(id, database, total);
    if (pos == -1) {
        printf("Student not found!\n");
        return;
    }
    printf("Enter New Batch : ");
    getchar();
    fgets(database[pos].batch, 50, stdin);
    database[pos].batch[strcspn(database[pos].batch, "\n")] = 0;
    printf("Enter New Membership [IEEE/ACM] : ");
    fgets(database[pos].membership, 10, stdin);
    database[pos].membership[strcspn(database[pos].membership, "\n")] = 0;
    saveDatabase(filename, database, total);
    printf("Record Updated!\n");
}

void deleteStudent(const char *filename, struct Student **database, int *total) {
    int id;
    printf("Enter Student ID to delete : ");
    scanf("%d", &id);
    int pos = findStudent(id, *database, *total);
    if (pos == -1) {
        printf("Student Not Found!\n");
        return;
    }
    for (int i = pos; i < *total - 1; i++) {
        (*database)[i] = (*database)[i + 1];
    }
    (*total)--;
    *database = realloc(*database, *total * sizeof(struct Student));
    saveDatabase(filename, *database, *total);
    printf("Student Deleted!\n");
}

void displayAll(struct Student *database, int total) {
    if (total == 0) {
        printf("No records found.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("\n--------Student %d--------\n", i+1);
        printf("Student ID : %d\n", database[i].studentID);
        printf("Name : %s\n", database[i].fullName);
        printf("Batch : %s\n", database[i].batch);
        printf("Membership : %s\n", database[i].membership);
        printf("Reg Date : %s\n", database[i].regDate);
        printf("DOB : %s\n", database[i].dob);
        printf("Interest : %s\n", database[i].interest);
    }
}

void batchReport(struct Student *database, int total) {
    char batchName[50];
    printf("Enter batch [CS/SE/AI/Cyber Security] : ");
    getchar();
    fgets(batchName, 50, stdin);
    batchName[strcspn(batchName, "\n")] = 0;
    printf("\n--- Students in Batch %s ---\n", batchName);
    int found = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(database[i].batch, batchName) == 0) {
            printf("ID: %d",database[i].studentID);
            printf("Membership : %s", database[i].membership);
            printf("Name: %s",database[i].fullName);
            found = 1;
        }
    }
    if (!found)
        printf("No students found in this batch.\n");
}

int main() {
    struct Student *database = NULL;
    int total = 0;
    const char *filename = "members.dat";
    loadDatabase(filename, &database, &total);
    int choice;
	do{
        printf("-------MEMBERSHIP SYSTEM MENU-------\n");
        printf("1 : Register New Student\n");
        printf("2 : Update Student\n");
        printf("3 : Delete Student\n");
        printf("4 : View All Students\n");
        printf("5 : Batch-wise Report\n");
        printf("6 : Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:{
				addStudent(filename, &database, &total); 
				break;
			}
            case 2:{
				updateStudent(filename, database, total);
				break;
			}
            case 3:{
				deleteStudent(filename, &database, &total);
				break;
			}
            case 4:{
				displayAll(database, total); 
				break;
			} 
            case 5:{
				batchReport(database, total); 
				break;}
            case 6:{
                saveDatabase(filename, database, total);
                free(database);
            	break;
			}
            default:{
                printf("Invalid choice!\n");
                break;
			}
        }
    }while(choice != 6);

    return 0;
}

