#include "Slav.h"
#include "weapon.h"
#include <stdlib.h>
#include <fstream>
#include <iterator>
using namespace std;

vector <string> Slav::names;

void Slav::init()
{
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

int randomValue()
{
	return 20 + rand() % 75;	
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size());
	_name = names[rand() % amountOfNames];
	_hp = baseHp = randomValue();
	exp = 0;
	_skill=baseSkill=randomValue();
	_fatigue = baseFatigue = randomValue();
	_grip=20+rand()%40;
	_slippery=rand() % 2;
	exhausted=false;
	_rain=rand()%2;
	_slippery=rand()%2;
	_temperature=rand()%4-1;
	_wind=rand()%2;
	_obscured=rand()%2;
	riposte_counter=get_skill()*10/_weapon.get_defence() ;
}

string Slav::description()
{
	return _name + "\n\tHP: " + to_string(_hp) + "Grip: "+to_string(_grip) + "\n\t" +
		"attack" + to_string(_weapon.get_attack()) + 
		"defence" + to_string(_weapon.get_defence()) + 
		"durability " + to_string(_weapon.get_durability()) ;
}

bool Slav::damage(int value)
{
	_hp -= value;
	return _hp <= 0;
}

void Slav::heal()
{
	_hp = baseHp;
	exp++;
}

void Slav::gripdown(int value){
	_grip-=value;
}
void Slav::set_grip(int value){
	_grip=value;
}
void Slav::set_fatigue(int value){
	_fatigue=value;
}

void Slav::fatiguedown(int value){
	_fatigue-=value;
}
void Slav::exhaust(){
	if(exhausted==false)
		exhausted==true;
}
bool Slav::get_exhausted(){
	return exhausted;
}
void Slav::ripostedown(){
	riposte_counter--;
}
void Slav::set_skill(int value){
	_skill=value;
}