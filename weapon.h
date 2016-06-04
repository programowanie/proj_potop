#pragma once


class Weapon {
	int _attack ;
	int _defence ;
	int _durability ;
	
	public:
	Weapon() ;
	
	int	get_attack() {return _attack;}
	int get_defence() { return _defence;}
	int get_durability(){ return _durability;}
	
	
	
};