#ifndef uFunctionH
#define uFunctionH
//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>
#include <PNGImage.hpp>
#include <MMSystem.hpp>
//---------------------------------------------------------------------------
// Struct para representar movimentos
typedef struct {
  bool Right;
  bool Down;
  bool Left;
  bool Up;
} TMov;

// Struct para representar estados de um joyStick de XBOX 360
typedef struct {
  bool A;
  bool B;
  bool X;
  bool Y;

  bool Back;
  bool Start;

  bool LB;
  bool RB;

  TMov Pad;

  bool LT;
  bool RT;

  TMov Analogic[2];
} TJoy;

// Faz a leitura dos estados do joyStick de XBOX 360
bool JoyStick(TJoy *Joy);

// Carrega uma imagem PNG e converte para um Bitmap
TBitmap *Png2Bmp(String filename);

// Quebra Strings por delimitadores
TStringList *explode(String Text, String Separator);
//---------------------------------------------------------------------------
#endif
