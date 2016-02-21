#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#define PIN 9
#define numPixels 73 // we cut off a corner light

typedef struct {
  int pos;
  boolean dir;
  int size;
  int r;
  int g;
  int b;
} Spr_mover;

int a = 0;

Spr_mover spr[] = {{0, true, 4, 255, 0, 0},                   {numPixels / 6, true, 5, 0, 255, 0},        {numPixels / 3, true, 4, 0, 0, 255},
  {numPixels * 2 / 3, false, 5, 255, 255, 0}, {numPixels * 5 / 6, false, 5, 0, 255, 255}, {numPixels, false, 4, 255, 0, 255}
};

double timer = 20;
int currentTime = 0;

Spr_mover sprsprspr = {0, true, 2, 0, 0, 0};
int rainbow[numPixels * 3];
Spr_mover trash = { -1, false, -1, -1, -1, -1};
Spr_mover colorBG = { -1, false, -1, 0, 0, 0};
#define SPR_SIZE (sizeof(spr)/sizeof(Spr_mover))
Spr_mover inLoc[SPR_SIZE];
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);
int rCount = 0;
int r1 = -1;
int r2 = -1;
int count = 0;
int num = 0;
int loopCounter = 0;
int R[numPixels];
int G[numPixels];
int B[numPixels];




void setup() {
  strip2.begin();
  strip2.clear();
  strip2.show();
  strip.begin();
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  strip.show();
  num = 7;

  for (int i = 0; i < numPixels; i++) {

    int mmeetthh = numPixels / 6;
    double meth = 255.0 / mmeetthh;

    if (i < mmeetthh) {
      rainbow[i] = 255;
      rainbow[i + numPixels] = (int)(meth * i);
      rainbow[i + numPixels * 2] = 0;
    } else if (i < mmeetthh * 2) {
      rainbow[i] = 255 - (int)(meth * (i % mmeetthh));
      rainbow[i + numPixels] = 255;
      rainbow[i + numPixels * 2] = 0;
    } else if (i < mmeetthh * 3) {
      rainbow[i] = 0;
      rainbow[i + numPixels] = 255;
      rainbow[i + numPixels * 2] = (int)(meth * (i % mmeetthh));
    } else if (i < mmeetthh * 4) {
      rainbow[i] = 0;
      rainbow[i + numPixels] = 255 - (int)(meth * (i % mmeetthh));
      rainbow[i + numPixels * 2] = 255;
    } else if (i < mmeetthh * 5) {
      rainbow[i] = (int)(meth * (i % mmeetthh));
      rainbow[i + numPixels] = 0;
      rainbow[i + numPixels * 2] = 255;
    } else if (i < mmeetthh * 6) {
      rainbow[i] = 255;
      rainbow[i + numPixels] = 0;
      rainbow[i + numPixels * 2] = 255 - (int)(meth * (i % mmeetthh));
    }
  }

  //  Sprites[0].pos =
  //  Sprites->pos =
  //
  //  Sprites[1].pos =
  //  Sprites+1->pos
  //  for (i = o...
  //    moveSprite(&sprites[i])
  //    moveSprite(sprites+i);
}

