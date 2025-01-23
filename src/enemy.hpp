
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.hpp"

class Enemy : public Entity
{
public:
    int direction;
    Enemy(float w, float h);
    void Update(double &dt);
    virtual ~Enemy();
};

#endif