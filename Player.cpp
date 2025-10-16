#include "Player.hpp"
#include "Asteroids.hpp"
#include <cstdlib>
#include <list>
#include <raylib.h>
#include <cmath>
#include <raymath.h>
Player::Player(){
    currentPos={GetScreenWidth()/2.0f,GetScreenHeight()/2.0f};
    rotation=180;
}
void Player::Draw(){
    //Player
    Vector2 points[]={{currentPos.x,currentPos.y},{currentPos.x-30,currentPos.y-30},{currentPos.x+30,currentPos.y-30},{currentPos.x,currentPos.y-20},};
    for(int i=0;i<4;i++){
    Vector2 local = Vector2Subtract(points[i], currentPos);
    Vector2 rotated = Vector2Rotate(local, DEG2RAD * rotation);
    points[i] = Vector2Add(currentPos, rotated);
    }
    DrawLineV(points[0],points[1], RAYWHITE);
    DrawLineV(points[0],points[2], RAYWHITE);
    DrawLineV(points[1],points[3], RAYWHITE);
    DrawLineV(points[2],points[3], RAYWHITE);
    //Shots
        for(auto i=shots.begin();i!=shots.end();){
            if(!(*i).Draw()){
                //(*i).Destroy();
                i=shots.erase(i);
            } 
            else {
                i++;
            }
        }
}
//direction: false=left true=right
void Player::rotate(bool direction){
    if(direction){
        rotation=fmod(rotation+5,360);
    }else {
        rotation=fmod(rotation-5,360);    
    }
}
void Player::thrust(){
    float trajectoryX=-sin(DEG2RAD*rotation)*5;
    float trajectoryY=cos(DEG2RAD*rotation)*5;
    // std::cout<<trajectoryX<<","<<trajectoryY<<","<<rotation<<std::endl;
    Vector2 newPos={currentPos.x+trajectoryX,currentPos.y+trajectoryY};
    if(newPos.x>0&&newPos.x<1920&&newPos.y>0&&newPos.y<1080)
        currentPos=newPos;
}
void Player::shoot(){
    // shotindex++;
    // if(shotindex>=shotsSize){
    //     if(shotsSize==0)
    //         shotsSize=1;
    //     else
    //         shotsSize*=2;
    //     shots=(shot *)realloc(shots,shotsSize*sizeof(shot));
    // }
    Vector2 trajectory={-sin(DEG2RAD*rotation)*30,cos(DEG2RAD*rotation)*30};
    // shots[shotindex]=shot(currentPos,trajectory);
    shots.push_back(shot(currentPos,trajectory));
}
shot::shot(Vector2 pos,Vector2 trajectory):pos(pos),trajectory(trajectory){}
bool shot::Draw(){
    DrawCircle(pos.x, pos.y, 5, WHITE);
    Vector2 newPos={pos.x+(trajectory.x),pos.y+(trajectory.y)};
    if(!CheckCollisionPointRec(newPos, {0,0,GetScreenWidth()*1.0f,GetScreenHeight()*1.0f})){
//         if(newPos.x<0){newPos.x=GetScreenWidth()-(newPos.x);}
//         else if(newPos.x>GetScreenWidth()){newPos.x=0+(newPos.x-GetScreenWidth());}
//         else if(newPos.y<0){newPos.y=GetScreenHeight()-(newPos.y);}
        // else {newPos.y=0+(newPos.y-GetScreenHeight());}
        return false;
    }
    pos=newPos;
    return true;
    
}
void shot::Destroy(){
    free(this);
}
//returns total points per check
int shot::CheckCollisionAsteroid(std::list<Asteroid>& asteroids){
    int points=0;
    for(auto it=asteroids.begin();it!=asteroids.end();it++){
        if(CheckCollisionPointCircle(pos, (*it).getPos(), ((*it).getSize()+1)*40)){
            switch((*it).getSize()){
                case 0:
                points+=40;
                break;
                case 1:
                points+=80;
                break;
                case 2:
                points+=160;
                break;
            }
            (*it).active=false;
            // it=asteroids.erase(it);
        }
    //     else
    //      it++;
    }
    return points;
}
Vector2 Player::getPos(){
    return currentPos;
}

