#include "CollisionManager.h"

CollisionManager::CollisionManager(Player* player, LinkedList<Enemy*>* enemies, SDL_Rect* floor)
{
    this->player = player;
    this->enemies = enemies;
    this->floor = floor;
}

void CollisionManager::handleAllCollisions()
{
    enemies->forEach([&](Enemy* firstEnemy){
        enemies->forEach([&](Enemy* secondEnemy){
            if(firstEnemy != secondEnemy && secondEnemy->getHasMoved())
            { 
                if(abs(firstEnemy->getX() - secondEnemy->getX()) < 30)
                    secondEnemy->undoMoveX();
                
                if(abs(firstEnemy->getY() - secondEnemy->getY()) < 15)
                    secondEnemy->undoMoveY();
            }
        });
        if(abs(firstEnemy->getX() - player->getX()) < 30)
        {
            if(player->getHasMoved()) player->undoMoveX();
            if(firstEnemy->getHasMoved()) firstEnemy->undoMoveX();
        }
                
        if(abs(firstEnemy->getY() - player->getY()) < 15)
        {
            if(player->getHasMoved()) player->undoMoveY();
            if(firstEnemy->getHasMoved()) firstEnemy->undoMoveY();
        }
    });
}

void CollisionManager::handleFloorCollisions()
{

}