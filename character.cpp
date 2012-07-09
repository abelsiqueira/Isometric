/* Copyright 2012 - Abel Soares Siqueira
 * 
 * This file is part of Isometric.
 * 
 * Isometric is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Isometric is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Isometric.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "character.h"
#include <string>
#include <iostream>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

using namespace std;

Character::Character () {
  x = 400;
  y = 400;
  updateCount = 0;
  frame = 0;
  speed = baseSpeed;
  isRunning = false;
  state = stopped;
  direction = en_south;
  string path("Images/Character/walking ");

  bitmap_walking = al_load_bitmap("Images/Character/walking.bmp");
  bitmap_stopped = al_load_bitmap("Images/Character/stopped.bmp");
  bitmap_running = al_load_bitmap("Images/Character/running.bmp");

  al_convert_mask_to_alpha(bitmap_walking, al_map_rgb(111, 79, 51));
  al_convert_mask_to_alpha(bitmap_stopped, al_map_rgb(111, 79, 51));
  al_convert_mask_to_alpha(bitmap_running, al_map_rgb(111, 79, 51));
}

Character::~Character () {
  al_destroy_bitmap(bitmap_running);
  al_destroy_bitmap(bitmap_walking);
  al_destroy_bitmap(bitmap_stopped);
}

void Character::Update () {
  if (state == stopped)
    return;

  if (++updateCount == updatesPerFrame) {
    if (++frame == constFrames) {
      frame = 0;
    }
    updateCount = 0;
  }

  float aux = sqrt(2);
  switch (direction) {
    case en_north:
      y -= speed;
      if (y <= -48) y = 720 + 48;
      break;
    case en_south:
      y += speed;
      if (y >= 720 + 48) y = -48;
      break;
    case en_east:
      x += speed*scale;
      if (x >= 1280 + 48) x = -48;
      break;
    case en_west:
      x -= speed*scale;
      if (x <= -48) x = 1280 + 48;
      break;
    case en_northwest:
      x -= speed*scale/aux;
      y -= speed/aux;
      if (y <= -48) y = 720 + 48;
      if (x <= -48) x = 1280 + 48;
      break;
    case en_northeast:
      x += speed*scale/aux;
      y -= speed/aux;
      if (y <= -48) y = 720 + 48;
      if (x >= 1280 + 48) x = -48;
      break;
    case en_southwest:
      x -= speed*scale/aux;
      y += speed/aux;
      if (y >= 720 + 48) y = -48;
      if (x <= -48) x = 1280 + 48;
      break;
    case en_southeast:
      x += speed*scale/aux;
      y += speed/aux;
      if (y >= 720 + 48) y = -48;
      if (x >= 1280 + 48) x = -48;
      break;
    default:
      break;
  }
}

void Character::Draw () const {
  if ( (state == moving) && (!isRunning) )
    al_draw_bitmap_region(bitmap_walking, frame*96, direction*96, 96, 96, x - 48, y - 48, 0);
  else if ( (state == moving) && isRunning)
    al_draw_bitmap_region(bitmap_running, frame*96, direction*96, 96, 96, x - 48, y - 48, 0);
  else if (state == stopped)
    al_draw_bitmap_region(bitmap_stopped, 0, direction*96, 96, 96, x - 48, y - 48, 0);
}
