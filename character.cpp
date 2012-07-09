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
  state = stopped;
  direction = en_south;
  string path("Images/Character/walking ");

  east      = new ALLEGRO_BITMAP*[constFrames];
  west      = new ALLEGRO_BITMAP*[constFrames];
  north     = new ALLEGRO_BITMAP*[constFrames];
  south     = new ALLEGRO_BITMAP*[constFrames];
  northeast = new ALLEGRO_BITMAP*[constFrames];
  northwest = new ALLEGRO_BITMAP*[constFrames];
  southeast = new ALLEGRO_BITMAP*[constFrames];
  southwest = new ALLEGRO_BITMAP*[constFrames];
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "e000" << i << ".bmp";
    east[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(east[i], al_map_rgb(111, 79, 51));
  }
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "w000" << i << ".bmp";
    west[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(west[i], al_map_rgb(111, 79, 51));
  }
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "n000" << i << ".bmp";
    north[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(north[i], al_map_rgb(111, 79, 51));
  }
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "s000" << i << ".bmp";
    south[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(south[i], al_map_rgb(111, 79, 51));
  }
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "ne000" << i << ".bmp";
    northeast[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(northeast[i], al_map_rgb(111, 79, 51));
  }
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "nw000" << i << ".bmp";
    northwest[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(northwest[i], al_map_rgb(111, 79, 51));
  }
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "se000" << i << ".bmp";
    southeast[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(southeast[i], al_map_rgb(111, 79, 51));
  }
  for (unsigned int i = 0; i < constFrames; i++) {
    stringstream aux;
    aux << path << "sw000" << i << ".bmp";
    southwest[i] = al_load_bitmap(aux.str().c_str());
    al_convert_mask_to_alpha(southwest[i], al_map_rgb(111, 79, 51));
  }
}

Character::~Character () {
  for (unsigned int i = 0; i < constFrames; i++) {
    al_destroy_bitmap(east[i]);
    al_destroy_bitmap(west[i]);
    al_destroy_bitmap(north[i]);
    al_destroy_bitmap(south[i]);
    al_destroy_bitmap(northeast[i]);
    al_destroy_bitmap(southeast[i]);
    al_destroy_bitmap(northwest[i]);
    al_destroy_bitmap(southwest[i]);
  }
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
      if (y <= -96) y = 720;
      break;
    case en_south:
      y += speed;
      if (y >= 720) y = -96;
      break;
    case en_east:
      x += speed*scale;
      if (x >= 1280) x = -96;
      break;
    case en_west:
      x -= speed*scale;
      if (x <= -96) x = 1280;
      break;
    case en_northwest:
      x -= speed*scale/aux;
      y -= speed/aux;
      if (y <= -96) y = 720;
      if (x <= -96) x = 1280;
      break;
    case en_northeast:
      x += speed*scale/aux;
      y -= speed/aux;
      if (y <= -96) y = 720;
      if (x >= 1280) x = -96;
      break;
    case en_southwest:
      x -= speed*scale/aux;
      y += speed/aux;
      if (y >= 720) y = -96;
      if (x <= -96) x = 1280;
      break;
    case en_southeast:
      x += speed*scale/aux;
      y += speed/aux;
      if (y >= 720) y = -96;
      if (x >= 1280) x = -96;
      break;
    default:
      break;
  }
}

void Character::Draw () const {
  switch (direction) {
    case en_north:
      al_draw_bitmap(north[frame], x - 24, y - 24, 0);
      break;
    case en_south:
      al_draw_bitmap(south[frame], x - 24, y - 24, 0);
      break;
    case en_east:
      al_draw_bitmap(east[frame], x - 24, y - 24, 0);
      break;
    case en_west:
      al_draw_bitmap(west[frame], x - 24, y - 24, 0);
      break;
    case en_northwest:
      al_draw_bitmap(northwest[frame], x - 24, y - 24, 0);
      break;
    case en_northeast:
      al_draw_bitmap(northeast[frame], x - 24, y - 24, 0);
      break;
    case en_southeast:
      al_draw_bitmap(southeast[frame], x - 24, y - 24, 0);
      break;
    case en_southwest:
      al_draw_bitmap(southwest[frame], x - 24, y - 24, 0);
      break;
  }
}
