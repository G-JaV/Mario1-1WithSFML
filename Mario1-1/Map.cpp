#include"Map.h"

//draw a map from the map vector
void drawMap(short view_x, sf::RenderWindow& window, const Map& map) {
	sf::Texture texture;
	sf::Sprite cell_sprite;
	texture.loadFromFile("Resources/wall.png");
	cell_sprite.setTexture(texture);
	short map_begin = floor(view_x / static_cast<float>(CELL_SIZE));
	short map_end = map_begin+18;
	float deviation = view_x - static_cast<float>(map_begin * CELL_SIZE);
	for (unsigned short a = map_begin; a <= map_end; a++) {
		for (unsigned short b = 0; b < map[a].size(); b++) {
			if (Cell::Empty == map[a][b]) {
				continue;
			}
			else if (Cell::Coin == map[a][b]) {
				texture.loadFromFile("Resources/coin.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a , CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::Brick == map[a][b]) {
				texture.loadFromFile("Resources/brick.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::QuestionBlock == map[a][b]) {
				texture.loadFromFile("Resources/questionblock.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::QuestionBlockChanged == map[a][b]) {
				texture.loadFromFile("Resources/questionblockchanged.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::Pipe1 == map[a][b]) {
				texture.loadFromFile("Resources/pipe1.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::Pipe2 == map[a][b]) {
				texture.loadFromFile("Resources/pipe2.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::Pipe3 == map[a][b]) {
				texture.loadFromFile("Resources/pipe3.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::Pipe4 == map[a][b]) {
				texture.loadFromFile("Resources/pipe4.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
			else if (Cell::FlagPole == map[a][b]) {
				texture.loadFromFile("resources/flagpole.png");
				sf::Sprite tmp;
				tmp.setTexture(texture);
				tmp.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(tmp);
			}
			else if (Cell::Flag == map[a][b]) {
				texture.loadFromFile("resources/flag.png");
				sf::Sprite tmp;
				tmp.setTexture(texture);
				tmp.setPosition(CELL_SIZE * a + 8 , CELL_SIZE * b);
				window.draw(tmp);
			}
			else{
				texture.loadFromFile("Resources/wall.png");
				cell_sprite.setTexture(texture);
				cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);
				window.draw(cell_sprite);
			}
		}
	}
}

//convert map_sketch to enemies,map and what`s inside a questionbox
void convert_sketch(Map& map, sf::Image map_sketch, std::vector<InsideQ>& v, std::vector<Goomba>& enemy)
{
	unsigned short map_height;

	map_height = floor(map_sketch.getSize().y/ 3.f);

	for (unsigned short a = 0; a < map.size(); a++)
	{
		for (unsigned short b = 0; b < map[0].size(); b++)
		{
			sf::Color pixel = map_sketch.getPixel(a, b);

			if (b < map_height)
			{
				if (sf::Color(182, 73, 0) == pixel)
				{
					map[a][b] = Cell::Brick;
				}
				else if (sf::Color(255, 255, 0) == pixel)
				{
					map[a][b] = Cell::Coin;
				}
				else if (sf::Color(0, 146, 0) == pixel)
				{
					map[a][b] = Cell::Pipe1;
				}
				else if (sf::Color(0, 166, 0) == pixel)
				{
					map[a][b] = Cell::Pipe2;
				}
				else if (sf::Color(56, 255, 6) == pixel)
				{
					map[a][b] = Cell::Pipe3;
				}
				else if (sf::Color(6, 255, 124) == pixel)
				{
					map[a][b] = Cell::Pipe4;
				}
				else if (sf::Color(255, 73, 85) == pixel || sf::Color(255, 146, 85) == pixel)
				{
					map[a][b] = Cell::QuestionBlock;
					if (sf::Color(255, 73, 85) == pixel) {
						InsideQ q(a*CELL_SIZE, b*CELL_SIZE, true);
						v.emplace_back(q);
					}
					else {
						InsideQ q(a * CELL_SIZE, b * CELL_SIZE, false);
						v.emplace_back(q);
					}
				}
				else if (sf::Color(0, 0, 0) == pixel || sf::Color(146, 73, 0) == pixel)
				{
					map[a][b] = Cell::Wall;
				}
				else if (sf::Color(119, 48, 0) == pixel) {
					Goomba g(a * CELL_SIZE, b * CELL_SIZE);
					enemy.emplace_back(g);
				}
				else if (sf::Color(0, 255, 255) == pixel) {
					map[a][b] = Cell::FlagPole;
				}
				else if (sf::Color(127, 127, 127) == pixel) {
					map[a][b] = Cell::Flag;
				}
				else
				{
					map[a][b] = Cell::Empty;
				}
			}
		}
	}
}
