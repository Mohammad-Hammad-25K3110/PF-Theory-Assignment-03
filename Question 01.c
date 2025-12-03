#include <stdio.h>

float calculateRepayment(float loan, float interestRate, int years, float installment){
	static float totalRepayment = 0;
	if (loan <= 0 || years == 0){
		if(loan <= 0)printf("Loan has returned!\n");
		else{
			printf("No more years left.\n");
		}
		return 0;
	}
	float interest = loan * interestRate;
	loan += interest;
	totalRepayment += installment + interest;
	loan -= installment;
	calculateRepayment(loan, interestRate, years - 1, installment);
	printf("-------------------------------------------\n");
	printf("Year : %d      Remaining Loan : %.2f\n", years, loan);
	printf("-------------------------------------------\n");
	return totalRepayment;
}

//For every recursion call loan is being calculated for that year, total repayment is accumulated,
//remaining years is being decremented, and remaining loan is being printed by every call for that year

int main(){
	float loan, interestRate, installment;
	int years;
	do{
	printf("Enter Loan : ");
	scanf("%f", &loan);
	}while(loan <= 0);
	do{
	printf("Enter Interest Rate : ");
	scanf("%f", &interestRate);
	}while(interestRate < 0);
	interestRate /= 100;
	do{
	printf("Enter Years : ");
	scanf("%d", &years);
	}while(years <= 0);
	do{
	printf("Enter Installment : ");
	scanf("%f", &installment);
	}while(installment <= 0);
	float totalRepayment = calculateRepayment(loan, interestRate, years, installment);
	printf("Total Repayment : %.2f", totalRepayment);
	return 0;
}
