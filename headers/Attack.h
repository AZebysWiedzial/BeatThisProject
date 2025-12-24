#ifndef ATTACK_H
#define ATTACK_H

class Attack
{
    public:
    Attack(int damage, int range, int sweepingRange, int animationDurationMs, int timeToAttackMs);
    //add getters
    int getDamage() const;
    int getRange() const;
    int getSweepingRange() const;
    int getAnimationDurationMs() const;
    int getTimeToAttackMs() const;

    private:
    int range;
    int sweepingRange;
    int animationDurationMs;
    int timeToAttackMs;
    int damage;
};
#endif