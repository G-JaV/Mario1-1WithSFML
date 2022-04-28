#include"insideQuestion.h"

InsideQ::InsideQ(float a, float b,bool f):x(a),y(b), form(f){}

float InsideQ::getx() {
	return x;
}
float InsideQ::gety() {
	return y;
}
void InsideQ::setkick() {
	kicked = true;
}
bool InsideQ::getkick() {
	return kicked;
}
bool InsideQ::getform() {
	return form;
}
float InsideQ::getmove() {
	return move;
}

void InsideQ::CoinMove() {
	move= move+0.8;
}
void InsideQ::MushroomMove(Map& map, float mariox, float marioy) {
	if (abs(mariox - x) < 13 && abs(marioy - y + move) < 13) {  //Mario ate the Mushroom
		kicked = false;
	}
	if (move < 16)move = move + 0.2;
	else {
		if (y - move + mushmovey >= SCREEN_HEIGHT) {  //if the mushroom drop out of the map ,then break;
			return;
		}
		else {
			int tmpx = floor(x / CELL_SIZE);
			int tmpy = ceil((y - move + mushmovey) / CELL_SIZE);
			if ((y - move) >= SCREEN_HEIGHT - 18 || (map[tmpx][tmpy] == Cell::Coin || map[tmpx][tmpy] == Cell::Empty) && (map[tmpx + 1][tmpy] == Cell::Coin || map[tmpx + 1][tmpy] == Cell::Empty)) {//使用短路运算符来吧后面的短路掉，板栗的down_collision
				y += mushmovey;
			}
			if (mushmovex < 0) {  //the left collision test of the Mushroom
				tmpx = floor((x + mushmovex) / CELL_SIZE);
				tmpy = floor((y - move) / CELL_SIZE);
				if (map[tmpx][tmpy] != Cell::Coin && map[tmpx][tmpy] != Cell::Empty) {
					mushmovex = -mushmovex;
				}
				else {
					x += mushmovex;
				}
			}
			else {   //the right collision test of the Mushroom
				tmpx = floor((x + mushmovex + 16) / CELL_SIZE);
				tmpy = floor((y - move) / CELL_SIZE);
				if (map[tmpx][tmpy] != Cell::Coin && map[tmpx][tmpy] != Cell::Empty) {
					mushmovex = -mushmovex;
				}
				else {
					x += mushmovex;
				}
			}
		}

		//this is the old collision test, which will throw errors，so I redo it as the new collision test above.
	//	if (!down_collision(x, y - move + 0.4, map)) {
	//		y += 0.8;
	//	}
	//	if (mushmovex < 0) {
	//		if (left_collision(x + mushmovex, y - move, map)) {
	//			mushmovex = -mushmovex;
	//		}
	//		else {
	//			x += mushmovex;
	//		}
	//	}
	//	else {
	//		if (right_collision(x + mushmovex, y - move, map)) {
	//			mushmovex = -mushmovex;
	//		}
	//		else {
	//			x += mushmovex;
	//		}
	//	}
	}
}
void InsideQ::draw(sf::RenderWindow& window) {  //draw the inside of a questionbox
	if (move > 24 && !form) {
		kicked = false;
	}
	if (move >= 16 && form) {
		move = 16;
	}
	sf::Texture t;
	sf::Sprite s;
	if (form == 0)t.loadFromFile("resources/coin.png");
	else t.loadFromFile("resources/mushroom.png");
	s.setTexture(t);
	s.setPosition(x, y-move);
	window.draw(s);
}