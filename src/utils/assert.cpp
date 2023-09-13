// header
#include "assert.hpp"

// extern
#include <fmt/color.h>
#include <fmt/format.h>



bool assert_exception = false;

void assert_enable_exception_mode()
{
    assert_exception = true;
}


class AssertException final : std::exception {
private:

    std::string m_message;

public:

    AssertException(std::string message, SourceLocation location)
    {
        m_message = fmt::format("({}:{}): {}", location.filename, location.line, message);
    }

    [[nodiscard]]
    char const* what() const noexcept override
    {
        return this->m_message.c_str();
    }
};


[[noreturn]]
void panic(std::string const& message, SourceLocation location)
{
    // build panic message
    auto color = fmt::color::red;
    auto styled = [&](std::string const& text) { return fmt::styled(text, fmt::fg(color)); };
    auto final_message = fmt::format("[{}]({}:{}): {}", styled("PANIC"), location.filename, location.line, message);

    fmt::println("{}", final_message);
    std::exit(1);
}

void debug_assert(bool result, std::string const& message, SourceLocation location)
{
#if !defined NDEBUG

    always_assert(result, message, location);

#else

    (void)result;
    (void)message;
    (void)location;

#endif
}
void always_assert(bool result, std::string const& message, SourceLocation location)
{
    // do nothing if result is true
    // if (result == true) [[likely]]
    //     return;

    // build panic message, using custom if there is one
    std::string panic_message = "assertion failed";
    if (message.empty() == false)
        panic_message = fmt::format("assertion failed: {}", message);

    // panic
    if (assert_exception == true)
        throw AssertException{panic_message, location};
    else
        panic(panic_message, location);
}
