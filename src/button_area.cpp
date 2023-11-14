

#include "button_area.h"


ButtonArea::ButtonArea(glm::vec2 pos, glm::vec2 size, void(*hot_callback)(bool), void(*click_callback)())
    : Position(pos), Size(size), Hot(false), HotCallback(hot_callback), ClickCallback(click_callback) { }

void ButtonArea::HandleEvent(const SDL_Event* Event) {
    if (Event->type == SDL_MOUSEMOTION)
    {
        if (this->Hot != IsWithinBounds(Event->motion.x, Event->motion.y))
        {
            this->Hot = !this->Hot;
            this->HotCallback(this->Hot);
        }
    } else if (Event->type == SDL_MOUSEBUTTONDOWN && this->Hot )
    {
        this->ClickCallback();
    }
}


bool ButtonArea::IsWithinBounds(int x, int y) {
    if (x < this->Position.x) return false;
    if (x > this->Position.x + this->Size.x) return false;
    if (y < this->Position.y) return false;
    if (y > this->Position.y + this->Size.y) return false;
    return true;
}

