#pragma once
#include"totalsettings.h"
#include"collision.h"

class Goomba {//the class of Goomba !
	float x;//Goomba's position
	float y;

	float vertical_speed=0.8;//Goomba vertical speed
	float horizontol_speed = -0.4;

	int timer=0;//timer is for a Goomba's animation ,which means every ten of this timer ,we will change the image of Goomba

	bool dead = false;//if the Goomba is dead or not

public:
	Goomba(float a, float b);
	float getx();
	float gety();
	bool getdeath();
	bool getdirection();
	void setdeath(bool d);
	void negetive_speed();//negetive the speed
	void move(Map& map);  //Goomba's moving!! Collision has been considered
	void draw(sf::RenderWindow& window);//draw a Goomba
};