#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/lilypad_image_1.h"
#include "images/lilypad_image_2.h"
#include "images/lilypad_image_3.h"
#include "images/lilypad_image_4.h"
#include "images/frog_sprite.h"
#include "images/home_screen.h"
#include "images/win_screen.h"
#include "images/dragonfly.h"

enum gba_state {
  START,
  PLAY,
  WIN
};

int main(void) {
  // set REG_DISPCNT to MODE3
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;
  drawFullScreenImageDMA(home_screen);
  // delay counter for home screen animation
  int delayCounter = 0;
  int pressedBack = 0;
  // create frog and lilypads, dragonflies
  struct frog frosch;
  frosch.row = 18;
  frosch.col = 19;
  frosch.width = 10;
  frosch.height = 10;
  frosch.fliesEaten = 48;
  struct dragonfly df1;
  df1.row = 105;
  df1.col = 139;
  df1.width = 10;
  df1.height = 10;
  df1.isEaten = 0;
  struct dragonfly df2;
  df2.row = 48;
  df2.col = 55;
  df2.width = 10;
  df2.height = 10;
  df2.isEaten = 0;
  struct dragonfly df3;
  df3.row = 130;
  df3.col = 19;
  df3.width = 10;
  df3.height = 10;
  df3.isEaten = 0;
  struct dragonfly df4;
  df4.row = 130;
  df4.col = 163;
  df4.width = 10;
  df4.height = 10;
  df4.isEaten = 0;
  struct finishLine fl;
  fl.row = 129;
  fl.col = 204;
  fl.height = 1;
  fl.width = 24;
  // left wall. starting at top and going down
  struct lilypad one;
  setLily(3, 1, &one);
  struct lilypad two;
  setLily(15, 1, &two);
  struct lilypad three;
  setLily(27, 1, &three);
  struct lilypad four;
  setLily(39, 1, &four);
  struct lilypad five;
  setLily(51, 1, &five);
  struct lilypad six;
  setLily(63, 1, &six);
  struct lilypad seven;
  setLily(75, 1, &seven);
  struct lilypad eight;
  setLily(87, 1, &eight);
  struct lilypad nine;
  setLily(99, 1, &nine);
  struct lilypad ten;
  setLily(111, 1, &ten);
  struct lilypad eleven;
  setLily(123, 1, &eleven);
  struct lilypad twelve;
  setLily(135, 1, &twelve);
  struct lilypad thirteen;
  setLily(147, 1, &thirteen);
  // top wall. starting at one from left and going right
  struct lilypad fourteen;
  setLily(3, 13, &fourteen);
  struct lilypad fifteen;
  setLily(3, 25, &fifteen);
  struct lilypad sixteen;
  setLily(3, 37, &sixteen);
  struct lilypad seventeen;
  setLily(3, 49, &seventeen);
  struct lilypad eighteen;
  setLily(3, 61, &eighteen);
  struct lilypad nineteen;
  setLily(3, 73, &nineteen);
  struct lilypad twenty;
  setLily(3, 85, &twenty);
  struct lilypad twentyone;
  setLily(3, 97, &twentyone);
  struct lilypad twentytwo;
  setLily(3, 109, &twentytwo);
  struct lilypad twentythree;
  setLily(3, 121, &twentythree);
  struct lilypad twentyfour;
  setLily(3, 133, &twentyfour);
  struct lilypad twentyfive;
  setLily(3, 145, &twentyfive);
  struct lilypad twentysix;
  setLily(3, 157, &twentysix);
  struct lilypad twentyseven;
  setLily(3, 169, &twentyseven);
  struct lilypad twentyeight;
  setLily(3, 181, &twentyeight);
  struct lilypad twentynine;
  setLily(3, 193, &twentynine);
  struct lilypad thirty;
  setLily(3, 205, &thirty);
  struct lilypad thirtyone;
  setLily(3, 217, &thirtyone);
  struct lilypad thirtytwo;
  setLily(3, 229, &thirtytwo);
  // right wall. starting at second from top and going down
  struct lilypad thirtythree;
  setLily(15, 229, &thirtythree);
  struct lilypad thirtyfour;
  setLily(27, 229, &thirtyfour);
  struct lilypad thirtyfive;
  setLily(39, 229, &thirtyfive);
  struct lilypad thirtysix;
  setLily(51, 229, &thirtysix);
  struct lilypad thirtyseven;
  setLily(63, 229, &thirtyseven);
  struct lilypad thirtyeight;
  setLily(75, 229, &thirtyeight);
  struct lilypad thirtynine;
  setLily(87, 229, &thirtynine);
  struct lilypad forty;
  setLily(99, 229, &forty);
  struct lilypad fortyone;
  setLily(111, 229, &fortyone);
  struct lilypad fortytwo;
  setLily(123, 229, &fortytwo);
  struct lilypad fortythree;
  setLily(135, 229, &fortythree);
  struct lilypad fortyfour;
  setLily(147, 229, &fortyfour);
  // bottom wall. starts at one from left, goes right until one from right.
  struct lilypad fortyfive;
  setLily(147, 13, &fortyfive);
  struct lilypad fortysix;
  setLily(147, 25, &fortysix);
  struct lilypad fortyseven;
  setLily(147, 37, &fortyseven);
  struct lilypad fortyeight;
  setLily(147, 49, &fortyeight);
  struct lilypad fortynine;
  setLily(147, 61, &fortynine);
  struct lilypad fifty;
  setLily(147, 73, &fifty);
  struct lilypad fiftyone;
  setLily(147, 85, &fiftyone);
  struct lilypad fiftytwo;
  setLily(147, 97, &fiftytwo);
  struct lilypad fiftythree;
  setLily(147, 109, &fiftythree);
  struct lilypad fiftyfour;
  setLily(147, 121, &fiftyfour);
  struct lilypad fiftyfive;
  setLily(147, 133, &fiftyfive);
  struct lilypad fiftysix;
  setLily(147, 145, &fiftysix);
  struct lilypad fiftyseven;
  setLily(147, 157, &fiftyseven);
  struct lilypad fiftyeight;
  setLily(147, 169, &fiftyeight);
  struct lilypad fiftynine;
  setLily(147, 181, &fiftynine);
  struct lilypad sixty;
  setLily(147, 193, &sixty);
  struct lilypad sixtyone;
  setLily(147, 205, &sixtyone);
  struct lilypad sixtytwo;
  setLily(147, 217, &sixtytwo);
  struct lilypad sixtythree;
  setLily(147, 229, &sixtythree);
  // interior lilypads. refer to reference sheet for notation
  struct lilypad a;
  setLily(15, 37, &a);
  struct lilypad b;
  setLily(27, 37, &b);
  struct lilypad c;
  setLily(39, 37, &c);
  struct lilypad d;
  setLily(51, 37, &d);
  struct lilypad e;
  setLily(63, 37, &e);
  struct lilypad f;
  setLily(63, 49, &f);
  struct lilypad g;
  setLily(63, 61, &g);
  struct lilypad h;
  setLily(39, 73, &h);
  struct lilypad i;
  setLily(51, 73, &i);
  struct lilypad j;
  setLily(63, 73, &j);
  struct lilypad k;
  setLily(39, 85, &k);
  struct lilypad l;
  setLily(51, 85, &l);
  struct lilypad m;
  setLily(63, 85, &m);
  struct lilypad n;
  setLily(39, 121, &n);
  struct lilypad o;
  setLily(51, 121, &o);
  struct lilypad p;
  setLily(39, 133, &p);
  struct lilypad q;
  setLily(51, 133, &q);
  struct lilypad v;
  setLily(15, 169, &v);
  struct lilypad t;
  setLily(27, 169, &t);
  struct lilypad r;
  setLily(39, 169, &r);
  struct lilypad s;
  setLily(51, 169, &s);
  struct lilypad u;
  setLily(51, 181, &u);
  struct lilypad w;
  setLily(51, 193, &w);
  struct lilypad x;
  setLily(51, 205, &x);
  struct lilypad y;
  setLily(51, 217, &y);
  struct lilypad z;
  setLily(99, 37, &z);
  struct lilypad aa;
  setLily(111, 37, &aa);
  struct lilypad ab;
  setLily(123, 37, &ab);
  struct lilypad ac;
  setLily(135, 37, &ac);
  struct lilypad ad;
  setLily(99, 49, &ad);
  struct lilypad ae;
  setLily(111, 49, &ae);
  struct lilypad af;
  setLily(99, 61, &af);
  struct lilypad ag;
  setLily(111, 61, &ag);
  struct lilypad ah;
  setLily(99, 97, &ah);
  struct lilypad ai;
  setLily(111, 97, &ai);
  struct lilypad aj;
  setLily(99, 109, &aj);
  struct lilypad ak;
  setLily(111, 109, &ak);
  struct lilypad al;
  setLily(87, 121, &al);
  struct lilypad am;
  setLily(87, 133, &am);
  struct lilypad an;
  setLily(87, 145, &an);
  struct lilypad ao;
  setLily(87, 157, &ao);
  struct lilypad ap;
  setLily(99, 157, &ap);
  struct lilypad aq;
  setLily(111, 157, &aq);
  struct lilypad ar;
  setLily(123, 145, &ar);
  struct lilypad as;
  setLily(135, 145, &as);
  struct lilypad at;
  setLily(87, 193, &at);
  struct lilypad au;
  setLily(99, 193, &au);
  struct lilypad av;
  setLily(111, 193, &av);
  struct lilypad aw;
  setLily(123, 193, &aw);
  struct lilypad ax;
  setLily(135, 193, &ax);
  struct lilypad ay;
  setLily(63, 121, &ay);
  struct lilypad az;
  setLily(75, 121, &az);
  struct lilypad ba;
  setLily(63, 133, &ba);
  struct lilypad bb;
  setLily(75, 133, &bb);
  struct lilypad bc;
  setLily(99, 121, &bc);





  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    waitForVBlank();
    switch (state) {
      case START:
        pressedBack = 0;
        // implement animation
        if (delayCounter == 0) {
          drawString(140, 53, "Press A/Enter to Play!", WHITE);
        } else if (delayCounter == 90) {
          drawRectDMA(140, 53, 150, 20, COLOR(11, 24, 31));
        }
        delayCounter++;
        if (delayCounter == 180) {
          delayCounter = 0;
        }
        
        


        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = PLAY;
          // Set background for game here (don't want to re-render every time)
          drawRectDMA(0, 0, 240, 160, BLUEBACKGROUND);
          drawString(16, 182, "Flies", BLACK);
          drawString(27, 182, "eaten:", BLACK);
          drawImageDMA(frosch.row, frosch.col, frosch.width, frosch.height, frog_sprite);
          drawRectDMA(fl.row, fl.col, fl.width, fl.height, BLACK);
          drawString(135, 206, "end", BLACK);
          drawImageDMA(df1.row, df1.col, df1.width, df1.height, dragonfly);
          drawImageDMA(df2.row, df2.col, df2.width, df2.height, dragonfly);
          drawImageDMA(df3.row, df3.col, df3.width, df3.height, dragonfly);
          drawImageDMA(df4.row, df4.col, df4.width, df4.height, dragonfly);
          
          // Draw lily pad images
          drawLily(&one, rand() % 4);
          drawLily(&two, rand() % 4);
          drawLily(&three, rand() % 4);
          drawLily(&four, rand() % 4);
          drawLily(&five, rand() % 4);
          drawLily(&six, rand() % 4);
          drawLily(&seven, rand() % 4);
          drawLily(&eight, rand() % 4);
          drawLily(&nine, rand() % 4);
          drawLily(&ten, rand() % 4);
          drawLily(&eleven, rand() % 4);
          drawLily(&twelve, rand() % 4);
          drawLily(&thirteen, rand() % 4);
          drawLily(&fourteen, rand() % 4);
          drawLily(&fifteen, rand() % 4);
          drawLily(&sixteen, rand() % 4);
          drawLily(&seventeen, rand() % 4);
          drawLily(&eighteen, rand() % 4);
          drawLily(&nineteen, rand() % 4);
          drawLily(&twenty, rand() % 4);
          drawLily(&twentyone, rand() % 4);
          drawLily(&twentytwo, rand() % 4);
          drawLily(&twentythree, rand() % 4);
          drawLily(&twentyfour, rand() % 4);
          drawLily(&twentyfive, rand() % 4);
          drawLily(&twentysix, rand() % 4);
          drawLily(&twentyseven, rand() % 4);
          drawLily(&twentyeight, rand() % 4);
          drawLily(&twentynine, rand() % 4);
          drawLily(&thirty, rand() % 4);
          drawLily(&thirtyone, rand() % 4);
          drawLily(&thirtytwo, rand() % 4);
          drawLily(&thirtythree, rand() % 4);
          drawLily(&thirtyfour, rand() % 4);
          drawLily(&thirtyfive, rand() % 4);
          drawLily(&thirtysix, rand() % 4);
          drawLily(&thirtyseven, rand() % 4);
          drawLily(&thirtyeight, rand() % 4);
          drawLily(&thirtynine, rand() % 4);
          drawLily(&forty, rand() % 4);
          drawLily(&fortyone, rand() % 4);
          drawLily(&fortytwo, rand() % 4);
          drawLily(&fortythree, rand() % 4);
          drawLily(&fortyfour, rand() % 4);
          drawLily(&fortyfive, rand() % 4);
          drawLily(&fortysix, rand() % 4);
          drawLily(&fortyseven, rand() % 4);
          drawLily(&fortyeight, rand() % 4);
          drawLily(&fortynine, rand() % 4);
          drawLily(&fifty, rand() % 4);
          drawLily(&fiftyone, rand() % 4);
          drawLily(&fiftytwo, rand() % 4);
          drawLily(&fiftythree, rand() % 4);
          drawLily(&fiftyfour, rand() % 4);
          drawLily(&fiftyfive, rand() % 4);
          drawLily(&fiftysix, rand() % 4);
          drawLily(&fiftyseven, rand() % 4);
          drawLily(&fiftyeight, rand() % 4);
          drawLily(&fiftynine, rand() % 4);
          drawLily(&sixty, rand() % 4);
          drawLily(&sixtyone, rand() % 4);
          drawLily(&sixtytwo, rand() % 4);
          drawLily(&sixtythree, rand() % 4);
          drawLily(&a, rand() % 4);
          drawLily(&b, rand() % 4);
          drawLily(&c, rand() % 4);
          drawLily(&d, rand() % 4);
          drawLily(&e, rand() % 4);
          drawLily(&f, rand() % 4);
          drawLily(&g, rand() % 4);
          drawLily(&h, rand() % 4);
          drawLily(&i, rand() % 4);
          drawLily(&j, rand() % 4);
          drawLily(&k, rand() % 4);
          drawLily(&l, rand() % 4);
          drawLily(&m, rand() % 4);
          drawLily(&n, rand() % 4);
          drawLily(&o, rand() % 4);
          drawLily(&p, rand() % 4);
          drawLily(&q, rand() % 4);
          drawLily(&r, rand() % 4);
          drawLily(&s, rand() % 4);
          drawLily(&t, rand() % 4);
          drawLily(&u, rand() % 4);
          drawLily(&v, rand() % 4);
          drawLily(&w, rand() % 4);
          drawLily(&x, rand() % 4);
          drawLily(&y, rand() % 4);
          drawLily(&z, rand() % 4);
          drawLily(&aa, rand() % 4);
          drawLily(&ab, rand() % 4);
          drawLily(&ac, rand() % 4);
          drawLily(&ad, rand() % 4);
          drawLily(&ae, rand() % 4);
          drawLily(&af, rand() % 4);
          drawLily(&ag, rand() % 4);
          drawLily(&ah, rand() % 4);
          drawLily(&ai, rand() % 4);
          drawLily(&aj, rand() % 4);
          drawLily(&ak, rand() % 4);
          drawLily(&al, rand() % 4);
          drawLily(&am, rand() % 4);
          drawLily(&an, rand() % 4);
          drawLily(&ao, rand() % 4);
          drawLily(&ap, rand() % 4);
          drawLily(&aq, rand() % 4);
          drawLily(&ar, rand() % 4);
          drawLily(&as, rand() % 4);
          drawLily(&at, rand() % 4);
          drawLily(&au, rand() % 4);
          drawLily(&av, rand() % 4);
          drawLily(&aw, rand() % 4);
          drawLily(&ax, rand() % 4);
          drawLily(&ay, rand() % 4);
          drawLily(&az, rand() % 4);
          drawLily(&ba, rand() % 4);
          drawLily(&bb, rand() % 4);
          drawLily(&bc, rand() % 4);
        }
        break;
      case PLAY:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
          df1.isEaten = 0;
          df2.isEaten = 0;
          df3.isEaten = 0;
          df4.isEaten = 0;
          frosch.fliesEaten = 48;
          // reset and undraw frog
          frosch.row = 18;
          frosch.col = 19;
          pressedBack = 1;
          // drawImageDMA(0, 0, 240, 160, home_screen);
          drawFullScreenImageDMA(home_screen);
        }
        /////////// ERASING //////////////////
        // undraw frog
        drawRectDMA(frosch.row, frosch.col, frosch.width, frosch.height, BLUEBACKGROUND);
        if (!pressedBack) {
          // undraw text area
        drawRectDMA(39, 182, 10, 10, BLUEBACKGROUND);
        }
        if (df1.isEaten) {
          // undraw fly
          drawRectDMA(df1.row, df1.col, df1.width, df1.height, BLUEBACKGROUND);
        }
        if (df2.isEaten) {
          // undraw fly
          drawRectDMA(df2.row, df2.col, df2.width, df2.height, BLUEBACKGROUND);
        }
        if (df3.isEaten) {
          // undraw fly
          drawRectDMA(df3.row, df3.col, df3.width, df3.height, BLUEBACKGROUND);
        }
        if (df4.isEaten) {
          // undraw fly
          drawRectDMA(df4.row, df4.col, df4.width, df4.height, BLUEBACKGROUND);
        }
        

        /////////// GAME LOGIC /////////////
        if (KEY_DOWN(BUTTON_LEFT, currentButtons)){
          // check whether the frog has left collided with any wall objects
          if (
            (frosch.col > 0) && (
            (rightLilypadCollision(frosch, two) == 0)
            && (rightLilypadCollision(frosch, three) == 0)
            && (rightLilypadCollision(frosch, four) == 0)
            && (rightLilypadCollision(frosch, five) == 0)
            && (rightLilypadCollision(frosch, six) == 0)
            && (rightLilypadCollision(frosch, seven) == 0)
            && (rightLilypadCollision(frosch, eight) == 0)
            && (rightLilypadCollision(frosch, nine) == 0)
            && (rightLilypadCollision(frosch, ten) == 0)
            && (rightLilypadCollision(frosch, eleven) == 0)
            && (rightLilypadCollision(frosch, twelve) == 0)
            && (rightLilypadCollision(frosch, a) == 0)
            && (rightLilypadCollision(frosch, b) == 0)
            && (rightLilypadCollision(frosch, c) == 0)
            && (rightLilypadCollision(frosch, d) == 0)
            && (rightLilypadCollision(frosch, k) == 0)
            && (rightLilypadCollision(frosch, l) == 0)
            && (rightLilypadCollision(frosch, m) == 0)
            && (rightLilypadCollision(frosch, p) == 0)
            && (rightLilypadCollision(frosch, q) == 0)
            && (rightLilypadCollision(frosch, af) == 0)
            && (rightLilypadCollision(frosch, ag) == 0)
            && (rightLilypadCollision(frosch, ab) == 0)
            && (rightLilypadCollision(frosch, ac) == 0)
            && (rightLilypadCollision(frosch, bc) == 0)
            && (rightLilypadCollision(frosch, ak) == 0)
            && (rightLilypadCollision(frosch, ao) == 0)
            && (rightLilypadCollision(frosch, ap) == 0)
            && (rightLilypadCollision(frosch, aq) == 0)
            && (rightLilypadCollision(frosch, ar) == 0)
            && (rightLilypadCollision(frosch, as) == 0)
            && (rightLilypadCollision(frosch, at) == 0)
            && (rightLilypadCollision(frosch, au) == 0)
            && (rightLilypadCollision(frosch, av) == 0)
            && (rightLilypadCollision(frosch, aw) == 0)
            && (rightLilypadCollision(frosch, ax) == 0)
            && (rightLilypadCollision(frosch, ba) == 0)
            && (rightLilypadCollision(frosch, bb) == 0)
            // && (rightFlyCollision(frosch, df1) == 0)
            )
          ) {
            frosch.col -= 1;
          }
        }

        if (KEY_DOWN(BUTTON_RIGHT, currentButtons)){
          if (
            (frosch.col + frosch.width) < 240 && (
            (leftLilypadCollision(frosch, thirtyseven) == 0)
            && (leftLilypadCollision(frosch, thirtyeight) == 0)
            && (leftLilypadCollision(frosch, thirtynine) == 0)
            && (leftLilypadCollision(frosch, forty) == 0)
            && (leftLilypadCollision(frosch, fortyone) == 0)
            && (leftLilypadCollision(frosch, fortytwo) == 0)
            && (leftLilypadCollision(frosch, fortythree) == 0)
            && (leftLilypadCollision(frosch, fortyfour) == 0)
            && (leftLilypadCollision(frosch, a) == 0)
            && (leftLilypadCollision(frosch, b) == 0)
            && (leftLilypadCollision(frosch, c) == 0)
            && (leftLilypadCollision(frosch, d) == 0)
            && (leftLilypadCollision(frosch, e) == 0)
            && (leftLilypadCollision(frosch, h) == 0)
            && (leftLilypadCollision(frosch, i) == 0)
            && (leftLilypadCollision(frosch, n) == 0)
            && (leftLilypadCollision(frosch, o) == 0)
            && (leftLilypadCollision(frosch, v) == 0)
            && (leftLilypadCollision(frosch, t) == 0)
            && (leftLilypadCollision(frosch, r) == 0)
            && (leftLilypadCollision(frosch, s) == 0)
            && (leftLilypadCollision(frosch, z) == 0)
            && (leftLilypadCollision(frosch, aa) == 0)
            && (leftLilypadCollision(frosch, ab) == 0)
            && (leftLilypadCollision(frosch, ac) == 0)
            && (leftLilypadCollision(frosch, ah) == 0)
            && (leftLilypadCollision(frosch, ai) == 0)
            && (leftLilypadCollision(frosch, al) == 0)
            && (leftLilypadCollision(frosch, ap) == 0)
            && (leftLilypadCollision(frosch, aq) == 0)
            && (leftLilypadCollision(frosch, ar) == 0)
            && (leftLilypadCollision(frosch, as) == 0)
            && (leftLilypadCollision(frosch, at) == 0)
            && (leftLilypadCollision(frosch, au) == 0)
            && (leftLilypadCollision(frosch, av) == 0)
            && (leftLilypadCollision(frosch, aw) == 0)
            && (leftLilypadCollision(frosch, ax) == 0)
            && (leftLilypadCollision(frosch, ay) == 0)
            && (leftLilypadCollision(frosch, az) == 0)
            // && (leftFlyCollision(frosch, df1) == 0)
            )
          ) {
            frosch.col += 1;
          }
        }

        if (KEY_DOWN(BUTTON_UP, currentButtons)){
          if (
            (frosch.row > 0) && (
            (bottomLilypadCollision(frosch, fourteen) == 0)
            && (bottomLilypadCollision(frosch, fifteen) == 0)
            && (bottomLilypadCollision(frosch, seventeen) == 0)
            && (bottomLilypadCollision(frosch, eighteen) == 0)
            && (bottomLilypadCollision(frosch, nineteen) == 0)
            && (bottomLilypadCollision(frosch, twenty) == 0)
            && (bottomLilypadCollision(frosch, twentyone) == 0)
            && (bottomLilypadCollision(frosch, twentytwo) == 0)
            && (bottomLilypadCollision(frosch, twentythree) == 0)
            && (bottomLilypadCollision(frosch, twentyfour) == 0)
            && (bottomLilypadCollision(frosch, twentyfive) == 0)
            && (bottomLilypadCollision(frosch, twentysix) == 0)
            && (bottomLilypadCollision(frosch, seven) == 0)
            && (bottomLilypadCollision(frosch, eight) == 0)
            && (bottomLilypadCollision(frosch, e) == 0)
            && (bottomLilypadCollision(frosch, f) == 0)
            && (bottomLilypadCollision(frosch, g) == 0)
            && (bottomLilypadCollision(frosch, j) == 0)
            && (bottomLilypadCollision(frosch, m) == 0)
            && (bottomLilypadCollision(frosch, s) == 0)
            && (bottomLilypadCollision(frosch, u) == 0)
            && (bottomLilypadCollision(frosch, w) == 0)
            && (bottomLilypadCollision(frosch, x) == 0)
            && (bottomLilypadCollision(frosch, y) == 0)
            && (bottomLilypadCollision(frosch, ae) == 0)
            && (bottomLilypadCollision(frosch, ag) == 0)
            && (bottomLilypadCollision(frosch, ai) == 0)
            && (bottomLilypadCollision(frosch, ak) == 0)
            && (bottomLilypadCollision(frosch, bc) == 0)
            && (bottomLilypadCollision(frosch, am) == 0)
            && (bottomLilypadCollision(frosch, an) == 0)
            && (bottomLilypadCollision(frosch, aq) == 0)
            )
          ) {
            frosch.row -= 1;
          }
        }

        if (KEY_DOWN(BUTTON_DOWN, currentButtons)){
          if (
            (frosch.row + frosch.height) < 160 && (
            (topLilypadCollision(frosch, fortyfive) == 0)
            && (topLilypadCollision(frosch, fortysix) == 0)
            && (topLilypadCollision(frosch, fortyeight) == 0)
            && (topLilypadCollision(frosch, fortynine) == 0)
            && (topLilypadCollision(frosch, fifty) == 0)
            && (topLilypadCollision(frosch, fiftyone) == 0)
            && (topLilypadCollision(frosch, fiftytwo) == 0)
            && (topLilypadCollision(frosch, fiftythree) == 0)
            && (topLilypadCollision(frosch, fiftyfour) == 0)
            && (topLilypadCollision(frosch, fiftyfive) == 0)
            && (topLilypadCollision(frosch, fiftyseven) == 0)
            && (topLilypadCollision(frosch, fiftyeight) == 0)
            && (topLilypadCollision(frosch, fiftynine) == 0)
            && (topLilypadCollision(frosch, sixty) == 0)
            && (topLilypadCollision(frosch, sixtyone) == 0)
            && (topLilypadCollision(frosch, sixtytwo) == 0)
            && (topLilypadCollision(frosch, sixtythree) == 0)
            && (topLilypadCollision(frosch, f) == 0)
            && (topLilypadCollision(frosch, g) == 0)
            && (topLilypadCollision(frosch, h) == 0)
            && (topLilypadCollision(frosch, k) == 0)
            && (topLilypadCollision(frosch, n) == 0)
            && (topLilypadCollision(frosch, p) == 0)
            && (topLilypadCollision(frosch, z) == 0)
            && (topLilypadCollision(frosch, ad) == 0)
            && (topLilypadCollision(frosch, af) == 0)
            && (topLilypadCollision(frosch, ah) == 0)
            && (topLilypadCollision(frosch, aj) == 0)
            && (topLilypadCollision(frosch, an) == 0)
            && (topLilypadCollision(frosch, ao) == 0)
            && (topLilypadCollision(frosch, ar) == 0)
            && (topLilypadCollision(frosch, at) == 0)
            )
          ) {
            frosch.row += 1;
          }
        }
        if (topFlyCollision(frosch, df1) || bottomFlyCollision(frosch, df1) || rightFlyCollision(frosch, df1) || leftFlyCollision(frosch, df1)) {
          df1.isEaten = 1;
          frosch.fliesEaten += 1;
        }
        if (topFlyCollision(frosch, df2) || bottomFlyCollision(frosch, df2) || rightFlyCollision(frosch, df2) || leftFlyCollision(frosch, df2)) {
          df2.isEaten = 1;
          frosch.fliesEaten += 1;
        }
        if (topFlyCollision(frosch, df3) || bottomFlyCollision(frosch, df3) || rightFlyCollision(frosch, df3) || leftFlyCollision(frosch, df3)) {
          df3.isEaten = 1;
          frosch.fliesEaten += 1;
        }
        if (topFlyCollision(frosch, df4) || bottomFlyCollision(frosch, df4) || rightFlyCollision(frosch, df4) || leftFlyCollision(frosch, df4)) {
          df4.isEaten = 1;
          frosch.fliesEaten += 1;
        }
        if (((frosch.row + frosch.height) == fl.row) && frosch.col >= (fl.col - 4)) {
          state = WIN;
        }
        /////////// REDRAWING  /////////////////
        if (!pressedBack) {
          drawImageDMA(frosch.row, frosch.col, frosch.width, frosch.height, frog_sprite);
          drawChar(39, 182, frosch.fliesEaten, BLACK);
        }
        
        break;
      case WIN:
        drawImageDMA(0, 0, 240, 160, win_screen);
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          // reset game
          state = START;
          df1.isEaten = 0;
          df2.isEaten = 0;
          df3.isEaten = 0;
          df4.isEaten = 0;
          frosch.fliesEaten = 48;
          frosch.row = 18;
          frosch.col = 19;
          pressedBack = 1;
          drawFullScreenImageDMA(home_screen);
        }
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  return 0;
}



