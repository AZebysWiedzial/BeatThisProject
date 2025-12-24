#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int hp, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : GameEntity(renderer, camera, x, y, hp, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    hpBar = new WorldRenderable(renderer, camera, x, y - objectHeight - 20, spriteWidth, 5, objectWidth, 5);
    hpBar->setRectangleAsSprite(255, 0, 0);
    hpBar->setAnchor(CENTER);
}

// void Enemy::render()
// {
//     WorldRenderable::render();
//     hpBar->render();
// }

void Enemy::move(double deltaTime)
{
    updateHpBar();
}

void Enemy::dealDamage(int damage)
{
    GameEntity::dealDamage(damage);
    updateHpBar();
}
void Enemy::updateHpBar()
{
    hpBar->setPosition(x, y - objectHeight - 20);
    hpBar->setSpriteWidth(((double)currHp / (double)maxHp) * objectWidth);
}

void Enemy::renderHpBar()
{
    hpBar->render();
}