void crawling(int r, int g, int b, int r2, int g2, int b2, boolean left)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < numPixels / 20.0 * timer; j += 4)
    {
      if (left)
      {
        if (i % 4 == 0)
        {
          strip.setPixelColor(j, r, g, b);
          strip.setPixelColor(j + 1, r, g, b);
          strip.setPixelColor(j + 2, r2, g2, b2);
          strip.setPixelColor(j + 3, r2, g2, b2);
        }
        else if (i % 4 == 1)
        {
          strip.setPixelColor(j, r2, g2, b2);
          strip.setPixelColor(j + 1, r, g, b);
          strip.setPixelColor(j + 2, r, g, b);
          strip.setPixelColor(j + 3, r2, g2, b2);
        }
        else if (i % 4 == 2)
        {
          strip.setPixelColor(j, r2, g2, b2);
          strip.setPixelColor(j + 1, r2, g2, b2);
          strip.setPixelColor(j + 2, r, g, b);
          strip.setPixelColor(j + 3, r, g, b);
        }
        else if (i % 4 == 3)
        {
          strip.setPixelColor(j, r, g, b);
          strip.setPixelColor(j + 1, r2, g2, b2);
          strip.setPixelColor(j + 2, r2, g2, b2);
          strip.setPixelColor(j + 3, r, g, b);
        }
      }
      else
      {
        if (i % 4 == 0)
        {

          strip.setPixelColor(j, r, g, b);
          strip.setPixelColor(j + 1, r2, g2, b2);
          strip.setPixelColor(j + 2, r2, g2, b2);
          strip.setPixelColor(j + 3, r, g, b);
        }
        else if (i % 4 == 1)
        {
          strip.setPixelColor(j, r2, g2, b2);
          strip.setPixelColor(j + 1, r2, g2, b2);
          strip.setPixelColor(j + 2, r, g, b);
          strip.setPixelColor(j + 3, r, g, b);
        }
        else if (i % 4 == 2)
        {
          strip.setPixelColor(j, r2, g2, b2);
          strip.setPixelColor(j + 1, r, g, b);
          strip.setPixelColor(j + 2, r, g, b);
          strip.setPixelColor(j + 3, r2, g2, b2);
        }
        else if (i % 4 == 3)
        {
          strip.setPixelColor(j, r, g, b);
          strip.setPixelColor(j + 1, r, g, b);
          strip.setPixelColor(j + 2, r2, g2, b2);
          strip.setPixelColor(j + 3, r2, g2, b2);
        }
      }
    }
    strip.show();
    delay(60);
  }
}

void moveSprite(Spr_mover *p) {
  if (p->dir)
    p->pos ++;
  else
    p->pos --;
}




void party(int location, int mini, int maxi) {
  strip.setPixelColor(location, random(mini, maxi), random(mini, maxi), random(mini, maxi));
}


