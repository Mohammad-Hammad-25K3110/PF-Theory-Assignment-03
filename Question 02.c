#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
	if(planet > totalPlanets || fuel <= 0){
		if(planet > totalPlanets)printf("==============  Journey completed!  ==============\n");
		else{
			printf("============  Ran out of fuel!  ============\n");
		}
		return;
	}
	if(planet % 4 == 0) fuel = (fuel + recharge + solarBonus) - consumption;
	else{
		fuel = (fuel + recharge) - consumption;
	}
	printf("-------------------------------------------\n");
	printf("Planet : %d      Remaining Fuel : %d\n", planet, fuel);
	printf("-------------------------------------------\n");
	calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main(){
	int fuel, consumption, recharge, solarBonus, planet, totalPlanets;
	do{
	printf("Enter Total Fuel : ");
	scanf("%d", &fuel);
	}while(fuel <= 0);
	do{
	printf("Enter Fuel Consumption per Planet: ");
	scanf("%d", &consumption);
	}while(consumption <= 0);
	do{
	printf("Enter Fuel Recharge at every Planet : ");
	scanf("%d", &recharge);
	}while(recharge < 0);
	do{
	printf("Enter Solar Bonus at every 4th Planet : ");
	scanf("%d", &solarBonus);
	}while(solarBonus < 0);
	do{
	printf("Enter Current Planet Number : ");
	scanf("%d", &planet);
	}while(planet < 1);
	do{
	printf("Enter Total Number of Planets : ");
	scanf("%d", &totalPlanets);
	}while(totalPlanets < 1 || totalPlanets < planet);
	calculateFuel(fuel, consumption, recharge,solarBonus, planet, totalPlanets);
	return 0;
}