int leftLilypadCollision(struct frog f, struct lilypad l) {
  int lilyLeft = l.col;
  int frogRight = f.col + f.width;
  int lilyTop = l.row;
  int lilyBottom = l.row + l.height;
  int frogTop = f.row;
  int frogBottom = f.row + f.height;
  if (
    (lilyLeft == frogRight) &&
    (((lilyTop <= frogTop) && (frogTop <= lilyBottom)) || ((lilyTop <= frogBottom) && (frogBottom <= lilyBottom)))
  ) {
    return 1;
  } else {
    return 0;
  }

}
int rightLilypadCollision(struct frog f, struct lilypad l) {
  int lilyRight = l.col + l.width;
  int frogLeft = f.col;
  int lilyTop = l.row;
  int lilyBottom = l.row + l.height;
  int frogTop = f.row;
  int frogBottom = f.row + f.height;
  if (
    (lilyRight == frogLeft) &&
    (((lilyTop <= frogTop) && (frogTop <= lilyBottom)) || ((lilyTop <= frogBottom) && (frogBottom <= lilyBottom)))
  ) {
    return 1;
  } else {
    return 0;
  }
}
int bottomLilypadCollision(struct frog f, struct lilypad l) {
  int lilyBottom = l.row + l.height;
  int lilyLeft = l.col;
  int frogTop = f.row;
  int frogLeft = f.col;
  int lilyRight = l.col + l.width;
  int frogRight = f.col + f.width;
  if (
  (lilyBottom == frogTop) &&
    (((lilyLeft <= frogLeft) && (frogLeft <= lilyRight)) || ((lilyLeft <= frogRight) && (frogRight <= lilyRight)))
  ) {
    return 1;
  } else {
    return 0;
  }
}
int topLilypadCollision(struct frog f, struct lilypad l) {
  int frogLeft = f.col;
  int lilyRight = l.col + l.width;
  int frogRight = f.col + f.width;
  int lilyTop = l.row;
  int frogBottom = f.row + f.height;
  int lilyLeft = l.col;
  if (
  (lilyTop == frogBottom) &&
    (((lilyLeft <= frogLeft) && (frogLeft <= lilyRight)) || ((lilyLeft <= frogRight) && (frogRight <= lilyRight)))
  ) {
    return 1;
  } else {
    return 0;
  }
}

