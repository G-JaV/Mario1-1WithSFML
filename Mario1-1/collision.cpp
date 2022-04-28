#include"collision.h"
//�ĸ������ϵ���ײ�ж�
bool down_collision(float x, float y, const Map& map) {
	if (y > SCREEN_HEIGHT - 32) {
		return false;
	}
	if (map[0].size() * CELL_SIZE - y <= 0.001) return true;
	int tmpx = ceil(x / CELL_SIZE);
	int tmpy = ceil(y / CELL_SIZE);
	if (map[tmpx][tmpy] != Cell::Empty && map[tmpx][tmpy] != Cell::Coin || (tmpx - 1 > 0 && map[tmpx - 1][tmpy] != Cell::Empty && map[tmpx - 1][tmpy] != Cell::Coin)) return true;
	return false;
}
bool up_collision(float x, float y, const Map& map) {
	if (y - 0 <= 0.001) return true;
	int tmpx = floor(x / CELL_SIZE);
	int tmpy = floor(y / CELL_SIZE);
	if (map[tmpx][tmpy] != Cell::Empty && map[tmpx][tmpy] != Cell::Coin || (tmpx + 1 < map.size() && map[tmpx + 1][tmpy] != Cell::Empty && map[tmpx + 1][tmpy] != Cell::Coin)) return true;
	return false;
}
bool left_collision(float x, float y, const Map& map) {
	int tmpy = floor(y / CELL_SIZE);
	int tmpx = floor(x / CELL_SIZE);
	float tmp = y / CELL_SIZE;
	if (map[tmpx][tmpy] != Cell::Empty && map[tmpx][tmpy] != Cell::Coin) return true;
	else if (tmpy + 1 < map[0].size() && (map[tmpx][tmpy + 1] != Cell::Empty && map[tmpx][tmpy + 1] != Cell::Coin) && tmp - tmpy > 0.01) return true;
	return false;
}
bool right_collision(float x, float y, const Map& map) {
	int tmpy = floor(y / CELL_SIZE);
	int tmpx = ceil(x / CELL_SIZE);
	float tmp = y / CELL_SIZE;
	if (map[tmpx][tmpy] != Cell::Empty && map[tmpx][tmpy] != Cell::Coin) return true;
	else if (tmpy + 1 < map[0].size() && (map[tmpx][tmpy + 1] != Cell::Empty && map[tmpx][tmpy + 1] != Cell::Coin) && tmp - tmpy > 0.01) return true;
	return false;
}

bool isdead(float mariox, float marioy, float goombax, float goombay, int form) {
	if (form) {   //��mario�����
		if (goombax - mariox < 15 && goombax - mariox > 0 && marioy - goombay<8 && marioy - goombay>-31) {//��mario������������ٶȴ���0������������������
			return true;
		}
		else if (mariox - goombax >= 0 && mariox - goombax < 15 && marioy - goombay<8 && marioy - goombay>-31) {//��mario���Ҳ�������������������
			return true;
		}
		else {
			return false;
		}
	}
	//Сmario�����
	if (goombax - mariox < 15 && goombax - mariox > 0 && marioy - goombay<8 && marioy - goombay>-15) {//mario������������ٶȴ���0������������������
		return true;
	}
	else if (mariox - goombax >= 0 && mariox - goombax < 15 && marioy - goombay<8 && marioy - goombay>-15) {//mario���Ҳ�������������������
		return true;
	}
	else {
		return false;
	}
}

bool iskilled(float mariox, float marioy, float goombax, float goombay,int form) {
	if (form) {//��mario�����
		if (abs(mariox - goombax) <= 15 && goombay - marioy >= 29 && goombay - marioy <= 35) {
			return true;
		}
		else {
			return false;
		}
	}
	//Сmario�����
	if (abs(mariox - goombax) <= 15 && goombay - marioy >= 15 && goombay - marioy <= 17) {
		return true;
	}
	else {
		return false;
	}
}
