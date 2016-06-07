#pragma once

#include <string>
#include <vector>
#include "weapon.h"
using namespace std;




class Slav
{
	static vector<string>names;

	string _name;
	int _hp, baseHp;
	int _grip;
	int _fatigue, baseFatigue;
	int _skill, baseSkill;
	int _rain;
	int _slippery;
	int _temperature;
	int _wind;
	int _obscured;
	bool exhausted;
	int riposte_counter;

	static void init();

public:
	Slav();
	Weapon _weapon;
	int get_hp() { return _hp; }
	string get_name() { return _name; }
	int get_grip() {return _grip;}
	void set_grip(int value);
	int get_fatigue(){return _fatigue;}
	int get_skill(){return _skill;}
	void gripdown(int value);
	bool damage(int value);
	void set_fatigue(int value);
	void fatiguedown(int value);
	int get_rain(){return _rain;}
	int get_slippery(){return _slippery;}
	int get_temperature(){return _temperature;}
	int get_wind(){return _wind;}
	int get_obscured(){return _obscured;}
	void exhaust();
	bool get_exhausted();
	int get_riposte_counter(){return riposte_counter;}
	void ripostedown();
	void set_skill(int value);
	int get_baseSkill() {return baseSkill;}
	string description();
};
