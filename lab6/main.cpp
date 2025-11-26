#include <iostream>
#include <string>

using namespace std;

enum Action
{
    ACTION_NONE = 0,
    ACTION_ADD_ONE = 1,
    ACTION_DOUBLE_VALUE = 2,
    ACTION_DIVIDE_BY_THREE = 3
};

struct Player
{
    string player_name;
    Action previous_action;

    Player(const string& name_parameter = "")
        : player_name(name_parameter), previous_action(ACTION_NONE) {
    }
};

void print_state(long long number_a, long long number_b)
{
    cout << "   Current numbers: a = " << number_a
        << ", b = " << number_b
        << ", sum = " << (number_a + number_b) << "\n";
}

bool make_move(Player& current_player,
    long long& number_a,
    long long& number_b,
    long long target_sum)
{
    Action action_to_execute = ACTION_NONE;

    if (current_player.previous_action == ACTION_ADD_ONE)
    {
        action_to_execute = ACTION_DOUBLE_VALUE;
    }
    else if (current_player.previous_action == ACTION_DOUBLE_VALUE)
    {
        action_to_execute = ACTION_ADD_ONE;
    }
    else if (current_player.previous_action == ACTION_DIVIDE_BY_THREE)
    {
        action_to_execute = ACTION_ADD_ONE;
    }
    else
    {
        action_to_execute = ACTION_DOUBLE_VALUE;
    }

    if (current_player.previous_action != ACTION_DIVIDE_BY_THREE &&
        (number_a % 3 == 0 || number_b % 3 == 0))
    {
        long long current_sum = number_a + number_b;
        if (current_sum * 2 > target_sum)
        {
            action_to_execute = ACTION_DIVIDE_BY_THREE;
        }
    }

    cout << current_player.player_name << " makes a move.\n";

    switch (action_to_execute)
    {
    case ACTION_ADD_ONE:
    {
        if (number_a <= number_b)
        {
            cout << "   Action: add 1 to a.\n";
            ++number_a;
        }
        else
        {
            cout << "   Action: add 1 to b.\n";
            ++number_b;
        }
        break;
    }

    case ACTION_DOUBLE_VALUE:
    {
        if (number_a <= number_b)
        {
            cout << "   Action: double a.\n";
            number_a *= 2;
        }
        else
        {
            cout << "   Action: double b.\n";
            number_b *= 2;
        }
        break;
    }

    case ACTION_DIVIDE_BY_THREE:
    {
        if (number_a % 3 == 0 && number_b % 3 == 0)
        {
            if (number_a >= number_b)
            {
                cout << "   Action: divide a by 3.\n";
                number_a /= 3;
            }
            else
            {
                cout << "   Action: divide b by 3.\n";
                number_b /= 3;
            }
        }
        else if (number_a % 3 == 0)
        {
            cout << "   Action: divide a by 3.\n";
            number_a /= 3;
        }
        else if (number_b % 3 == 0)
        {
            cout << "   Action: divide b by 3.\n";
            number_b /= 3;
        }
        else
        {
            cout << "   (Divide by 3 impossible, adding 1 to a instead.)\n";
            ++number_a;
            action_to_execute = ACTION_ADD_ONE;
        }
        break;
    }

    default:
        break;
    }

    current_player.previous_action = action_to_execute;

    print_state(number_a, number_b);

    long long current_sum = number_a + number_b;
    if (current_sum >= target_sum)
    {
        cout << "   " << current_player.player_name
            << " reached the target sum (" << current_sum
            << " >= " << target_sum << ") and wins!\n";
        return true;
    }

    return false;
}

int main()
{
    long long input_number_a, input_number_b;
    cout << "Enter two positive integers (a b): ";
    cin >> input_number_a >> input_number_b;

    if (input_number_a <= 0 || input_number_b <= 0)
    {
        cout << "Numbers must be positive.\n";
        return 0;
    }

    long long initial_sum = input_number_a + input_number_b;
    long long required_target_sum = initial_sum * 10;

    cout << "\nInitial sum = " << initial_sum
        << ", target sum = " << required_target_sum << ".\n";
    print_state(input_number_a, input_number_b);
    cout << "\nGame Started!\n\n";

    Player player_list[3] = {
        Player("Coroutine 1"),
        Player("Coroutine 2"),
        Player("Coroutine 3")
    };

    int active_player_index = 0;
    int move_counter = 1;

    while (true)
    {
        cout << "Move " << move_counter
            << " ("<< player_list[active_player_index].player_name <<")\n";

        bool victory = make_move(player_list[active_player_index],
            input_number_a,
            input_number_b,
            required_target_sum);

        cout << "\n";

        if (victory)
        {
            cout << "Game Over!\n";
            cout << "Winner: " << player_list[active_player_index].player_name << ".\n";
            break;
        }

        active_player_index = (active_player_index + 1) % 3;
        ++move_counter;

        if (move_counter > 10000)
        {
            cout << "Game too long, terminating.\n";
            break;
        }
    }

    return 0;
}
