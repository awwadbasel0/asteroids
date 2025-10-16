// #ifndef ASTEROID_HPP_
// #define ASTEROID_HPP_
#pragma once
#define MaxRotationSpeed 60;
#include <raylib.h>
class Asteroid{
    private:
    Vector2 pos;
    Vector2 speed;
    float rotation,rotationSpeed;
    int size;
    public:
    bool active=true;
    Asteroid(Vector2 pos,Vector2 speed,int size);
    void Draw();
    void Update();
    static Asteroid CreateAsteroid();
    void Destroy();
    Vector2 getPos();
    int getSize();
};
// class AsteroidGroup{
//     private:
//     std::list<Asteroid> asteroids;
//     public:
//     AsteroidGroup();
//     void add();
//     void 
// };
// #endif
