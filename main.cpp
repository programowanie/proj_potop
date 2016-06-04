#include "Slav.h"
#include "weapon.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "fight.h"



int main(int argc, char const *argv[])
{	
	srand(time(NULL));
	fighting f;
	f.set_weather();
	f.fight(1,1);
}