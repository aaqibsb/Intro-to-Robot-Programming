#ifndef __ROBOT_H__
#define __ROBOT_H__

#pragma once

#include<iostream>
#include<array>

namespace rwa2group12 {
class Robot {
public:
void turn_left();
void turn_right();
void move_forward();
std::pair<int, int> get_position(){return m_position;}
char get_direction(){return m_direction;}
void set_position(int x, int y);
void set_direction(char d);
private:
std::pair<int, int> m_position;
char m_direction{'n'};
};
} // namespace rwa2group12

#endif