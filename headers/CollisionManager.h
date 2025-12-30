#include "Player.h"
#include "Enemy.h"
#include "LinkedList.h"

class CollisionManager
{
    public:
    CollisionManager(Player* player, LinkedList<Enemy*>* enemies, SDL_Rect* floor);
    void handleEnemiesCollisions();
    void handleFloorCollisions();
    void handleAllCollisions();

    private:
    Player* player;
    LinkedList<Enemy*>* enemies;
    SDL_Rect* floor;
};