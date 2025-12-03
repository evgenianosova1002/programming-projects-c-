#include <iostream>
#include <memory>
#include "game.h"
#include "subprogram.h"

using namespace std;

int main()
{
    long long number_a, number_b;
    cout << "Enter two positive integers (a b): ";
    cin >> number_a >> number_b;

    if (number_a <= 0 || number_b <= 0) {
        cout << "Numbers must be positive.\n";
        return 0;
    }

    long long initial_sum = number_a + number_b;
    long long target_sum = initial_sum * 10;

    cout << "\nInitial sum = " << initial_sum
        << ", target sum = " << target_sum << ".\n\n";

    auto state = std::make_shared<GameState>();
    state->number_a = number_a;
    state->number_b = number_b;

    Subprogram subprogram_1 = subprogram_coroutine(state);
    Subprogram subprogram_2 = subprogram_coroutine(state);
    Subprogram subprogram_3 = subprogram_coroutine(state);

    Subprogram* players[3] = { &subprogram_1, &subprogram_2, &subprogram_3 };

    int current_player_index = 0;
    int move_number = 1;

    while (true) {
        long long current_sum = state->number_a + state->number_b;

        if (current_sum >= target_sum) {
            cout << "Game Over!\n";
            cout << "Winner: Subprogram " << (current_player_index + 1) << ".\n";
            break;
        }

        cout << "Move " << move_number
            << " (Subprogram " << (current_player_index + 1) << ")\n";

        Move move = players[current_player_index]->ask();
        Action action_to_execute = move.action;

        long long& chosen_number = (move.which == WHICH_A ? state->number_a : state->number_b);

        switch (action_to_execute)
        {
        case ACTION_ADD_ONE:
            cout << "   Action: " << action_to_string(action_to_execute) << " ";
            chosen_number += 1;
            break;

        case ACTION_DOUBLE_VALUE:
            cout << "   Action: " << action_to_string(action_to_execute) << " ";
            chosen_number *= 2;
            break;

        case ACTION_DIVIDE_BY_THREE:
            cout << "   Action: " << action_to_string(action_to_execute) << " ";
            if (chosen_number % 3 == 0) {
                chosen_number /= 3;
            }
            else {
                cout << "(cannot divide, changed to add 1) ";
                chosen_number += 1;
            }
            break;

        default:
            cout << "   Action: none\n";
            break;
        }

        cout << "(applied to "
            << ((&chosen_number == &state->number_a) ? "a)\n" : "b)\n");

        cout << "   Current numbers: a = " << state->number_a
            << ", b = " << state->number_b
            << ", sum = " << (state->number_a + state->number_b) << "\n\n";

        current_sum = state->number_a + state->number_b;
        if (current_sum >= target_sum) {
            cout << "Game Over!\n";
            cout << "Winner: Subprogram " << (current_player_index + 1) << ".\n";
            break;
        }

        if (move_number > 10000) {
            cout << "Game too long, terminating.\n";
            break;
        }

        current_player_index = (current_player_index + 1) % 3;
        ++move_number;
    }

    return 0;
}
