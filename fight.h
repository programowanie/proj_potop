#pragma once 
#include "Slav.h"
class fighting{
int weatherParameters[5];
int _worldDice;

public:
fighting(){};
void set_weather();
void  fight(int var1,int var2);
void riposte(Slav s1,Slav s2,int damage);
bool slash(Slav* slavs);
void checkExhaustion(Slav s);
int get_worldDice(){return _worldDice;}
void rollDice();
void checkGrip(Slav* slavs);
void slip(Slav s);
void checkRain(Slav* slavs);
void checkTemperature(Slav* slavs);
void critickal(Slav slavs1,Slav slavs2);
};