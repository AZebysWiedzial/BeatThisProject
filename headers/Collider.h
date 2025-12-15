#include<SDL.h>

class Collider
{
    enum ColliderType
    {
        PhisicalInner,
        PhisicalOuter,
        Interactable
    };
    public:
    Collider(ColliderType type);

    private:
    ColliderType type;
    SDL_Rect collider;
};