#include"Goomba.h"

Goomba::Goomba(float a, float b) :x(a), y(b) {};

void Goomba::move(Map& map) {
	if (y + vertical_speed >= SCREEN_HEIGHT) {  //if Goomba is out of the map which means drop out, let's just consider it dead
		dead = true;
	}
	else {
		int tmpx = floor(x / CELL_SIZE);
		int tmpy = ceil((y + vertical_speed) / CELL_SIZE);
		if (y>= SCREEN_HEIGHT-18 ||( map[tmpx][tmpy] == Cell::Coin || map[tmpx][tmpy] == Cell::Empty)&&(map[tmpx+1][tmpy]==Cell::Coin || map[tmpx+1][tmpy] == Cell::Empty)) {//使用短路运算符来吧后面的短路掉，板栗的down_collision
			y += vertical_speed;
		}
		if (horizontol_speed < 0) {  //Goomba's collision from the left
			tmpx = floor((x + horizontol_speed) / CELL_SIZE);
			tmpy = floor(y / CELL_SIZE);
			if (map[tmpx][tmpy] != Cell::Coin && map[tmpx][tmpy] != Cell::Empty) {
				horizontol_speed = -horizontol_speed;
			}
			else {
				x += horizontol_speed;
			}
		}
		else {   //Goomba's collision from the right
			tmpx = floor((x + horizontol_speed + 16) / CELL_SIZE);
			tmpy = floor(y / CELL_SIZE);
			if (map[tmpx][tmpy] != Cell::Coin && map[tmpx][tmpy] != Cell::Empty) {
				horizontol_speed = -horizontol_speed;
			}
			else {
				x += horizontol_speed;
			}
		}
	}
}

float Goomba::getx() {
	return x;
}
float Goomba::gety() {
	return y;
}
bool Goomba::getdirection() {
	if (horizontol_speed > 0) return true;
	return false;
}

void Goomba::setdeath(bool d) {
	dead = d;
}
void Goomba::negetive_speed() {
	horizontol_speed = -horizontol_speed;
}

bool Goomba::getdeath() {
	return dead;
}

void Goomba::draw(sf::RenderWindow& window) {
	sf::Texture t;
	if (timer /10%2==0) {    //thats what I said ,load different image depends on timer
		t.loadFromFile("resources/goomba1.png");
		timer++;
	}
	else{
		t.loadFromFile("resources/goomba2.png");
		timer++;
	}
	sf::Sprite s;
	s.setTexture(t);
	s.setPosition(x, y);
	window.draw(s);
}