#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>

enum Action
{
    ACTION_NONE = 0,
    ACTION_ADD_ONE = 1,
    ACTION_DOUBLE_VALUE = 2,
    ACTION_DIVIDE_BY_THREE = 3
};

enum WhichNumber
{
    WHICH_A = 0,
    WHICH_B = 1
};

std::string action_to_string(Action action);

struct Move
{
    Action action;
    WhichNumber which;
};

struct GameState
{
    long long number_a;
    long long number_b;
};

class Subprogram;

Subprogram subprogram_coroutine(std::shared_ptr<GameState> game_state);

#endif
