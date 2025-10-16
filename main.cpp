#include <raylib.h>
#include <string>
#include "Asteroids.hpp"
#include "Player.hpp"
int main(int argc, char *argv[]) {
  InitWindow(1920, 1080, "asteroids");
  SetTargetFPS(60);
  std::list<Asteroid>asteroids;
  Player *play=new Player();
  int points=0;
  for(auto i=0;i<10;i++){
        asteroids.push_back(Asteroid::CreateAsteroid());
      }
  while (!WindowShouldClose()) {
    if(IsKeyDown(KEY_LEFT))
      play->rotate(false);
    if(IsKeyDown(KEY_RIGHT))
      play->rotate(true);
    if(IsKeyDown(KEY_UP))
      play->thrust();
    if(IsKeyPressed(KEY_SPACE))
      play->shoot();
    while(asteroids.size()<10)
    {asteroids.push_back(Asteroid::CreateAsteroid());}
    BeginDrawing();
    ClearBackground(CLITERAL(Color){0x1F,0x1F,0x23, 1});
    // here
    for(auto i=asteroids.begin();i!=asteroids.end();i++){
      (*i).Draw();
//       if(CheckCollisionCircles(play->getPos(),40,(*i).getPos(), ((*i).getSize()+1)*40))
//         i=asteroids.erase(i);
      // else
    }
    play->Draw();
    DrawText(std::to_string(points).c_str(), 0, 0, 64, RAYWHITE);
    EndDrawing();
    for(auto i=play->shots.begin();i!=play->shots.end();i++){
            points+=(*i).CheckCollisionAsteroid(asteroids);
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
