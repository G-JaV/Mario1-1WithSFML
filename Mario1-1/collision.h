#pragma once
#include"totalsettings.h"
bool down_collision(float x, float y, const Map& map);
bool left_collision(float x, float y, const Map& map);
bool right_collision(float x, float y, const Map& map);
bool up_collision(float x, float y, const Map& map);
bool isdead(float mariox, float marioy, float goombax, float goombay, int form);//�ж�������Ƿ���Ϊ������������
bool iskilled(float mariox, float marioy, float goombax, float goombay, int form);//�ж�������Ƿ��������
