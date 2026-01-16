#include "Player.h"
#include "mathFuncs.h"
#include <stdio.h>

#include "constants.h"


Player::Player(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int hp, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : GameEntity(renderer, camera, x, y, hp, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    speed = PLAYER_SPEED;

    lightAttack = new Attack(10, 100, 30, 500, 250);
    heavyAttack = new Attack(30, 100, 50, 1000, 500);
    currAttack = nullptr;

    setRectangleAsSprite(255, 0, 0);
}
void Player::move(double deltaTime)
{
    GameEntity::move(deltaTime);

    
    
    double dx = dirX;
    double dy = dirY;

    normalizeVector(&dx, &dy);

    if(dx != 0 || dy != 0) hasMoved = true;

    x += dx * speed * deltaTime;
    y += dy * speed * deltaTime;

    collider.x = (int)(x - (collider.w / 2));
    collider.y = (int)(y - collider.h);

    // printf("Player position: x - %f y - %f\n", x, y);
}
void Player::handleInput(SDL_Event* event)
{
    switch(event->type) {
        case SDL_KEYDOWN:
        {
            SDL_Keycode keyPressed = event->key.keysym.sym;
            if(keyPressed == KEY_RIGHT) 
            {
                dirX = 1;
                facingDirection = RIGHT;
            }
            else if(keyPressed == KEY_LEFT) 
            {
                dirX = -1;
                facingDirection = LEFT;
            }
            else if(keyPressed == KEY_DOWN) dirY = 1;
            else if(keyPressed == KEY_UP) dirY = -1;
            else if(!isAttacking && keyPressed == KEY_LIGHT_ATTACK) startAttacking(lightAttack);
            else if(!isAttacking && keyPressed == KEY_HEAVY_ATTACK) startAttacking(heavyAttack);
            else if(keyPressed == 'd') dealDamage(10);
            break;
        }

        case SDL_KEYUP:
        {
            SDL_Keycode keyUnPressed = event->key.keysym.sym;
            if(dirX == 1 && keyUnPressed == KEY_RIGHT) dirX = 0;
            else if(dirX == -1 && keyUnPressed == KEY_LEFT) dirX = 0;
            else if(dirY == 1 && keyUnPressed == KEY_DOWN) dirY = 0;
            else if(dirY == -1 && keyUnPressed == KEY_UP) dirY = 0;
            
            break;
        }
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
    wantsToAttack = false;
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
    else if(attackTimer <= currAttack->getAnimationDurationMs() - currAttack->getTimeToAttackMs())
    {
        if(!hasAttacked)
        {
            wantsToAttack = true;
            hasAttacked = true;
        }
        else 
        {
            wantsToAttack = false;
            // printf("Attacking - after attack; ");
        }
    }

    // else printf("Attacking - before attack; ");
    int attack = 0;
    if(currAttack == lightAttack) attack = 1;
    else if(currAttack == heavyAttack) attack = 2;
    // printf("Attack timer - %f; current attack: %d\n", attackTimer, attack);
}

bool Player::getWantsToAttack()
{
    return wantsToAttack;
}

int* Player::getHp()
{
    return &currHp;
}