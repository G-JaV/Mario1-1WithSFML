#include<algorithm>
#include "Mario.h"

Mario::Mario() {
	y = 0.5f * SCREEN_HEIGHT;
	x = 0.5f * SCREEN_WIDTH;
	texture.loadFromFile("Resources/mariostand.png");
	//sprite.setTexture(texture);
	jump_timer = 0;
}

void Mario::draw(sf::RenderWindow& window) {
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(round(x), round(y));
	window.draw(sprite);
}

float Mario::getx() {
	return x;
}

float Mario::gety() {
	return y;
}

bool Mario::getdeath(){
	return dead;
}
void Mario::setdeath(bool b) {
	dead = b;
}
bool Mario::getwin() {
	return win;
}

void Mario::upgrade() {
	form = 1;
}
void Mario::degrade() {
	form = 0;
}
int Mario::getform() {
	return form;
}

void Mario::update(Map& map,std::vector<InsideQ>& v,sf::RenderWindow& window, std::vector<Goomba>& enemy) {
	if (x >= 3159) {//if you touch the flagpole, you win
		win = true;
		return;
	}
	if (!dead && y >= SCREEN_HEIGHT - 34 && form == 1 || y >= SCREEN_HEIGHT - 18) {//drop to the edge of the map, you loss.
		vertical_speed = -0.8;
		dead = true;
	}
	//draw the moving of enemies
	for (int i = 0; i < enemy.size(); i++) {
		if (enemy[i].getdeath()) continue;
		int	view_x = std::clamp<float>(x + 0.5f * (CELL_SIZE - SCREEN_WIDTH), 0, CELL_SIZE * map.size() - SCREEN_WIDTH);
		if (enemy[i].getx() >= view_x - 16 && enemy[i].getx() <= view_x + SCREEN_WIDTH + 16 && !enemy[i].getdeath()) {
			enemy[i].move(map);
			//if this Goomba is moving right, then check if there is a collision on the right
			//when a gommba move, the collision only happened between the nearest two Goomba which are alive
			//so just find the nearest alive one then check.
			if (enemy[i].getdirection()) {
				for (int j = i + 1; j < enemy.size(); j++) {
					if (!enemy[j].getdeath() && enemy[j].getx() - enemy[i].getx() <= 16 && enemy[j].gety() == enemy[i].gety()) {
						enemy[i].negetive_speed();
						enemy[j].negetive_speed();
					}
					break;
				}
			}
			else {
				for (int j = i -1; j >=0; j--) {
					if (!enemy[j].getdeath() && enemy[i].getx() - enemy[j].getx() <= 16 && enemy[j].gety() == enemy[i].gety()) {
						enemy[i].negetive_speed();
						enemy[j].negetive_speed();
					}
					break;
				}
			}
			enemy[i].draw(window);
			if (!dead) {                   
				//when drawing a Goomba, we just check if the mario or this goomba is dead by the way
				if (iskilled(x, y, enemy[i].getx(), enemy[i].gety(), form)) {
					enemy[i].setdeath(true);
					vertical_speed = -1.2;
					continue;
				}
				else if (isdead(x, y, enemy[i].getx(), enemy[i].gety(), form) && immortal_time <= 0) {
					vertical_speed = -1.2;
					if (form == 0) {
						dead = true;
					}
					else { 
						//if Mario is big, then turn it to small
						y += 16;
						immortal_time = 100;
						form = 0;
					}
				}
			}
		}
	}

	//if mario is dead, then draw the dead animation
	if (dead) {
		texture.loadFromFile("resources/mariodead.png");
		if (y < SCREEN_HEIGHT - 17) {
			y += vertical_speed;
			if (vertical_speed < MAX_VERTICAL_SPEED) {
				vertical_speed += 0.05;
			}
		}
	}
	else {
		//draw the twinkle and immortal when Mario eat a mushroom
		if (trans_timer > 0) {
			trans_timer--;
			immortal_time--;
			y = bigy + 16;
			sf::Image ima;
			ima.loadFromFile("resources/mariostand.png");
			if (trans_timer / 10 % 2 == 0) {
				y = bigy;
				ima.loadFromFile("resources/bigmariostand.png");
			}
			if (!direction) ima.flipHorizontally();
			texture.loadFromImage(ima);
			return;
		}
		//when you press left or right button then accelerate by POWER
		if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			direction = false;
			if (x + horizontal_speed < 0) {
				x = 0;
				horizontal_speed = 0;
				move_timer = 0;
				if (form == 0)texture.loadFromFile("Resources/mariostand.png");
				else if (form == 1) texture.loadFromFile("Resources/bigmariostand.png");
			}
			else if (right_collision(x + horizontal_speed, y, map) && (form == 0 || right_collision(x + horizontal_speed, y + 16, map))) {
				horizontal_speed = 0;
			}
			//moving when there is no collision
			else if (!left_collision(x + horizontal_speed, y, map) && (form == 0 || !left_collision(x + horizontal_speed, y + 16, map))) {
				x = x + horizontal_speed;
				sf::Image image;
				if (form == 0) {
					if (move_timer < 7) image.loadFromFile("Resources/mariomove1.png");  //the moving ani of the small
					else if (move_timer >= 7 && move_timer < 14) image.loadFromFile("Resources/Mariomove2.png");
					else image.loadFromFile("Resources/Mariomove3.png");
				}
				else if (form == 1) {
					if (move_timer < 7) image.loadFromFile("Resources/bigmariomove1.png");  //the moving ani of the big
					else if (move_timer >= 7 && move_timer < 14) image.loadFromFile("Resources/bigmariomove2.png");
					else image.loadFromFile("Resources/bigmariomove3.png");
				}
				image.flipHorizontally();
				texture.loadFromImage(image);
				move_timer++;
				move_timer = move_timer % 21;
				if (horizontal_speed - POWER > MAX_LEFT_SPEED)horizontal_speed -= POWER;
			}
		}
		//the right is just like the left
		else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			direction = true;
			if (x + horizontal_speed > CELL_SIZE * (map.size() - 1)) {
				x = CELL_SIZE * (map.size() - 1);
				horizontal_speed = 0;
				move_timer = 0;
				if (form == 0)texture.loadFromFile("Resources/mariostand.png");
				else if (form == 1) texture.loadFromFile("Resources/bigmariostand.png");
			}
			else if (left_collision(x + horizontal_speed, y, map) && (form == 0 || left_collision(x + horizontal_speed, y + 16, map))) {
				horizontal_speed = 0;
			}
			else if (!right_collision(x + horizontal_speed, y, map) && (form == 0 || !right_collision(x + horizontal_speed, y + 16, map))) {
				if (form == 0) {
					if (move_timer < 7) texture.loadFromFile("Resources/Mariomove1.png");
					else if (move_timer >= 7 && move_timer < 14) texture.loadFromFile("Resources/Mariomove2.png");
					else texture.loadFromFile("Resources/Mariomove3.png");
				}
				else {
					if (move_timer < 7) texture.loadFromFile("Resources/bigmariomove1.png");
					else if (move_timer >= 7 && move_timer < 14) texture.loadFromFile("Resources/bigmariomove2.png");
					else texture.loadFromFile("Resources/bigmariomove3.png");
				}
				move_timer++;
				move_timer = move_timer % 21;
				x = x + horizontal_speed;
				if (horizontal_speed + POWER < MAX_RIGHT_SPEED)horizontal_speed += POWER;
			}
		}
		//when not pression left or right button, then show down by FRICTION
		else if (horizontal_speed > 0) {  
			if (x + horizontal_speed < CELL_SIZE * (map.size() - 1)) {
				if (!right_collision(x + horizontal_speed, y, map) && (form == 0 || !right_collision(x + horizontal_speed, y + 16, map))) {//小的时候只需要前者，长大了需要后者
					x += horizontal_speed;
					horizontal_speed -= FRICTION;
					sf::Image image;
					if (form == 0)image.loadFromFile("Resources/marioflip.png");
					else image.loadFromFile("Resources/bigmarioflip.png");
					image.flipHorizontally();
					texture.loadFromImage(image);
					if (horizontal_speed < 0) {//when the speed is opposite, that means you have stopped
						horizontal_speed = 0;
						if (down_collision(x, y, map)) {
							sf::Image image;
							if (form == 0)image.loadFromFile("Resources/mariostand.png");
							else if(form == 1)image.loadFromFile("Resources/bigmariostand.png");
							image.flipHorizontally();
							texture.loadFromImage(image);
							direction = false;
						}
					}
				}
				else {
					horizontal_speed = 0;
				}
			}
			else {
				x = CELL_SIZE * (map.size() - 1);
				horizontal_speed = 0;
				if(form==1)texture.loadFromFile("Resources/mariostand.png");
				else texture.loadFromFile("Resources/bigmariostand.png");
			}
		}
		else if (horizontal_speed < 0) {//the left is just like the right
			if (x + horizontal_speed > 0) {
				if (!left_collision(x + horizontal_speed, y, map) && (form == 0 || !left_collision(x + horizontal_speed, y + 16, map))) {
					x += horizontal_speed;
					horizontal_speed += FRICTION;
					if(form==0)texture.loadFromFile("Resources/marioflip.png");
					else texture.loadFromFile("Resources/bigmarioflip.png");
					if (horizontal_speed > 0) {
						horizontal_speed = 0;//减速到0停下
						if (down_collision(x, y, map)) {
							direction = true;
						}
					}
				}
				else {
					horizontal_speed = 0;
				}
			}
			else {
				x = 0;
				horizontal_speed = 0;
			}
		}

		if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {  //jumpping!!!
			//you can only press jump button when you stand on the floor
			if (0 == vertical_speed && 1 == down_collision(x, y, map) && record_jump_timer == jump_timer && form == 0 || (0 == vertical_speed && 1 == down_collision(x, y + 16, map) && record_jump_timer == jump_timer && form == 1)) {
				vertical_speed = JUMP_SPEED;
				jump_timer = JUMP_TIMER;
				record_jump_timer = jump_timer;
				sf::Image image;
				if (form == 0) image.loadFromFile("Resources/mariojump.png");
				else image.loadFromFile("Resources/bigmariojump.png");
				if (0 == direction) image.flipHorizontally();
				texture.loadFromImage(image);
			}
			else if (jump_timer > 0 && record_jump_timer - jump_timer <= 1) {//the longer you press, the higher you jump
				vertical_speed = JUMP_SPEED;
				--jump_timer;
				record_jump_timer = jump_timer;
			}
		}
		//oops! you are falling
		if (vertical_speed >= 0) {
			if (1 == down_collision(x, y + vertical_speed, map) && form == 0 || (1 == down_collision(x, y + vertical_speed + 16, map) && form == 1)) {
				vertical_speed = 0;
				record_jump_timer = jump_timer;
				if (horizontal_speed == 0) { //oh shit, that was close, you fall on the ground safely
					if (direction) {
						if (form == 0)texture.loadFromFile("Resources/mariostand.png");
						else if (form == 1) texture.loadFromFile("Resources/bigmariostand.png");
					}
					else {
						sf::Image image;
						if(form==0)image.loadFromFile("Resources/mariostand.png");
						else if(form==1)image.loadFromFile("Resources/bigmariostand.png");
						image.flipHorizontally();
						texture.loadFromImage(image);
					}
				}
			}
			else {
				jump_timer--;
				vertical_speed = std::min<float>(vertical_speed + GRAVITY, MAX_VERTICAL_SPEED);
				y += vertical_speed;
				sf::Image image;
				if(form==0)image.loadFromFile("Resources/mariojump.png");
				else if(form==1)image.loadFromFile("Resources/bigmariojump.png");
				if (!direction) image.flipHorizontally();
				texture.loadFromImage(image);
			}
		}
		else if (vertical_speed < 0) {//oops!! you are flying!:) you jump up!
			if (y + vertical_speed < 0) {
				vertical_speed = 0;
				y = 0;
			}
			else if (0 == up_collision(x, y + vertical_speed, map)) {
				jump_timer--;
				vertical_speed = std::min<float>(vertical_speed + GRAVITY, MAX_VERTICAL_SPEED);
				y += vertical_speed;
				sf::Image image;
				if(form==0)image.loadFromFile("Resources/mariojump.png");
				else image.loadFromFile("Resources/bigmariojump.png");
				if (!direction) image.flipHorizontally();
				texture.loadFromImage(image);
			}
			else {
				int tmpx = floor(x / CELL_SIZE);
				int tmpy = floor((y + vertical_speed) / CELL_SIZE);
				//顶到questionblock之后将questionblock切换为被顶过的状态
				if (map[tmpx][tmpy] == Cell::QuestionBlock) {      
					map[tmpx][tmpy] = Cell::QuestionBlockChanged;
					//	map[tmpx][tmpy - 1] = Cell::Coin;
					activate(v, tmpx * CELL_SIZE, tmpy * CELL_SIZE);

					recordx = tmpx;
					recordy = tmpy - 1;
					//	coin_timer = 15;
				}
				else if (tmpx + 1 < map.size() && map[tmpx + 1][tmpy] == Cell::QuestionBlock) {
					map[tmpx + 1][tmpy] = QuestionBlockChanged;
					//	map[tmpx + 1][tmpy - 1] = Cell::Coin;
					activate(v, (tmpx + 1) * CELL_SIZE, tmpy * CELL_SIZE);
					recordx = tmpx + 1;
					recordy = tmpy - 1;
					//coin_timer = 15;
				}
				jump_timer = 0;
				vertical_speed = 0;
			}
		}
	}

	//画蘑菇的移动
	for (int i = 0; i < v.size();i++) {
		if (v[i].getkick()) {
			if (v[i].getform()) {
				v[i].MushroomMove(map,x,y);
				if (!v[i].getkick()&&!form) {
					form = 1;
					y -= 16.5;
					bigy = y;
					trans_timer = 100;
					immortal_time = 100;
				}
				v[i].draw(window);
			}
			else {
				v[i].CoinMove();
				v[i].draw(window);
			}
		}
	}

	//无敌时间闪烁
	if (immortal_time > 0) {
		immortal_time--;
		if (immortal_time / 10 % 2 == 0) {
			texture.loadFromFile("resources/blank.png");
		}
	}
}

