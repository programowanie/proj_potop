#include "Slav.h"
#include "weapon.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "fight.h"
#include <math.h>

#define HIT_FORCE 10
#define HIT_INTERVAL 1000000



bool fighting::slash(Slav* slavs){
	double attack[2];
	bool isLethal;
		for (int i = 0; i < 2; ++i)
			attack[i] = (rand() % 100) < slavs[i].get_skill()
				? (slavs[i]._weapon.get_attack()) / 100. * HIT_FORCE
				: 0;
		for(int i=0;i<2;i++)
			if(weatherParameters[2]==1 && slavs[i].get_obscured()==0){
				attack[i]-=10;
				printf("Z powodu slabej widocznosci %s ma trudnosci z trafieniem");
			}


		if(attack[1]==attack[0]){
			printf("%s i %s zderzaja sie szablami\n",slavs[0].get_name().c_str(),
				slavs[1].get_name().c_str());
			slavs[1].gripdown(1);slavs[0].gripdown(1);
		}
		else {
		int whoHits = (int)(attack[1] > attack[0]);
		if(_worldDice>97)
			critickal(slavs[whoHits],slavs[1-whoHits]);
		
		int damage = attack[whoHits]- attack[1 - whoHits];
		
		damage *= (rand() % 100) < slavs[1-whoHits].get_skill()
			? 1 - (slavs[1-whoHits]._weapon.get_defence() / 100.)
			: 1;
		if(damage==0){
			printf("%s i %s zderzaja sie szablami\n",slavs[0].get_name().c_str(),
				slavs[1].get_name().c_str());
			slavs[0].gripdown(1);slavs[1].gripdown(1);
				isLethal=0;
		}
		else{
			
		 isLethal = slavs[1 - whoHits].damage(damage);

		printf(" [%2i, %2i] uderza %s z siłą %i grip=[%i,%i]\n ", 
			slavs[0].get_hp(), slavs[1].get_hp(), 
			slavs[whoHits].get_name().c_str(),
			damage,slavs[0].get_grip(),slavs[1].get_grip());

		riposte(slavs[1-whoHits],slavs[whoHits],damage);
		}
			
				slavs[1-whoHits].gripdown(1);
		checkGrip(slavs);
return isLethal	;		
		
}

}
void  fighting::fight(int var1,int var2){

	
	Slav slavs[2];
	bool isLethal;
	checkRain(slavs);
	for (int i = 0; i < 2; ++i)
		printf("%s\n", slavs[i].description().c_str());
	srand(time(NULL));
	while(1)
	{
		usleep(HIT_INTERVAL);
		rollDice();
		
		if(weatherParameters[1]==1)
			for(int i=0;i<2;i++)
				if(slavs[i].get_slippery()==0)
					slip(slavs[i]);

		checkTemperature(slavs);
		isLethal=slash(slavs);

		
			if(slavs[0].get_hp()<=0){
				printf("%s wygrywa\n", slavs[1].get_name().c_str());
				break;
			}
			if(slavs[1].get_hp()<=0){
				printf("%s wygrywa\n", slavs[0].get_name().c_str());
				break;
			} 


		
		
		for(int i=0;i<2;i++){
			slavs[i].fatiguedown(1);
			if(slavs[i].get_fatigue()<=0)
				slavs[i].exhaust();
			checkExhaustion(slavs[i]);
		}

		
			if(slavs[0].get_hp()<=0){
				printf("%s wygrywa\n", slavs[1].get_name().c_str());
				break;
			}
			if(slavs[1].get_hp()<=0){
				printf("%s wygrywa\n", slavs[0].get_name().c_str());
				break;
			} 
		
}	
}



void fighting::set_weather(){
	for(int i=0;i<4;i++)
		weatherParameters[i]=rand()%2;
	weatherParameters[4]=rand()%3-1;
	if(weatherParameters[0]==1)
		printf("Pada\n");
	if(weatherParameters[1]==1)
		printf("Jest slisko\n");
	if(weatherParameters[2]==1)
		printf("Jest mala widocznosc\n");
	if(weatherParameters[4]==1)
		printf("Jest goraco\n");
	if(weatherParameters[4]==-1)
		printf("Jest zimno\n");
}

void fighting::rollDice(){
	_worldDice=rand()%100;
	printf("dice = %i\n",_worldDice);
}

void fighting::checkExhaustion(Slav s){
	if(s.get_exhausted()==true){
		s.damage(5);
		s.gripdown(2);
		printf("%s jest zmeczony walka",s.get_name().c_str());
	}

}

void fighting::riposte(Slav s1,Slav s2,int damage){
	if(s1.get_riposte_counter()>=0){
		if(s1.get_skill()*s1._weapon.get_defence()/20>2*s1.get_fatigue()+_worldDice){
			s2.damage(damage);
			s1.fatiguedown(1);
			s1.ripostedown();
			printf("%s ripostuje %s \n",s1.get_name().c_str(),s2.get_name().c_str());
		}
	}
}

void fighting::checkGrip(Slav* slavs){
	for(int i =0;i<2;i++){
			int grip=(int)slavs[i].get_grip() ;
			if(grip<0){
				printf("%s wypada bron, zostaje uderzony przez %s\n",slavs[i].get_name().c_str(),slavs[1-i].get_name().c_str());
				slavs[i].damage(abs(slavs[1-i]._weapon.get_attack() - slavs[i]._weapon.get_defence())) ;
				if(weatherParameters[1]==1 && slavs[i].get_slippery()==0){
					printf(" %s z powodu sliskiej powierzchni i braku umiejetnosici jescze raz zostaje uderzony\n",slavs[i].get_name().c_str() );
					slavs[i].damage(abs(slavs[1-i]._weapon.get_attack() - slavs[i]._weapon.get_defence())) ;
				}
				slavs[i].set_grip(10) ;
				
			}
		}	
}

void fighting::slip(Slav s){
	if(s.get_fatigue()<30){
		s.damage(3);
		s.gripdown(2);
		s.fatiguedown(3);
		printf("%s wywraca sie na sliskiej powierzchni",s.get_name().c_str());
	}
}

void fighting::checkRain(Slav* slavs){
	if(weatherParameters[0]==1)
		for(int i=0;i<2;i++)
			if(slavs[i].get_rain()==0){
				slavs[i].set_skill(slavs[i].get_baseSkill()-10);
				printf("pada %s gorzej sobie radzi\n",slavs[i].get_name().c_str());
			}

}
void fighting::checkTemperature(Slav* slavs){
	if(weatherParameters[4]!=0)
		for(int i=0;i<2;i++)
			if(slavs[i].get_temperature()!=weatherParameters[4] || slavs[i].get_temperature()!=2){
				slavs[i].fatiguedown(2);
				slavs[i].gripdown(1);
				printf("%s nie radzi sobie z temperatura",slavs[i].get_name().c_str());
			}
}
void fighting::critickal(Slav slavs1,Slav slavs2){
	printf("%s dzieki szczesciu uderza %s nie dajac mu szansy sie przygotowac",slavs1.get_name().c_str(),
		slavs2.get_name().c_str());
	slavs2.damage(10);
	slavs2.fatiguedown(10);
}
