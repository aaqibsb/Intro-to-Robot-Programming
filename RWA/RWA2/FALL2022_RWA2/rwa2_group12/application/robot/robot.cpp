#include "../simulator/simulator.h"
#include "robot.h"


void rwa2group12::Robot::turn_left(){
    Simulator::turnLeft();
}

void rwa2group12::Robot::turn_right(){
    Simulator::turnRight();
}

void rwa2group12::Robot::move_forward(){
    Simulator::moveForward();
}

void rwa2group12::Robot::set_position(int x, int y){
    m_position.first=x;
    m_position.second=y;
}

void rwa2group12::Robot::set_direction(char d){
    m_direction=d;
}