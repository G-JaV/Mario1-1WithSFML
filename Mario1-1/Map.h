#pragma once
#include"Mario.h"

void drawMap(short view_x, sf::RenderWindow& window, const Map& map);
void convert_sketch(Map& map, sf::Image map_sketch, std::vector<InsideQ>& v, std::vector<Goomba>& enemy);
