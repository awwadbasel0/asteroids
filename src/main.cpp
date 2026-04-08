#include <iostream>
#include <raylib.h>
#include <string>
#include "../include/Asteroids.hpp"
#include "../include/Player.hpp"
int main(int argc, char *argv[]) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(1920, 1080, "asteroids");
  SetTargetFPS(60);
  std::list<Asteroid>asteroids;
  Player *play=new Player();
  int timebroken=0;
  int points=0;
  for(auto i=0;i<10;i++){
        asteroids.push_back(Asteroid::CreateAsteroid());
      }
  while (!WindowShouldClose()) {
    if(IsKeyDown(KEY_LEFT))
      play->rotate(false);
    if(IsKeyDown(KEY_RIGHT))
      play->rotate(true);
    // if(IsKeyDown(KEY_UP))
    //   play->thrust();
    if(IsKeyPressed(KEY_UP)){
      play->accelarate();
    }
    if(IsKeyPressed(KEY_SPACE))
      play->shoot();
    while(asteroids.size()<4)
    {asteroids.push_back(Asteroid::CreateAsteroid());}
    if(timebroken>1){
      timebroken--;
    } else if(timebroken>0) {
      play=new Player();
      timebroken=0;
    }
    BeginDrawing();
    ClearBackground(CLITERAL(Color){0x1F,0x1F,0x23, 1});
    DrawRectangleGradientEx({0,0,GetScreenWidth()*1.0f,GetScreenHeight()*1.0f}, Color{0x29,0x29,0x29}, BLACK, BLACK, BLACK);
    // here
    for(auto i=asteroids.begin();i!=asteroids.end();i++){
      (*i).Draw();
      if(CheckCollisionCircles(play->getPos(),30,(*i).getPos(), ((*i).getSize()+1)*40)){
        play->Destroy();
        timebroken=60;
      }
      // else
    }
    play->Draw();
    DrawText(std::to_string(points).c_str(), 0, 0, 64, RAYWHITE);
    EndDrawing();
    play->differentMovement();
    for(auto i=play->shots.begin();i!=play->shots.end();){
      int gained=(*i).CheckCollisionAsteroid(asteroids);
            points+=gained;
            if(gained>0)
              i=play->shots.erase(i);
            else
              i++;
        }
    for(auto i=asteroids.begin();i!=asteroids.end();){
      (*i).Update();
      if(!(*i).active){
        i=asteroids.erase(i);
      }else{
       i++;
      }
    }
  }
  for(auto i=asteroids.begin();i!=asteroids.end();i++)
    (*i).Destroy();
  CloseWindow();
  return 0;
}
