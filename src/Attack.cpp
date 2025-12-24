#include "Attack.h"
Attack::Attack(int damage, int range, int sweepingRange, int animationDurationMs, int timeToAttackMs)
{
    this->damage = damage;
    this->range = range;
    this->sweepingRange = sweepingRange;
    this->animationDurationMs = animationDurationMs;
    this->timeToAttackMs = timeToAttackMs;
}
int Attack::getDamage() const
{
    return damage;
}
int Attack::getRange() const
{
    return range;
}
int Attack::getSweepingRange() const
{
    return sweepingRange;   
}
int Attack::getAnimationDurationMs() const
{
    return animationDurationMs;
}
int Attack::getTimeToAttackMs() const
{
    return timeToAttackMs;
}