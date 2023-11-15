

#ifndef BUTTON_AREA_H
#define BUTTON_AREA_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>


class ButtonArea {
private:
    glm::vec2 Position, Size;
    bool Hot;
    void (*HotCallback)(bool);
    void (*ClickCallback)();
    bool IsWithinBounds(int x, int y);
public:
    ButtonArea(glm::vec2 pos, glm::vec2 size, void(*hot_callback)(bool), void(*click_callback)());
    void HandleEvent(const SDL_Event* Event);
    void SetHot(bool hot);
    void Click();
};


#endif

