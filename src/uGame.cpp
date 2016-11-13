#pragma hdrstop
#include "uGame.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
TGameObject::TGameObject(int id, String filename)
{
  this->id = id;
  picture = new TPicture();
  picture->Bitmap = Png2Bmp("images/" + filename + ".png");
}

TGameObject::TGameObject(const TGameObject &obj)
{
  id = obj.id;
  picture = new TPicture();
  picture->Bitmap = obj.picture->Bitmap;
}

TGameObject::TGameObject(int id, TPicture *picture)
{
  this->id = id;
  this->picture = picture;
}

TGameObject::~TGameObject()
{
  delete picture;
}
//---------------------------------------------------------------------------
TMap::TMap()
{
  for (int i = 0; i < GAME_WIDTH; i++) {
    for (int j = 0; j < GAME_HEIGHT; j++) {
      grid[i][j] = NULL;
    }
  }
}

TMap::~TMap()
{
  for (int i = 0; i < GAME_WIDTH; i++) {
    for (int j = 0; i < GAME_HEIGHT; i++) {
      if (grid[i][j]) {
        delete grid[i][j];
      }
    }
  }
}

TGameObject *TMap::getBlock(int x, int y)
{
  if ((x >= 0 && x <= GAME_WIDTH - 1 && y >= 0 && y <= GAME_HEIGHT - 1)) {
    return grid[x][y];
  }
  return Object[BLOCK];
}

void TMap::setBlock(int x, int y, TGameObject *b)
{
  if (!(x < 0 || x > GAME_WIDTH - 1 || y < 0 || y > GAME_HEIGHT - 1)) {
    if (grid[x][y]) {
      delete grid[x][y];
      grid[x][y] = NULL;
    }
    if (b) {
      grid[x][y] = new TGameObject(*b);
    }
  }
}
//---------------------------------------------------------------------------
TPerson::TPerson()
{
  x = GAME_WIDTH / 2;
  y = GAME_HEIGHT / 2;
  index = 11;
  name = "Luan Einhardt";
}
