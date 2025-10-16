#pragma once
#include "Asteroids.hpp"
#include <list>
#include <raylib.h>
class shot{
    private:
        Vector2 pos;
        Vector2 trajectory;
    public:
        shot(Vector2 point,Vector2 trajectory);
        bool Draw();
        void Destroy();
        int CheckCollisionAsteroid(std::list<Asteroid>& asteroids);
};
class Player{
    private:
    Vector2 currentPos;
    float rotation;
    public:
    std::list<shot> shots;
    Player();
    void Draw();
    void thrust();
    void rotate(bool direction);
    void shoot();
    Vector2 getPos();
};
