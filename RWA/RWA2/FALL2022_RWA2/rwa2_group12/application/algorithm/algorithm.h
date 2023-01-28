#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#pragma once

#include<iostream>
#include<memory>
#include<array>
#include"../simulator/simulator.h"


namespace rwa2group12 {
/**
* @brief This class implements the search algorithm.
*/
class Algorithm {
public:
// initialize outer walls, generate goal, execute search algorithm, etc
void run();
// color outer walls
void init_outer_walls();
// algorithm for left-hand rule approach
void follow_wall_left();
// algorithm for right-hand rule approach
void follow_wall_right();
// generate random goal adjacent to an outer wall
void generate_goal();
// set right wall in m_maze and in simulator
void set_right_wall(int x, int y, char d);
// set left wall in m_maze and in simulator
void set_left_wall(int x, int y, char d);
// set front wall in m_maze and in simulator
void set_front_wall(int x, int y, char d);

void set_maze_height(){
    m_maze_height=Simulator::mazeHeight();
}

void set_maze_width(){
    m_maze_width=Simulator::mazeWidth();
}


private:
std::pair<int, int> goal;
int m_maze_height;
int m_maze_width;
};
} // namespace rwa2group12

#endif