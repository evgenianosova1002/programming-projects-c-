#include "subprogram.h"
#include <exception>

Subprogram::Subprogram(handle_type h)
    : coroutine_handle_(h)
{
}

Subprogram::Subprogram(Subprogram&& other) noexcept
    : coroutine_handle_(other.coroutine_handle_)
{
    other.coroutine_handle_ = nullptr;
}

Subprogram& Subprogram::operator=(Subprogram&& other) noexcept
{
    if (this != &other) {
        if (coroutine_handle_) {
            coroutine_handle_.destroy();
        }
        coroutine_handle_ = other.coroutine_handle_;
        other.coroutine_handle_ = nullptr;
    }
    return *this;
}

Subprogram::~Subprogram()
{
    if (coroutine_handle_) {
        coroutine_handle_.destroy();
    }
}

Move Subprogram::ask()
{
    coroutine_handle_.resume();
    return coroutine_handle_.promise().current_value;
}


Subprogram Subprogram::promise_type::get_return_object()
{
    return Subprogram{ handle_type::from_promise(*this) };
}

std::suspend_always Subprogram::promise_type::initial_suspend() noexcept
{
    return {};
}

std::suspend_always Subprogram::promise_type::final_suspend() noexcept
{
    return {};
}

void Subprogram::promise_type::unhandled_exception()
{
    throw;
}

std::suspend_always Subprogram::promise_type::yield_value(
    const Move& value) noexcept
{
    current_value = value;
    return {};
}

void Subprogram::promise_type::return_void()
{
}
