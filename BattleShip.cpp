#include <iostream>
#include <vector>
#include <ctime>

#include "BS_lib.hpp"

std::string dialog();


int main()
{
    int size = 0;
    std::cout << "Board size: ";
    while (size < 4) { std::cin >> size; }
    Board map(size,size);
    if (!map.init_board()) { exit(1); }
    Space invalid;
    invalid.add_space( {size + 1, 0} , {size + 1, 0} );
    T3 omega_1 (size, size, invalid);
    T2 delta_1 (size, size, invalid);
    T1 alpha_1(size, size, invalid);
    T1 alpha_2(size, size, invalid);
    T1 alpha_3(size, size, invalid);
    int fire_x = 0;
    int fire_y = 0;
    int turns = 1;
    int max_turns = (size * size) * 0.75;
    int count;
    pause(0.5);

    std::cout << "Loging in...";
    pause(0.25);
    std::cout << "...Authenticating...\n";
    pause(2);
    std::cout << "...User authorized\n" << "Acecess granted\n\n";
    pause(1.5);
	std::cout
		<< "Mission breifing: code a-2se-3\n"
		<< "Eliminate all target, before reinforcement arrive.\n"
		<< "Target:"
		<< "        Omega 1\n"
		<< "        Delta 1\n"
		<< "        Alpha 1\n"
		<< "        Alpha 2\n"
		<< "        Alpha 3\n"
		<< std::endl;
    pause(0.5);
    while (!omega_1.is_destroyed || !alpha_1.is_destroyed || !alpha_2.is_destroyed || !alpha_3.is_destroyed || !delta_1.is_destroyed) {
        if (turns > max_turns)
        {
            map.edit_time_up_board();
            map.render_board();
            std::cout << "Enemy reinforcement have arived." << std::endl;
            break;
        }
        else
        {
            map.render_board();
            std::cout << "\nTurn: " << turns << "\n";
            turns += 1;
            std::cout << "Fire coordinate:\n";
            count = 0;
            while (fire_x == 0 && count < 5)
            {
                std::cout << "X: ";
                std::cin >> fire_x;
                if (size + 1 > fire_x && fire_x > 0) { break; }
                else { fire_x = 0;  count += 1; }
            }
            count = 0;
            while (fire_y == 0 && count < 5)
            {
                std::cout << "Y: ";
                std::cin >> fire_y;
                if (size + 1 > fire_y && fire_y > 0) { break; }
                else { fire_y = 0;  count += 1; }
            }
          
            
            if (omega_1.hit(fire_x, fire_y))
            {
                map.edit_hit_board(fire_x, fire_y);
                pause(0.2);
                if (omega_1.is_destroyed) { std::cout << "\n\n" << dialog() << "\n" << std::endl; }
            }
            else if (delta_1.hit(fire_x, fire_y))
            {
                map.edit_hit_board(fire_x, fire_y);
                pause(0.2);
                if (delta_1.is_destroyed) { std::cout << "\n\n" << dialog() << "\n" << std::endl; }
            }
            else if (alpha_1.hit(fire_x, fire_y) || alpha_2.hit(fire_x, fire_y) || alpha_3.hit(fire_x, fire_y))
            {
                map.edit_hit_board(fire_x, fire_y);
                pause(0.2);
                std::cout << "\n\n" << dialog() << "\n" << std::endl;
            }
            else
            {
                map.edit_board(fire_x, fire_y);
                pause(0.2);
            }
            fire_x = 0;
            fire_y = 0;
        }
    }
    if (omega_1.is_destroyed && alpha_1.is_destroyed && alpha_2.is_destroyed && alpha_3.is_destroyed && delta_1.is_destroyed)
    {
        map.render_board();
        std::cout << "\nMission sucessful." << std::endl;
    }
    else { std::cout << "\nMission falied." << std::endl; }
    return 0;
}

std::string dialog()
{
    srand((unsigned)time(NULL));
    std::vector<std::string> line = {
        "Direct hit!",
        "Good work.",
        "Tango down!",
        "Keep up the good work."
    };
    int pick = rand() % line.size();
    return line[pick];
}

