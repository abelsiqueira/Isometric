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
