#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Enemy.h"
#include "LinkedList.h"
#include "Attack.h"

class EnemyManager
{
    public:
    EnemyManager(SDL_Renderer* renderer, SDL_Rect* camera);
    bool isEnemiesListEmpty();
    void spawnEnemy(int x, int y);
    void handleEnemiesMovement(double deltaTime);
    void handleEnemiesCollisions();
    int handlePlayerAttack(double playerX, double playerY, Direction playerDirection, Attack* attack);
    void clearEnemies();
    void renderEnemies();
    LinkedList<Enemy*>* getEnemiesList();

    private:
    SDL_Renderer* renderer;
    SDL_Rect* camera;
    LinkedList<Enemy*> enemies;
};
#endif