// main.cpp
#include <iostream>
#include <raylib.h>
#include "player.h"

using std::cout;


int main(int argc, char *argv[]) {
  InitWindow(800, 600, "Mesh Collision");
  SetTargetFPS(60);
  double delta_time;

  Camera3D camera;
  camera.position = {30, 30, 30};
  camera.up = {0, 1, 0};
  camera.target = {0, 0, 0};
  camera.fovy = 60;
  camera.projection = CAMERA_PERSPECTIVE;

  Texture texture = LoadTexture("texture.png");
  Model model = LoadModel("model.glb");
  SetMaterialTexture(&model.materials[1], MATERIAL_MAP_DIFFUSE, texture);

  BoundingBox model_bounds = GetModelBoundingBox(model);

  Player player(model.meshes[0], model.transform, model_bounds);

  cout << "Everything seems to be good to go!\n";
  while (WindowShouldClose() == false) {
    delta_time = GetFrameTime() * 60;

    player.keyPressed();
    player.KeyReleased();

    player.update(delta_time);

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);
      {
        DrawModel(model, {0, 0, 0}, 1, WHITE);
        DrawBoundingBox(model_bounds, GREEN);
        player.draw();
      }
      EndMode3D();

      DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 24, RED);
      DrawText(TextFormat("Distance from ground: %f", 
                          player.ground_distance), 10, 28, 24, RED);
      DrawText(TextFormat("Position: (%.03f, %.03f, %.03f)",
        player.position.x, player.position.y, player.position.z),
               10, 52, 24, RED);
    }
    EndDrawing();
  }

  UnloadModel(model);
  UnloadTexture(texture);
  return 0;
}
