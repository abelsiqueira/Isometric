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
const float speed = 8.0/updatesPerFrame;

enum State { stopped, moving };
enum Direction { en_north, en_northeast, en_east, en_southeast, en_south, 
                 en_southwest, en_west, en_northwest };

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
  private:
    float x, y;
    unsigned int frame, updateCount;

    State state;
    Direction direction;
    ALLEGRO_BITMAP **east, **west, **north, **south, **northwest,
                   **northeast, **southeast, **southwest;
};

#endif