int topFlyCollision(struct frog f, struct dragonfly df) {
  int frogLeft = f.col;
  int flyRight = df.col + df.width;
  int frogRight = f.col + f.width;
  int flyTop = df.row;
  int frogBottom = f.row + f.height;
  int flyLeft = df.col;
  if (
    (!df.isEaten) &&
    (flyTop == frogBottom) &&
    (((flyLeft <= frogLeft) && (frogLeft <= flyRight)) || ((flyLeft <= frogRight) && (frogRight <= flyRight)))
  ) {
    return 1;
  } else {
    return 0;
  }
}

int bottomFlyCollision (struct frog f, struct dragonfly df) {
  int flyBottom = df.row + df.height;
  int flyLeft = df.col;
  int frogTop = f.row;
  int frogLeft = f.col;
  int flyRight = df.col + df.width;
  int frogRight = f.col + f.width;
  if ( (!df.isEaten) &&
    (flyBottom == frogTop) &&
    (((flyLeft <= frogLeft) && (frogLeft <= flyRight)) || ((flyLeft <= frogRight) && (frogRight <= flyRight)))
  ) {
    return 1;
  } else {
    return 0;
  }
}

int rightFlyCollision(struct frog f, struct dragonfly l) {
  int flyRight = l.col + l.width;
  int frogLeft = f.col;
  int flyTop = l.row;
  int flyBottom = l.row + l.height;
  int frogTop = f.row;
  int frogBottom = f.row + f.height;
  if (
    (!l.isEaten) &&
    (flyRight == frogLeft) &&
    (((flyTop <= frogTop) && (frogTop <= flyBottom)) || ((flyTop <= frogBottom) && (frogBottom <= flyBottom)))
  ) {
    return 1;
  } else {
    return 0;
  }
}