//激活某个question方块
void Mario::activate(std::vector<InsideQ>& v, float x, float y) {
	for (int i = 0;i < v.size();i++) {
		if (v[i].getx() == x && v[i].gety() == y) {
			v[i].setkick();
			break;
		}
	}
}

//画出胜利的动画
void Mario::drawwin(Map& map, sf::RenderWindow& window, int& flag) {
	if (form == 1)texture.loadFromFile("resources/bigmariowin.png");
	else if (form == 0)texture.loadFromFile("resources/littlemariowin.png");
	if (flag >= 8) {//旗子没升到顶时升旗子
		flag -= 0.4;
		sf::Texture t;
		sf::Sprite s;
		t.loadFromFile("resources/flag.png");
		s.setTexture(t);
		s.setPosition(3160, flag);
		map[197][11] = Cell::Empty;
		window.draw(s);
		draw(window);
		vertical_speed = -MAX_VERTICAL_SPEED;
		horizontal_speed = MAX_RIGHT_SPEED;
		jump_timer = 40;
		return;
	}
	else {
		sf::Texture t;
		sf::Sprite s;
		t.loadFromFile("resources/flag.png");
		s.setTexture(t);
		s.setPosition(3160, flag);
		window.draw(s);
		if (jump_timer > 0) {//升完旗后有一个小延迟之后马里奥跳起来
			jump_timer--;
		}
		else if (0 == down_collision(x, y + vertical_speed, map) && form == 0 || (0 == down_collision(x, y + vertical_speed + 16, map) && form == 1)) {  //跳起来的mario
			x += horizontal_speed;
			y += vertical_speed;
			if (vertical_speed < MAX_VERTICAL_SPEED)vertical_speed += GRAVITY;
			else vertical_speed = MAX_VERTICAL_SPEED;
			if (form)texture.loadFromFile("resources/bigmariojump.png");
			if (!form)texture.loadFromFile("resources/mariojump.png");
			draw(window);
			record_jump_timer = 40;
		}
		else {//落地之后
			if (record_jump_timer > 0) {
				record_jump_timer--;
				if (!form)texture.loadFromFile("resources/mariostand.png");
				else texture.loadFromFile("resources/bigmariostand.png");
			}
			else {
				if (!form)texture.loadFromFile("resources/pose.png");
				else texture.loadFromFile("resources/bigpose.png");
				sf::Texture text;
				sf::Sprite sp;
				text.loadFromFile("resources/youwin.png");
				sp.setTexture(text);
				sp.setPosition(x - SCREEN_WIDTH / 2, y - SCREEN_HEIGHT / 2);
				window.draw(sp);
			}
		}
	}
}