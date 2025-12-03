#include "game.h"
#include "subprogram.h"

std::string action_to_string(Action action)
{
    switch (action)
    {
    case ACTION_ADD_ONE:         return "add 1";
    case ACTION_DOUBLE_VALUE:    return "double";
    case ACTION_DIVIDE_BY_THREE: return "divide by 3";
    default:                     return "none";
    }
}

Subprogram subprogram_coroutine(std::shared_ptr<GameState> game_state)
{
    Action previous_action = ACTION_NONE;

    while (true) {
        long long value_a = game_state->number_a;
        long long value_b = game_state->number_b;

        WhichNumber which_to_change =
            (value_a <= value_b) ? WHICH_A : WHICH_B;

        long long current_value =
            (which_to_change == WHICH_A) ? value_a : value_b;

        Action action_to_execute = ACTION_NONE;

        if (previous_action == ACTION_ADD_ONE) {
            action_to_execute = ACTION_DOUBLE_VALUE;
        }
        else if (previous_action == ACTION_DOUBLE_VALUE) {
            if (current_value % 3 == 0)
                action_to_execute = ACTION_DIVIDE_BY_THREE;
            else
                action_to_execute = ACTION_ADD_ONE;
        }
        else if (previous_action == ACTION_DIVIDE_BY_THREE) {
            action_to_execute = ACTION_ADD_ONE;
        }
        else {
            action_to_execute = ACTION_DOUBLE_VALUE;
        }

        previous_action = action_to_execute;

        Move move{ action_to_execute, which_to_change };
        co_yield move;
    }
}
