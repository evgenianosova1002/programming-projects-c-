#ifndef SUBPROGRAM_H
#define SUBPROGRAM_H

#include <coroutine>
#include "game.h"

class Subprogram
{
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    explicit Subprogram(handle_type h);
    Subprogram(Subprogram&& other) noexcept;
    Subprogram(const Subprogram&) = delete;
    Subprogram& operator=(const Subprogram&) = delete;
    Subprogram& operator=(Subprogram&& other) noexcept;
    ~Subprogram();

    Move ask();

    struct promise_type
    {
        Move current_value{ ACTION_NONE, WHICH_A };

        Subprogram get_return_object();
        std::suspend_always initial_suspend() noexcept;
        std::suspend_always final_suspend() noexcept;
        void unhandled_exception();
        std::suspend_always yield_value(const Move& value) noexcept;
        void return_void();
    };

private:
    handle_type coroutine_handle_ = nullptr;
};

#endif
