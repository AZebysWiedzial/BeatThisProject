#ifndef ENEMY_H
#define ENEMY_H
#include "GameEntity.h"

class Enemy : public GameEntity
{
    public:
    Enemy(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int hp, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
    // void render() override;
    void renderHpBar();
    void move(double deltaTime) override;
    void dealDamage(int damage) override;
    void updateHpBar();

    private:
    WorldRenderable* hpBar;
};
#endif