#include "Player.h"
#include "mathFuncs.h"
#include <stdio.h>




Player::Player(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int hp, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : GameEntity(renderer, camera, x, y, hp, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    speed = PLAYER_SPEED;

    lightAttack = new Attack(10, 100, 30, 500, 250);
    heavyAttack = new Attack(30, 100, 50, 1000, 500);

    setRectangleAsSprite(255, 0, 0);
}
void Player::move(double deltaTime)
{
    GameEntity::move(deltaTime);
    
    double dx = dirX;
    double dy = dirY;

    normalizeVector(&dx, &dy);

    x += dx * speed * deltaTime;
    y += dy * speed * deltaTime;

    collider.x = (int)(x - (collider.w / 2));
    collider.y = (int)(y - collider.h);

    // printf("Player position: x - %f y - %f\n", x, y);
}
void Player::handleInput(SDL_Event& event)
{
    switch(event.type) {
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == KEY_RIGHT) 
            {
                dirX = 1;
                facingDirection = RIGHT;
            }
            else if(event.key.keysym.sym == KEY_LEFT) 
            {
                dirX = -1;
                facingDirection = LEFT;
            }
            else if(event.key.keysym.sym == KEY_DOWN) dirY = 1;
            else if(event.key.keysym.sym == KEY_UP) dirY = -1;
            else if(!isAttacking && event.key.keysym.sym == KEY_LIGHT_ATTACK) startAttacking(lightAttack);
            else if(!isAttacking && event.key.keysym.sym == KEY_HEAVY_ATTACK) startAttacking(heavyAttack);
            break;

        case SDL_KEYUP:
            if(dirX == 1 && event.key.keysym.sym == KEY_RIGHT) dirX = 0;
            else if(dirX == -1 && event.key.keysym.sym == KEY_LEFT) dirX = 0;
            else if(dirY == 1 && event.key.keysym.sym == KEY_DOWN) dirY = 0;
            else if(dirY == -1 && event.key.keysym.sym == KEY_UP) dirY = 0;
            break;
        }
}

void Player::startAttacking(Attack* attack)
{
    currAttack = attack;

    attackTimer = currAttack->getAnimationDurationMs();
    isAttacking = true;
    hasAttacked = false;

}
Attack* Player::attack()
{
    return currAttack;
}
void Player::finishAttacking()
{
    currAttack = nullptr;
    isAttacking = false;
    attackTimer = 0;
}
void Player::handleAttacking(double deltaTime)
{
    if(!isAttacking) return;
    
    attackTimer -= deltaTime;
    if(attackTimer <= 0)
    {
        finishAttacking();
        // printf("Attack finished; ");
    }
    else if(attackTimer < currAttack->getAnimationDurationMs() - currAttack->getTimeToAttackMs())
    {
        if(!hasAttacked)
        {
            wantsToAttack = true;
            printf("Attacked;\n");
            hasAttacked = true;
        }
        else 
        {
            wantsToAttack = false;
            // printf("Attacking - after attack; ");
        }
    }

    // else printf("Attacking - before attack; ");
    // printf("Attack timer - %f\n", attackTimer);
}

bool Player::getWantsToAttack()
{
    return wantsToAttack;
}