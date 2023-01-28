#include "../simulator/simulator.h"
#include "../robot/robot.h"
#include "algorithm.h"

#include <vector>
#include <array>
#include <time.h>
#include <cstdlib>


void rwa2group12::Algorithm::init_outer_walls()
{
    set_maze_height();
    set_maze_width();

    for (int i = 0; i < m_maze_width; i++)
    {
        Simulator::setWall(i, 0, 's');
        Simulator::setWall(i, m_maze_height - 1, 'n');
    }

    for (int i = 0; i < m_maze_height; i++)
    {
        Simulator::setWall(0, i, 'w');
        Simulator::setWall(m_maze_width - 1, i, 'e');
    }
}


void rwa2group12::Algorithm::run()
{
    init_outer_walls();
    generate_goal();
    follow_wall_right();
}


void rwa2group12::Algorithm::set_right_wall(int x, int y, char d)
{
    if (Simulator::wallRight())
    {
        if (d == 'n')
        {
            Simulator::setWall(x, y, 'e');
        }
        else if (d == 'e')
        {
            Simulator::setWall(x, y, 's');
        }
        else if (d == 's')
        {
            Simulator::setWall(x, y, 'w');
        }
        else
        {
            Simulator::setWall(x, y, 'n');
        }
    }
}


void rwa2group12::Algorithm::set_left_wall(int x, int y, char d)
{
    if (Simulator::wallLeft())
    {
        if (d == 'n')
        {
            Simulator::setWall(x, y, 'w');
        }
        else if (d == 'e')
        {
            Simulator::setWall(x, y, 'n');
        }
        else if (d == 's')
        {
            Simulator::setWall(x, y, 'e');
        }
        else
        {
            Simulator::setWall(x, y, 's');
        }
    }
}


void rwa2group12::Algorithm::set_front_wall(int x, int y, char d)
{
    if (Simulator::wallFront())
    {
        if (d == 'n')
        {
            Simulator::setWall(x, y, 'n');
        }
        else if (d == 'e')
        {
            Simulator::setWall(x, y, 'e');
        }
        else if (d == 's')
        {
            Simulator::setWall(x, y, 's');
        }
        else
        {
            Simulator::setWall(x, y, 'w');
        }
    }
}


void rwa2group12::Algorithm::follow_wall_right()
{
    auto robot = std::make_unique<rwa2group12::Robot>();
    int x=0;
    int y=0;


    std::cerr<<"TURN RIGHT ALGORITHM: "<<std::endl;
    std::cerr<<"Goal: "<<goal.first+1<<" "<<goal.second+1<<std::endl;
    while (x!=goal.first || y!=goal.second)
    {   
        set_right_wall(x, y, robot->get_direction());
        set_left_wall(x, y, robot->get_direction());
        set_front_wall(x, y, robot->get_direction());
        Simulator::setColor(x, y, 'c');
        if (!Simulator::wallRight())
        {
            std::cerr << "Turning Right !!!" << std::endl;
            robot->turn_right();
            robot->move_forward();
            if (robot->get_direction()=='n'){
                robot->set_direction('e');
                x++;
            }else if (robot->get_direction()=='e'){
                robot->set_direction('s');
                y--;
            }else if (robot->get_direction()=='s'){
                robot->set_direction('w');
                x--;
            }else if (robot->get_direction()=='w'){
                robot->set_direction('n');
                y++;
            }
            robot->set_position(x, y);

        }
        else if (!Simulator::wallFront())
        {
            std::cerr << "Moving Front !!!" << std::endl;
            if (robot->get_direction()=='n'){
                y++;
            }else if (robot->get_direction()=='e'){
                x++;
            }else if (robot->get_direction()=='s'){
                y--;
            }else if (robot->get_direction()=='w'){
                x--;
            }
            robot->move_forward();
            robot->set_position(x, y);
        }
        else if (!Simulator::wallLeft())
        {
            std::cerr << "Turning Left !!!" << std::endl;
            robot->turn_left();
            robot->move_forward();
            if (robot->get_direction()=='n'){
                robot->set_direction('w');
                x--;
            }else if (robot->get_direction()=='e'){
                robot->set_direction('n');
                y++;
            }else if (robot->get_direction()=='s'){
                robot->set_direction('e');
                x++;
            }else if (robot->get_direction()=='w'){
                robot->set_direction('s');
                y--;
            }
            robot->set_position(x, y);
        }
        else
        {
            std::cerr << "Turning around !!!" << std::endl;
            robot->turn_right();
            robot->turn_right();
            if (robot->get_direction()=='n'){
                robot->set_direction('s');
            }else if (robot->get_direction()=='e'){
                robot->set_direction('w');
            }else if (robot->get_direction()=='s'){
                robot->set_direction('n');
            }else if (robot->get_direction()=='w'){
                robot->set_direction('e');
            }
            robot->set_position(x, y);
        }
    }
}


