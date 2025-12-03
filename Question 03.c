#include <stdio.h>
#include <string.h>

// To give every employee (below a certain threshold ) a 10% salary bonus i would create a function with arguments of structure array,
// size n and threshold. We will use for loop for the size of array and check every employees salary and compare it with the threshold.
// if it is below threshold then we multiply it with 1.1 and assign it back to it. This way every employee below the current threshold
// will get a 10% bonus.

struct Employee{
	int id;
	char name[50];
	char designation[50];
	float salary;
};

void displayEmployees(struct Employee employeesArray[], int n){
	for(int i = 0; i < n; i++){
		printf("-------Employee %d-------\n", i+1);
		printf("Employee ID : %d\n", employeesArray[i].id);
		printf("Employee Name : %s\n", employeesArray[i].name);
		printf("Employee Designation : %s\n", employeesArray[i].designation);
		printf("Employee Salary : %.2f\n", employeesArray[i].salary);
	}
}

void findHighestSalary(struct Employee employeesArray[], int n){
	float highestSalary = employeesArray[0].salary;
	int highestIndex = 0;
	for(int i = 1; i < n; i++){
		if(employeesArray[i].salary > highestSalary){
			highestSalary = employeesArray[i].salary;
			highestIndex = i;
		}
	}
	printf("-------Highest Paid Employee Details-------\n");
	printf("Employee ID : %d\n", employeesArray[highestIndex].id);
	printf("Employee Name : %s\n", employeesArray[highestIndex].name);
	printf("Employee Designation : %s\n", employeesArray[highestIndex].designation);
	printf("Employee Salary : %.2f\n", employeesArray[highestIndex].salary);
}

void searchEmployee(struct Employee employeesArray[], int n){
	int choice;
	do{
		printf("Enter '1' to Search by ID or '2' to search by Name : ");
		scanf("%d", &choice);
	}while(choice != 1 && choice != 2);
	switch (choice){
		case 1:{
			int id, found = 0;
			printf("Enter ID to search : ");
			scanf("%d", &id);
			for(int i = 0; i < n; i++){
				if(id == employeesArray[i].id){
					found = 1;
					printf("Employee Found!\n");
					break;
				}
			}
			if(!found)printf("Employee Not Found!\n");
			break;
		}
		case 2:{
			int found = 0;
			char name[50];
			printf("Enter Name to search : ");
			scanf(" %[^\n]", name);
			for(int i = 0; i < n; i++){
				if(strcmp(name, employeesArray[i].name) == 0){
					found = 1;
					printf("Employee Found!\n");
					break;
				}
			}
			if(!found)printf("Employee Not Found!\n");
			break;
		}
	}
}

int main(){
	int n, choice;
	printf("Enter Number of Employees : ");
	scanf("%d", &n);
	struct Employee employeesArray[n];
	for(int i = 0; i < n; i++){
		printf("-------Employee %d-------\n", i+1);
		do{
			printf("Enter Employee ID : ");
			scanf("%d", &employeesArray[i].id);
		}while(employeesArray[i].id < 0);
		printf("Enter Employee Name : ");
		scanf(" %[^\n]", employeesArray[i].name);
		printf("Enter Employee Designation : ");
		scanf(" %[^\n]", employeesArray[i].designation);
		do{
			printf("Enter Employee Salary : ");
			scanf("%f", &employeesArray[i].salary);
		}while(employeesArray[i].salary <= 0);
	}
	do{
	printf("-----ABC Technologies Employees Management System-----\n");
	printf("1 : Display All Employees Details\n");
	printf("2 : Display Highest Paid Employee Details\n");
	printf("3 : Search for Employee\n");
	printf("4 : Exit\n");
	printf("Enter Choice : ");
	scanf("%d", &choice);
	switch(choice){
		case 1:{
			displayEmployees(employeesArray, n);
			break;
		}
		case 2:{
			findHighestSalary(employeesArray, n);
			break;
		}
		case 3:{
			searchEmployee(employeesArray, n);
			break;
		}
		case 4:{
			break;
		}
		default:{
			printf("Invald Choice!\n");
			break;
		}
		
	}
	}while(choice != 4);
	return 0;
}
