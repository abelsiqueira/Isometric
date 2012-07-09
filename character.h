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
#ifndef character_h
#define character_h

#include <allegro5/allegro.h>
#include <cmath>

const unsigned int constFrames = 8;
const unsigned int updatesPerFrame = 4;
const float scale = 4.0/3.0;
const float baseSpeed = 8.0/updatesPerFrame;

enum State { stopped, moving };
enum Direction { en_north=0, en_northeast=1, en_east=2, en_southeast=3, 
                 en_south=4, en_southwest=5, en_west=6, en_northwest=7 };

class Character {
  public:
    Character ();
    ~Character ();

    void Update ();
    void Draw () const;

    void Stop () {
      state = stopped;
    }
    void Move (Direction d) {
      state = moving;
      direction = d;
    }
    void Run () {
      isRunning = true;
      speed = 2*baseSpeed;
    }
    void Walk () {
      isRunning = false;
      speed = baseSpeed;
    }
  private:
    float x, y;
    unsigned int frame, updateCount;
    bool isRunning;
    float speed;

    State state;
    Direction direction;
    ALLEGRO_BITMAP *bitmap_stopped, *bitmap_walking, *bitmap_running;
};

#endif
