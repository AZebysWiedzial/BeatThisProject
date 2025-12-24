#ifndef PLAYER_H
#define PLAYER_H
#include "GameEntity.h"
#include "Attack.h"
#include "EnemyManager.h"

#define KEY_UP SDLK_UP
#define KEY_DOWN SDLK_DOWN
#define KEY_LEFT SDLK_LEFT
#define KEY_RIGHT SDLK_RIGHT
#define KEY_LIGHT_ATTACK 'z'
#define KEY_HEAVY_ATTACK 'x'


#define PLAYER_SPEED 400

class Player : public GameEntity
{
    public:
        Player(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int hp, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
        void move(double deltaTime) override;
        void handleInput(SDL_Event& event);
        void startAttacking(Attack* attack);
        Attack* attack();
        void finishAttacking();
        void handleAttacking(double deltaTime);
        bool getWantsToAttack();
        
        
    private:
    double attackTimer, attackCooldown;
    bool isAttacking, hasAttacked, wantsToAttack;



    Attack* lightAttack;
    Attack* heavyAttack;

    Attack* currAttack;
    
    EnemyManager* enemyManager;
};
#endif