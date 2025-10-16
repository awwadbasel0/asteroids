#include "Asteroids.hpp"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include "Asteroids.hpp"
#include <cmath>


Asteroid::Asteroid(Vector2 pos,Vector2 speed,int size):pos(pos),speed(speed),size(size){
        rotationSpeed=GetRandomValue(5, 50);
        rotation=rand()%360;
    }
 void Asteroid::Draw(){
        if(active)
        DrawPolyLines(pos, 3, (size+1)*40, rotation,WHITE);
    }
    void Asteroid::Update(){
        Vector2 newPos={pos.x+speed.x,pos.y+speed.y};
            rotation=fmod(rotation+rotationSpeed,360);
        if(!CheckCollisionPointRec(newPos, {0,0,GetScreenWidth()*1.0f,GetScreenHeight()*1.0f}))
            {active=false;}
        else
            {pos=newPos;}
    }
    Asteroid Asteroid::CreateAsteroid(){
    switch (rand()%4) {
    case 0:
    return Asteroid({rand()%1920/1.0f,1080.0f},{GetRandomValue(2, 4)*1.0f,-GetRandomValue(2, 4)*1.0f},rand()%3);
    case 1:
    return Asteroid({rand()%1920/1.0f,0.0f},{GetRandomValue(2, 5)*1.0f,GetRandomValue(2, 5)*1.0f},rand()%3);
    case 2:
    return Asteroid({1920,rand()%1080/1.0f},{-GetRandomValue(2, 5)*1.0f,GetRandomValue(2, 5)*1.0f},rand()%3);
    case 3:
    return Asteroid({0,rand()%1080/1.0f},{GetRandomValue(2, 5)*1.0f,GetRandomValue(2, 5)*1.0f},rand()%3);    
    }
    return Asteroid({0,rand()%1080/1.0f},{GetRandomValue(2, 5)*1.0f,GetRandomValue(2, 5)*1.0f},rand()%3);
    }
    void Asteroid::Destroy(){
        free(this);
    }
    Vector2 Asteroid::getPos(){
    return pos;
}
int Asteroid::getSize(){
    return size;
}
