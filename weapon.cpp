#include "weapon.h"
#include <stdlib.h>


int randomValue2(){
	return 20 + rand() % 75;	
}

Weapon::Weapon(){
	_attack=randomValue2();
	_defence=randomValue2();
	_durability= 20+rand()%20;
	
}
