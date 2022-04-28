#include<vector>
#include<algorithm>
#include<iostream>
#include"Mario.h"
#include"Map.h"
#include"insideQuestion.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mario");
	Mario m;
	std::vector<Cell> v(15);
	//Map map(211,v);
	Map map(211, v);
	short view_x;
	sf::Image map_sketch;
	std::vector<InsideQ> hiden;
	std::vector<Goomba> enemy;
	sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	map_sketch.loadFromFile("Resources/LevelSketch0.png");
	convert_sketch(map, map_sketch, hiden, enemy);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Color(92,242,254));
		view_x = std::clamp<float>(m.getx() + 0.5f * (CELL_SIZE - SCREEN_WIDTH), 0, CELL_SIZE * map.size() - SCREEN_WIDTH);
		view.reset(sf::FloatRect(view_x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
		m.update(map, hiden, window, enemy);
		while (m.getdeath() && abs(SCREEN_HEIGHT - m.gety() <= 18)) {//if Mario dead,then it goes in here
			window.clear(sf::Color::Color(92, 242, 254));
			sf::Texture text;
			sf::Sprite sp;
			text.loadFromFile("resources/fail.png");
			sp.setTexture(text);
			sp.setPosition(view_x+50, 50);
			window.draw(sp);
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed)
					window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) == 1) { //if P is pressed then restart
				hiden.clear();
				enemy.clear();
				convert_sketch(map, map_sketch, hiden, enemy);
				Mario tmpm;
				m = tmpm;
				view_x = std::clamp<float>(m.getx() + 0.5f * (CELL_SIZE - SCREEN_WIDTH), 0, CELL_SIZE * map.size() - SCREEN_WIDTH);
				view.reset(sf::FloatRect(view_x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
				window.clear(sf::Color::Color(92, 242, 254));
				m.setdeath(false);
				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) == 1) {//if Q is pressed then shut down
				window.close();
				return 0;
			}
			drawMap(view_x, window, map);
			m.draw(window);
			window.setView(view);
			window.display();
		}
		int flag = 160;
		while (m.getwin()) {  //if you win, then it goes in here
			window.clear(sf::Color::Color(92, 242, 254));
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					window.close();
					return 0;
				}
			}
			m.drawwin(map, window,flag);
			drawMap(view_x, window, map);
			m.draw(window);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) == 1) {//waiting for the button you pressed 
				hiden.clear();
				enemy.clear();
				convert_sketch(map, map_sketch, hiden, enemy);
				Mario tmpm;
				m = tmpm;
				view_x = std::clamp<float>(m.getx() + 0.5f * (CELL_SIZE - SCREEN_WIDTH), 0, CELL_SIZE * map.size() - SCREEN_WIDTH);
				view.reset(sf::FloatRect(view_x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
				window.clear(sf::Color::Color(92, 242, 254));
				m.setdeath(false);
				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) == 1) {
				window.close();
				return 0;
			}
			window.setView(view);
			window.display();
		}
		drawMap(view_x, window, map);
		m.draw(window);
		window.setView(view);
		window.display();
	}
}