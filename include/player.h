// player.h
#pragma once
#include <raylib.h>


/* The player object is the controllable implement for the user. They are
 * able to moving around the space, and it has gravity. Collisions are
 * implemented through the usage of raycasts.*/
class Player {
private:
  Vector3 center;
  
  Mesh *lv_mesh;
  Matrix *lv_transform;
  BoundingBox *lv_bounds;

  BoundingBox bounding_box;
  Vector3 scale;

  float fall_speed;
  float movement_speed;

  float velocity_x = 0;
  float velocity_z = 0;
public:
  Player(Mesh &lv_mesh, Matrix &lv_transform, BoundingBox &lv_bounds);
  void updateCenterPosition();
  void updateBoundingBox();

  void applyGravity(double delta_time);
  void gravityRaycast();

  void movement(double delta_time);
  void moveX(double delta_time);
  void moveZ(double delta_time);

  void keyPressed();
  void KeyReleased();

  void update(double delta_time);
  void draw();

  Vector3 position;
  float ground_distance;
};