void setAll(int r, int g, int b) {
  for (int i = 0; i < numPixels; i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void setEveryOther(int r, int g, int b) {
  for (int i = 0; i < numPixels; i += 2) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void fadeTo(int r, int g, int b) {
  double rFade = r / 100.0;
  double gFade = g / 100.0;
  double bFade = b / 100.0;
  double r1 = r;
  double g1 = g;
  double b1 = b;
  for (int i = 0; i < 101; i++) {
    r1 += rFade;
    g1 += gFade;
    b1 += bFade;
    setAll((int)r1, (int)g1, (int)b1);
    strip.show();
    delay(2);
  }
}

void fadeFromTo(int r, int g, int b, int r2, int g2, int b2) {
  double rFade = (r2 - r) / 100.0;
  double gFade = (g2 - g) / 100.0;
  double bFade = (b2 - b) / 100.0;
  double r1 = r;
  double g1 = g;
  double b1 = b;
  for (int i = 0; i < 101; i++) {
    r1 += rFade;
    g1 += gFade;
    b1 += bFade;
    if (i != 100)
      setAll((int)r1, (int)g1, (int)b1);
    else if (i == 100)
      setAll(r2, g2, b2);
    if (i <= 23 || i >= 77)
      delay(8);
    delay(2);
  }
  delay(30);
}

void bouncy(Spr_mover *spr) {

  if (spr->pos == 0)
    spr->dir = true;
  if (spr->pos == numPixels - 1 - (spr->size))
    spr->dir = false;

  moveSprite(spr);
}

void allBouncy() {
  for (int i = 0; i < SPR_SIZE; i++) {

    if (spr[i].pos + spr[i].size == 0)
      spr[i].dir = true;
    if (spr[i].pos == numPixels - 1)
      spr[i].dir = false;

    moveSprite(&spr[i]);
  }
}

void allThrough() {

  for (int i = 0; i < SPR_SIZE; i++) {
    moveSprite(&spr[i]);

    if (spr[i].pos == numPixels && spr[i].dir)
      spr[i].pos = 0;
    if (spr[i].pos + spr[i].size == 0 && !spr[i].dir)
      spr[i].pos = numPixels - spr[i].size;
  }
}

void loopThrough(Spr_mover *spr) {

  moveSprite(spr);

  if (spr->pos == numPixels && spr->dir)
    spr->pos = 0;
  if (spr->pos + spr->size == 0 && !spr->dir)
    spr->pos = numPixels - spr->size;
}


void allBouncy2() {
  for (int i = 0; i < SPR_SIZE; i++) {

    if (spr[i].pos + spr[i].size == 0)
      spr[i].dir = true;
    if (spr[i].pos == numPixels - 1)
      spr[i].dir = false;

    moveSprite(&spr[i]);
  }
}

void receiveEvent(int howMany) {
  num = Wire.read();
  Serial.println(num);
}

boolean inLocationFade(int pixel) {
  for (int i = 0; i < SPR_SIZE; i++) {
    inLoc[i] = trash;
  }
  int var = 0;
  for (int i = 0; i < SPR_SIZE; i++) {
    if (spr[i].pos < pixel && (spr[i].pos + spr[i].size) >= pixel) {
      inLoc[var].pos = spr[i].pos;
      inLoc[var].dir = spr[i].dir;
      inLoc[var].size = spr[i].size;
      if (inLoc[var].dir) {
        inLoc[var].r = (int)(spr[i].r * ((double)(pixel - inLoc[var].pos) / inLoc[var].size));
        inLoc[var].g = (int)(spr[i].g * ((double)(pixel - inLoc[var].pos) / inLoc[var].size));
        inLoc[var].b = (int)(spr[i].b * ((double)(pixel - inLoc[var].pos) / inLoc[var].size));
      }
      else {
        if (inLoc[var].pos == pixel) {

          inLoc[var].r = spr[i].r;
          inLoc[var].g = spr[i].g;
          inLoc[var].b = spr[i].b;
        } else {
          inLoc[var].r = (int)(spr[i].r * ((double)(inLoc[var].pos - pixel) / inLoc[var].size));
          inLoc[var].g = (int)(spr[i].g * ((double)(inLoc[var].pos - pixel) / inLoc[var].size));
          inLoc[var].b = (int)(spr[i].b * ((double)(inLoc[var].pos - pixel) / inLoc[var].size));
        }
      }
      var++;
    }
  }
  return (inLoc[0].size != trash.size);

}

boolean inLocation(int pixel) {
  for (int i = 0; i < SPR_SIZE; i++) {
    inLoc[i] = trash;
  }
  int var = 0;
  for (int i = 0; i < SPR_SIZE; i++) {
    if (spr[i].pos < pixel && (spr[i].pos + spr[i].size) >= pixel) {
      inLoc[var].pos = spr[i].pos;
      inLoc[var].dir = spr[i].dir;
      inLoc[var].size = spr[i].size;
      inLoc[var].r = spr[i].r;
      inLoc[var].g = spr[i].g;
      inLoc[var].b = spr[i].b;
      var++;
    }
  }
  return (inLoc[0].size != trash.size);
}

void draw() {
  for (int pixel = 0; pixel < numPixels; pixel++) {

    if (inLocation(pixel)) {
      int amountInLoc = 0;
      for (int i = 0; i < SPR_SIZE; i++) {
        if (inLoc[i].size == trash.size) {
          break;
        }
        amountInLoc++;
      }
      int r[amountInLoc + 1];
      int g[amountInLoc + 1];
      int b[amountInLoc + 1];
      for (int i = 0; i < amountInLoc; i++) {
        r[i] = inLoc[i].r;
        g[i] = inLoc[i].g;
        b[i] = inLoc[i].b;
      }
      if (amountInLoc == 1) {
        R[pixel] = r[0];
        G[pixel] = g[0];
        B[pixel] = b[0];
      } else if (amountInLoc == 2) {
        R[pixel] = (r[0] + r[1]) / 2;
        G[pixel] = (g[0] + g[1]) / 2;
        B[pixel] = (b[0] + b[1]) / 2;
      } else {
        R[pixel] = (r[0] + r[1]);
        G[pixel] = (g[0] + g[1]);
        B[pixel] = (b[0] + b[1]);
        for (int i = 2; i < amountInLoc; i++) {
          R[pixel] += r[i];
          G[pixel] += g[i];
          B[pixel] += b[i];
        }
        R[pixel] /= amountInLoc;
        G[pixel] /= amountInLoc;
        B[pixel] /= amountInLoc;
      }


    } else {
      R[pixel] = colorBG.r;
      G[pixel] = colorBG.g;
      B[pixel] = colorBG.b;
    }
    strip.setPixelColor(pixel, R[pixel], G[pixel], B[pixel]);
  }
  strip.show();
}

void draw2() {
  for (int pixel = 0; pixel < numPixels; pixel++) {

    if (inLocationFade(pixel)) {
      int amountInLoc = 0;
      for (int i = 0; i < SPR_SIZE; i++) {
        if (inLoc[i].size == trash.size) {
          break;
        }
        amountInLoc++;
      }
      int r[amountInLoc + 1];
      int g[amountInLoc + 1];
      int b[amountInLoc + 1];
      for (int i = 0; i < amountInLoc; i++) {
        r[i] = inLoc[i].r;
        g[i] = inLoc[i].g;
        b[i] = inLoc[i].b;
      }
      if (amountInLoc == 1) {
        R[pixel] = r[0];
        G[pixel] = g[0];
        B[pixel] = b[0];
      } else if (amountInLoc == 2) {
        R[pixel] = (r[0] ^ r[1]);
        G[pixel] = (g[0] ^ g[1]);
        B[pixel] = (b[0] ^ b[1]);
      } else {
        R[pixel] = (r[0] ^ r[1]);
        G[pixel] = (g[0] ^ g[1]);
        B[pixel] = (b[0] ^ b[1]);
        for (int i = 2; i <= amountInLoc; i++) {
          R[pixel] ^= r[i];
          G[pixel] ^= g[i];
          B[pixel] ^= b[i];
        }
      }


    } else {
      R[pixel] = colorBG.r;
      G[pixel] = colorBG.g;
      B[pixel] = colorBG.b;
    }
    strip.setPixelColor(pixel, R[pixel], G[pixel], B[pixel]);

  }
  strip.show();
}

void rainbowThrough(int r, int g, int b, int pos, int offset) {
  strip.setPixelColor((pos + offset) % numPixels, r, g, b);
}
boolean shrink = false;

void loop() {
  if (loopCounter >= numPixels - 1) {
    loopCounter = 0;
    a++;
    strip.show();

    if (num == 2) {
      if (!shrink)
        sprsprspr.size++;
      else
        sprsprspr.size--;
      if (sprsprspr.size >= numPixels)
        shrink = true;
      else if (sprsprspr.size <= 2)
        shrink = false;
    } else
      delay(55);
  }
  else
    loopCounter++;
  switch (num) {
    case 0:
      fadeFromTo(0, 10, 0, 0, 200, 0);
      fadeFromTo(0, 200, 0, 0, 10, 0);
      break;
    case 1:
      rainbowThrough(rainbow[loopCounter], rainbow[loopCounter + numPixels], rainbow[loopCounter + numPixels * 2], loopCounter, a);
      break;
    case 2:
      colorBG.r = 0;
      colorBG.b = 0;
      colorBG.g = 0;
      strip.clear();
      allThrough();
      draw2();
      strip.show();
      delay(20);
      break;
    case 3:
      party(loopCounter, 0, 225);
      break;
    case 4:
      strip.clear();
      crawling(0, 0, 255, 255, 255, 0, false);
      for (int i = 0; i < numPixels; i++)
        if (!i <= numPixels / 20.0 * timer)
          strip.setPixelColor(i, 0, 0, 0);
      
      currentTime++;
      if (currentTime % 1 == 0)
        timer -= .25;
      break;
    case 5:
      colorBG.r = 0;
      colorBG.b = 0;
      colorBG.g = 255;
      strip.clear();
      allThrough();
      draw2();
      strip.show();
      delay(20);
      break;
  }
}


