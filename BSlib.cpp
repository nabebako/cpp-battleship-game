#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <unistd.h>

#include "BS_lib.hpp"

void pause(const double& secs) { usleep(secs * 1000000); }



void Space::add_space(const std::vector<int>& x, const std::vector<int>& y)
{
    for (int i = 0; i < x.size(); i++) { Space::x.push_back(x[i]); }
    for (int i = 0; i < y.size(); i++) { Space::y.push_back(y[i]); }
}


Board::Board(const int& length, const int& with)
{
    board_length = length;
    board_with = with;
}


void Board::render_board()
{
    for (int i = 0; i < board_with; i++)
    {
        std::cout << std::endl;
        for (int x = 0; x < board_length; x++) { std::cout << map[i][x] << " "; }
    }
    std::cout << std::endl;
}

void Board::edit_board(int& edit_x, int& edit_y)
{
    edit_x -= 1;
    edit_y = board_with - edit_y;
    map[edit_y][edit_x] = '-';
}

void Board::edit_hit_board(int& edit_x, int& edit_y)
{
    edit_x -= 1;
    edit_y = board_with - edit_y;
    map[edit_y][edit_x] = 'x';
}

void Board::edit_time_up_board()
{
    srand((unsigned)time(NULL));
    int edit_x;
    int edit_y;
    for (int i = 0; i < 10; i++)
    {
        edit_x = (rand() % board_length);
        edit_y = (rand() % board_with);
        map[edit_y][edit_x] = '+';
    }
}



void Target::dammage() { if (health <= 0) { is_destroyed = true; } }



T1::T1(const int& limit_x, const int& limit_y, Space& space)
{
    is_destroyed = false;
    locate( limit_x, limit_y, space);
    space.add_space({x1},{y1});
}

void T1::locate(const int& limit_x, const int& limit_y, const Space& invalid)
{
    int step = 0;
    
    srand((unsigned)time(NULL));
    
    while (step == 0)
    {
        x1 = (rand() % limit_x) + 1;
        y1 = (rand() % limit_y) + 1;
        for (int i = 0; i < invalid.x.size(); i++)
        {
            if (x1 == invalid.x[i] && y1 == invalid.y[i]) { step = 0;  break; }
            else { step = 1; }
        }
        if (step == 1) { break; }
    }
}

bool T1::hit (const int& shot_x, const int& shot_y)
{
    if (shot_x == x1 && shot_y == y1)
    { is_destroyed = true;  return true; }
    else { return false; }
}



T2::T2(const int& limit_x, const int& limit_y, Space& space)
{
    health = 2;
    is_destroyed = false;
    locate(limit_x, limit_y, space);
    space.add_space({x1,x2},{y1,y2});
}

void T2::locate(const int& limit_x, const int& limit_y, const Space& invalid)
{
    int step = 0;
    unsigned rotation;
    
    srand((unsigned)time(NULL));
    
    while (step == 0)
    {
        rotation = rand() % 1;
        x1 = (rand() % limit_x) + 1;
        y1 = (rand() % limit_y) + 1;
        for (int i = 0; i < invalid.x.size(); i++)
        {
            if (x1 == invalid.x[i] && y1 == invalid.y[i]) { step = 0;  break; }
            else { step = 1;}
        }
        if (step == 1 && rotation == 0 /* horizontal */)
        {
            y2 = y1;
            x2 = x1 + 1;
            for (int i = 0; i < invalid.x.size(); i++)
            {
                if (x2 == invalid.x[i]) { step = 1;  break; }
                else { step = 2; }
            }
            if (step == 1) {
                x2 = x1 - 1;
                for (int i = 0; i < invalid.x.size(); i++)
                {
                    if (x2 == invalid.x[i]) { step = 0;  break; }
                    else { step = 2;}
            }}
             if (step == 2) { break; }
        }
        if (step == 1 && rotation == 1 /* vertical */)
        {
            x2 = x1;
            y2 = y1 + 1;
            for (int i = 0; i < invalid.y.size(); i++)
            {
                if (y2 == invalid.y[i]) { step = 1;  break; }
                else { step = 2; }
            }
            if (step == 1)
            {
                y2 = y1 - 1;
                for (int i = 0; i < invalid.y.size(); i++)
                {
                    if (y2 == invalid.y[i]) { step = 0;  break; }
                    else { step = 2; }
            }}
            if (step == 2) { break; }
    }}
}

bool T2::hit(const int& shot_x, const int& shot_y)
{
    bool x_id = true;
    bool y_id = true;
    bool id;
    for (int i = 0; i < hit_x.size(); i++)
    {
        if (shot_x == hit_x[i]) { x_id = false;  break; }
    }
    for (int i = 0; i < hit_y.size(); i++)
    {
        if (shot_y == hit_y[i]) { y_id = false;  break; }
    }
    id = x_id || y_id;
    if (((shot_x == x1 && shot_y == y1) || (shot_x == x2 && shot_y == y2)) && id)
    {
        health -= 1;
        dammage();
        hit_x.push_back(shot_x);
        hit_y.push_back(shot_y);
        return true;
    }
    else { return false; }
}