void rwa2group12::Algorithm::follow_wall_left()
{
    auto robot = std::make_unique<rwa2group12::Robot>();
    int x=0;
    int y=0;

    std::cerr<<"TURN LEFT ALGORITHM: "<<std::endl;
    std::cerr<<"Goal: "<<goal.first+1<<" "<<goal.second+1<<std::endl;
    while (x!=goal.first || y!=goal.second)
    {
        set_right_wall(x, y, robot->get_direction());
        set_left_wall(x, y, robot->get_direction());
        set_front_wall(x, y, robot->get_direction());
        Simulator::setColor(x, y, 'c');
        if (!Simulator::wallLeft())
        {
            std::cerr << "Turning Left !!!" << std::endl;
            robot->turn_left();
            robot->move_forward();
            if (robot->get_direction()=='n'){
                robot->set_direction('w');
                x--;
            }else if (robot->get_direction()=='e'){
                robot->set_direction('n');
                y++;
            }else if (robot->get_direction()=='s'){
                robot->set_direction('e');
                x++;
            }else if (robot->get_direction()=='w'){
                robot->set_direction('s');
                y--;
            }
            robot->set_position(x, y);
        }
        else if (!Simulator::wallFront())
        {
            std::cerr << "Moving Front !!!" << std::endl;
            if (robot->get_direction()=='n'){
                y++;
            }else if (robot->get_direction()=='e'){
                x++;
            }else if (robot->get_direction()=='s'){
                y--;
            }else if (robot->get_direction()=='w'){
                x--;
            }
            robot->move_forward();
            robot->set_position(x, y);
        }
        else if (!Simulator::wallRight())
        {
            std::cerr << "Turning Right !!!" << std::endl;
            robot->turn_right();
            robot->move_forward();
            if (robot->get_direction()=='n'){
                robot->set_direction('e');
                x++;
            }else if (robot->get_direction()=='e'){
                robot->set_direction('s');
                y--;
            }else if (robot->get_direction()=='s'){
                robot->set_direction('w');
                x--;
            }else if (robot->get_direction()=='w'){
                robot->set_direction('n');
                y++;
            }
            robot->set_position(x, y);
        }
        else
        {
            std::cerr << "Turning around !!!" << std::endl;
            robot->turn_right();
            robot->turn_right();
            if (robot->get_direction()=='n'){
                robot->set_direction('s');
            }else if (robot->get_direction()=='e'){
                robot->set_direction('w');
            }else if (robot->get_direction()=='s'){
                robot->set_direction('n');
            }else if (robot->get_direction()=='w'){
                robot->set_direction('e');
            }
            robot->set_position(x, y);
        }
    }
}


void rwa2group12::Algorithm::generate_goal()
{
    srand((unsigned)time(NULL));
    int y = std::rand() % 16;
    if (y == 0 || y == 15)
    {
        int x = std::rand() % 16;
        goal.first=x;
        Simulator::setColor(x, y, 'R');
        Simulator::setText(x, y, "G");
    }
    else
    {
        std::array<int, 2> g{0, 15};
        int x = g.at(std::rand() % 2);
        goal.first=x;
        Simulator::setColor(x, y, 'R');
        Simulator::setText(x, y, "G");
    }
    goal.second=y;
}
