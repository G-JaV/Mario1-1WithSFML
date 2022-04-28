#pragma once

#include"totalsettings.h"
#include"insideQuestion.h"
#include"Goomba.h"

class Mario {
	float x;
	float y;
	float vertical_speed = 0;
	float horizontal_speed = 0;

	bool dead=false;//if the mario is dead
	int form = 0;//show that the mario is big or small

	int jump_timer = 0;//used to make mario jump higher when upbutton is pressed longer
	int record_jump_timer = 0;//prevent mario from jump again when upbutton is pressed several times when he already jumped
	int move_timer = 0;//show the 
	int recordx = 0, recordy = 0;//record the coin's position when it is activited inside a questionbox

	int immortal_time = 0;//the immortal time when mario is attacked

	bool direction = true;//the direction of mario, true is right, false is left
	bool win = false;//judge if we win the game

	int trans_timer = 0;//used to show the twinkle when mario eat a mushroom or get attacked
	float bigy = 0;//used to record the location when mario eat a mushroom to show the ani

//	sf::Sprite sprite; 曾经使用这个来实现画mario，但是后面发现画大mario时会只画一半，因此改用在draw函数中新定义一个sprite
	sf::Texture texture;

public:
	Mario();
	float getx();
	float gety();
	bool getdeath();
	bool getwin();
	void upgrade();//from small mario to big one
	int getform();//get the form of mario either big or small
	void degrade();//from big to small
	void drawwin(Map& map, sf::RenderWindow& window, int& flag);//draw the winning animation
	void draw(sf::RenderWindow& window);
	void update(Map& map, std::vector<InsideQ>& v, sf::RenderWindow& window, std::vector<Goomba>& enemy);//renew the state of mario
	void activate(std::vector<InsideQ>& v, float x, float y);
	void setdeath(bool b);
};