// player.cpp
#include <raylib.h>
#include <raymath.h>
#include "player.h"

#define HALF(number) number / 2


Player::Player(Mesh &lv_mesh, Matrix &lv_transform, BoundingBox &lv_bound)
{
  position = {5, 20, 5};
  scale = {2, 8, 2};

  this->lv_mesh = &lv_mesh;
  this->lv_transform = &lv_transform;
  this->lv_bounds = &lv_bound;

  fall_speed = 0.25f;
  movement_speed = 0.25f;
  ground_distance = 9999;

  updateCenterPosition();
  updateBoundingBox();
}

void Player::update(double delta_time) {
  applyGravity(delta_time);
  movement(delta_time);

  if (position.y <= -10) {
    position = {5, 20, 5};
  }
}

void Player::applyGravity(double delta_time) {
  position.y -= fall_speed * delta_time;
  updateCenterPosition();
  updateBoundingBox();

  if (CheckCollisionBoxes(bounding_box, *lv_bounds) == false) {
    return;
  }
  else {
    gravityRaycast();
  }
}

/* This is for checking if the player has clipped into the ground after
 * having gravity applied to them, and corrects their Y position. This is
 * down by shooting a raycast from the player's center position, directly
 * towards the ground.*/
void Player::gravityRaycast() {
  Vector3 direction = {0, -1, 0};

  Ray raycast = {center, direction};
  auto hit_info = GetRayCollisionMesh(raycast, *lv_mesh, *lv_transform);

  if (hit_info.hit == false) {
    ground_distance = 9999;
    return;
  }

  Vector3 hit_position = hit_info.point;
  ground_distance = position.y - hit_position.y;

  if (position.y < hit_position.y) {
    position.y = hit_position.y;
    ground_distance = 0;

    updateCenterPosition();
    updateBoundingBox();
  }
}

void Player::movement(double delta_time) {
  bool moving = velocity_x || velocity_z;

  if (velocity_x != 0) {
    moveX(delta_time);
  }
  if (velocity_z != 0) {
    moveZ(delta_time);
  }
  if (moving) {
    updateBoundingBox();
    updateCenterPosition();
  }
}

/* For moving the player on the X axis when called. Also prevents clipping
 * using a raycast starting from the player's center position towards
 * whatever direction the player is moving in.*/
void Player::moveX(double delta_time) {
  float direction_x = Normalize(velocity_x, 0, 1) * 4;
  float offset_x = position.x + (HALF(scale.x) * direction_x);

  Vector3 direction = {direction_x, 0, 0};

  Ray raycast = {center, direction};
  auto hit_info = GetRayCollisionMesh(raycast, *lv_mesh, *lv_transform);

  bool can_move_fully = false;

  if (hit_info.hit) {
    Vector3 hit_position = hit_info.point;
    float next_x = offset_x + (velocity_x * delta_time);

    bool moving_right = direction_x > 0;
    bool clipped_right = next_x > hit_position.x;

    bool moving_left = direction_x < 0;
    bool clipped_left = next_x < hit_position.x;

    if (moving_right && clipped_right) {
      position.x = hit_position.x - HALF(scale.x);
    }
    else if (moving_left && clipped_left) {  
      position.x = hit_position.x + HALF(scale.x);
    }
    else {
      can_move_fully = true;
    }
  }
  else {
    can_move_fully = true;
  }

  if (can_move_fully) {
    position.x += velocity_x * delta_time;
  } 
}

/* Functions virtually the same as moveX, except on the Z axis. To prevent
 * the player from clipping into the terrain, a ray is casted from the
 * player's center position, towards whatever direction the player is
 * moving in at the time.*/
void Player::moveZ(double delta_time) {
  float direction_z = Normalize(velocity_z, 0, 1) * 4;
  float offset_z = position.z + (HALF(scale.z) * direction_z);

  Vector3 direction = {0, 0, direction_z};

  Ray raycast = {center, direction};
  auto hit_info = GetRayCollisionMesh(raycast, *lv_mesh, *lv_transform);

  bool can_move_fully = false;

  if (hit_info.hit) {
    Vector3 hit_position = hit_info.point;
    float next_z = offset_z + (velocity_z * delta_time);

    bool moving_down = direction_z > 0;
    bool clipped_down = next_z > hit_position.z;

    bool moving_up = direction_z < 0;
    bool clipped_up = next_z < hit_position.z;

    if (moving_down && clipped_down) {
      position.z = hit_position.z - HALF(scale.z);
    }
    else if (moving_up && clipped_up) {
      position.z = hit_position.z + HALF(scale.z);
    }
    else {
      can_move_fully = true;
    }
  }
  else {
    can_move_fully = true;
  }

  if (can_move_fully) {
    position.z += velocity_z * delta_time;
  }
}

/* For updating the player's center position. Should be called after the
 * the player's base position has be changed in any way as the player's
 * center position is used as the start point of raycasts.*/
void Player::updateCenterPosition() {
  float centerY = position.y + HALF(scale.y);
  center = {position.x, centerY, position.z};
}

/* For updating the player's bounding box to their correct scale and 
 * position. This is typically called after the player's base position is
 * changed in any significant way.*/
void Player::updateBoundingBox() {
  float minX = position.x - HALF(scale.x);
  float minY = position.y;
  float minZ = position.z - HALF(scale.z);

  float maxX = position.x + HALF(scale.x);
  float maxY = position.y + scale.y;
  float maxZ = position.z + HALF(scale.z);

  Vector3 min_position = {minX, minY, minZ};
  Vector3 max_position = {maxX, maxY, maxZ};
  bounding_box = {min_position, max_position};
}

void Player::keyPressed() {
  if (IsKeyPressed(KEY_D)) {
    velocity_x += movement_speed;
  }
  if (IsKeyPressed(KEY_A)) {
    velocity_x -= movement_speed;
  }
  if (IsKeyPressed(KEY_S)) {
    velocity_z += movement_speed;
  }
  if (IsKeyPressed(KEY_W)) {
    velocity_z -= movement_speed;
  }
  
  if (IsKeyPressed(KEY_R)) {
    position.y = 20;
  }
}

void Player::KeyReleased() {
  if (IsKeyReleased(KEY_D)) {
    velocity_x -= movement_speed;
  }
  if (IsKeyReleased(KEY_A)) {
    velocity_x += movement_speed;
  }
  if (IsKeyReleased(KEY_S)) {
    velocity_z -= movement_speed;
  }
  if (IsKeyReleased(KEY_W)) {
    velocity_z += movement_speed;
  }
}

void Player::draw() {
  Vector3 line_start = {position.x, 20, position.z};
  Vector3 line_end = {position.x, -20, position.z};

  DrawLine3D(line_start, line_end, BLUE);
  DrawCubeV(center, scale, RED);
  DrawBoundingBox(bounding_box, YELLOW);
}
