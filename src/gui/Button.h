#pragma once

#include <functional>

#include "Text.h"
#include "Font.h"
#include "Vector.h"

class Button
{
public:
    Button(vec2 const& position, vec2 const& size, std::string const& text, std::function<void()> const& callback);

    bool check_bounds(vec2 const& position) const;
    void click();
    void try_click(vec2 const& postion);

    void render() const;

private:
    vec2 pos;
    vec2 size;

    Font font {"arial", 48};
    Text text;

    std::function<void()> callback;

};