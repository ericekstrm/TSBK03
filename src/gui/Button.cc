#include "Button.h"

Button::Button(vec2 const& position, vec2 const& size, std::string const& text, std::function<void()> const& callback)
    : pos {position}, size {size}, text {text, position, font}, callback {callback}
{
}

bool Button::check_bounds(vec2 const& p) const
{
    return (p.x >= pos.x && p.x <= pos.x + size.x && p.y >= pos.y && p.y <= pos.y + size.y);
}

void Button::click()
{
    callback();
}

void Button::try_click(vec2 const& p)
{
    if (check_bounds(p))
    {
        click();
    }
}

void Button::render() const
{
    text.render();
}