int leftFlyCollision(struct frog f, struct dragonfly l) {
  int flyLeft = l.col;
  int frogRight = f.col + f.width;
  int flyTop = l.row;
  int flyBottom = l.row + l.height;
  int frogTop = f.row;
  int frogBottom = f.row + f.height;
  if (
    (!l.isEaten) &&
    (flyLeft == frogRight) &&
    (((flyTop <= frogTop) && (frogTop <= flyBottom)) || ((flyTop <= frogBottom) && (frogBottom <= flyBottom)))
  ) {
    return 1;
  } else {
    return 0;
  }

}

void setLily(int r, int c, struct lilypad *l) {
  l->row = r;
  l->col = c;
  l->width = 10;
  l->height = 10;
}

void drawLily(struct lilypad *l, int num) {
  // num is a random integer 0-3 denoting which orientation the lilypad should have
  // possible problem: how to make sure the lilypads only draw when game is loaded up? not every loop?
  if (num == 0) {
    drawImageDMA(l->row, l->col, l->width, l->height, lilypad_image_1);
  } else if (num == 1) {
    drawImageDMA(l->row, l->col, l->width, l->height, lilypad_image_2);
  } else if (num == 2) {
    drawImageDMA(l->row, l->col, l->width, l->height, lilypad_image_3);
  } else if (num == 3) {
    drawImageDMA(l->row, l->col, l->width, l->height, lilypad_image_4);
  }
}