#pragma once
#include<math.h>
#include"totalsettings.h"
#include"collision.h"

class InsideQ {//the class that show whats inside each questionbox
	float x; //the location
	float y;

	float move = 0;//this is used to make the animation that the mushroom move out of the questionbox
	float mushmovex = 0.4;//the horizontol speed of Mushroom
	float mushmovey = 0.6;//the vertical speed of Mushroom

	bool form;//indicate that the thing inside is either a mushroom or a coin
	bool kicked = false;//either the questionbox is activate

public:
	InsideQ(float a,float b,bool f);
	float getx();
	float gety();
	void setkick();
	bool getkick();
	bool getform();
	float getmove();
	void CoinMove();//the animation that coin-questionbox is activate
	void MushroomMove(Map& map, float mariox, float marioy);//the animation that mushroom-questionbox is activate
	void draw(sf::RenderWindow& window);//draw it!
};