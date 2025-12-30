#include "EnemyManager.h"
#include <stdio.h>

EnemyManager::EnemyManager(SDL_Renderer* renderer, SDL_Rect* camera)
{
    this->renderer = renderer;
    this->camera = camera;
}

void EnemyManager::spawnEnemy(int x, int y)
{
    Enemy* newEnemy = new Enemy(renderer, camera, x, y, 100, 30, 30, 30, 30);
    newEnemy->setRectangleAsSprite(0, 255, 0);
    enemies.add(newEnemy);
}
void EnemyManager::handleEnemiesCollisions()
{
    
}
int EnemyManager::handlePlayerAttack(double playerX, double playerY, Direction playerDirection, Attack* attack)
{
    int hitEnemies = 0;
    enemies.forEachAndRemoveIf([&](Enemy* enemy){
        if((playerX < enemy->getX() && playerDirection == RIGHT) || (playerX > enemy->getX() && playerDirection == LEFT))
            if(abs(enemy->getX() - playerX) <= attack->getRange() && abs(enemy->getY() - playerY) <= attack->getSweepingRange())
                {
                    enemy->dealDamage(attack->getDamage());   
                    printf("Took damage! Current HP: %d\n", enemy->getCurrHp());
                    hitEnemies++;
                }
        return enemy->getCurrHp() <= 0;
    });
    return hitEnemies;
}

void EnemyManager::handleEnemiesMovement(double deltaTime)
{
    enemies.forEach([deltaTime](Enemy* enemy){
        enemy->move(deltaTime);
    });
}
// void EnemyManager::renderEnemies()
// {
//     // enemies.sort();
//     enemies.forEach([](Enemy* enemy){
//         enemy->renderShadow();
//     });

//     enemies.forEach([](Enemy* enemy){
//         enemy->render();
//     });

//     enemies.forEach([](Enemy* enemy){
//         enemy->renderHpBar();
//     });
// }
LinkedList<Enemy*>* EnemyManager::getEnemiesList()
{
    return &enemies;
}
void EnemyManager::clearEnemies()
{
    enemies.clear();
}