T3::T3(const int& limit_x, const int& limit_y, Space& space)
{
    health = 3;
    is_destroyed = false;
    locate( limit_x, limit_y, space);
    space.add_space({x1,x2,x3},{y1,y2,y3});
}

void T3::locate(const int& limit_x,const int& limit_y, const Space& invalid)
{
    int step = 0;
    unsigned rotation;
    
    srand((unsigned)time(NULL));
    
    while (step == 0)
    {
        rotation = rand() % 1;
        x1 = (rand() % limit_x) + 1;
        y1 = (rand() % limit_y) + 1;
        for (int i = 0; i < invalid.x.size(); i++)
        {
            if (x1 == invalid.x[i] && y1 == invalid.x[i]) { step = 0;  break; }
            else { step = 1; }
        }
        if (rotation == 0 /* horizontal */)
        {
            if (step == 1)
            {
                y2 = y1;
                y3 = y1;
                x2 = x1 + 1;
                for (int i = 0; i < invalid.x.size(); i++)
                {
                    if (x2 == invalid.x[i]) { step = 1;  break; }
                    else { step = 2; }
                }
                if (step == 1)
                {
                    x2 = x1 - 1;
                    for (int i = 0; i < invalid.x.size(); i++)
                    {
                        if (x2 == invalid.x[i]) { step = 0;  break; }
                        else { step = 2; }
            }}}
            if (step == 2)
            {
                if (x2 - 1 == x1)
                {
                    x3 = x1 + 2;
                    for (int i = 0; i < invalid.x.size(); i++)
                    {
                        if (x3 == invalid.x[i]) { step = 2;  break; }
                        else { step = 3; }
                    }
                    if (step == 2)
                    {
                        x3 = x1 - 1;
                        for (int i = 0; i < invalid.x.size(); i++)
                        {
                            if (x3 == invalid.x[i]) { step = 2;  break; }
                            else { step = 3; }
                }}}
                else if (x2 + 1 == x1)
                {
                    x3 = x1 - 2;
                    for (int i = 0; i < invalid.x.size(); i++)
                    {
                        if (x3 == invalid.x[i]) { step = 2;  break; }
                        else { step = 3; }
                    }
                    if (step == 2)
                    {
                        x3 = x1 + 1;
                        for (int i = 0; i < invalid.x.size(); i++)
                        {
                            if (x3 == invalid.x[i]) { step = 0;  break; }
                            else { step = 3; }
            }}}}
            if (step == 3) { break; }
        }
        if (rotation == 1 /* vertical */)
        {
            if (step == 1)
            {
                x2 = x1;
                x3 = x1;
                y2 = y1 + 1;
                for (int i = 0; i < invalid.y.size(); i++)
                {
                    if (y2 == invalid.y[i]) { step = 1;  break; }
                    else { step = 2; }
                }
                if (step == 1)
                {
                    y2 = y1 - 1;
                    for (int i = 0; i < invalid.y.size(); i++)
                    {
                        if (y2 == invalid.y[i]) { step = 0;  break; }
                        else { step = 2; }
            }}}
            if (step == 2)
            {
                if (y2 - 1 == y1)
                {
                    y3 = y1 + 2;
                    for (int i = 0; i < invalid.x.size(); i++)
                    {
                        if (x3 == invalid.x[i]) { step = 2;  break; }
                        else { step = 3; }
                    }
                    if (step == 2)
                    {
                        y3 = y1 - 1;
                        for (int i = 0; i < invalid.x.size(); i++)
                        {
                            if (y3 == invalid.x[i]) { step = 2;  break; }
                            else { step = 3; }
                }}}
                else if (y2 + 1 == y1)
                {
                    y3 = y1 - 2;
                    for (int i = 0; i < invalid.x.size(); i++)
                    {
                        if (x3 == invalid.x[i]) { step = 2;  break; }
                        else { step = 3; }
                    }
                    if (step == 2)
                    {
                        y3 = y1 + 1;
                        for (int i = 0; i < invalid.x.size(); i++)
                        {
                            if (y3 == invalid.x[i]) { step = 2;  break; }
                            else { step = 3; }
            }}}}
            if (step == 3) { break; }
    }}
}

bool T3::hit(const int& shot_x, const int& shot_y)
{
    bool x_id = true;
    bool y_id = true;
    bool id;
    for (int i = 0; i < hit_x.size(); i++)
    {
        if (shot_x == hit_x[i]) { x_id = false;  break; }
    }
    for (int i = 0; i < hit_y.size(); i++)
    {
        if (shot_y == hit_y[i]) { y_id = false;  break; }
    }
    id = x_id || y_id;
    if (((shot_x == x1 && shot_y == y1) || (shot_x == x2 && shot_y == y2) || (shot_x == x3 && shot_y == y3)) && id)
    {
        health -= 1;
        dammage();
        hit_x.push_back(shot_x);
        hit_y.push_back(shot_y);
        return true;
    }
    else { return false; }
}


