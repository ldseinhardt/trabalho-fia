#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "uFunction.h"
#include "uGame.h"
#include "uAStar.h"
//---------------------------------------------------------------------------
class ThGame : public TForm
{
__published:  // IDE-managed Components
  TTimer *GameLoop;
  TPopupMenu *PopupMenu;
  TMenuItem *AdicionarObjecto1;
  TMenuItem *RemoverObjeto1;
  TMenuItem *Pokemon1;
  TMenuItem *rvore1;
  TMenuItem *Rocha1;
  TMenuItem *Placa1;
  TMenuItem *Bloco1;
  TMenuItem *N11;
  TMenuItem *N21;
  TMenuItem *N31;
  TMenuItem *N41;
  TMenuItem *N51;
  TMenuItem *N61;
  TMenuItem *N71;
  TMenuItem *N81;
  TMenuItem *N91;
  TMenuItem *N101;
  TMenuItem *N12;
  TMenuItem *N22;
  TMenuItem *N32;
  TMenuItem *N42;
  TMenuItem *N13;
  TMenuItem *N23;
  TMenuItem *ModoDesenho1;
  TMenuItem *ModoApagar1;
  TTimer *GameWalk;
  TTimer *GamePad;
  TMenuItem *PararMusicadefundo1;
  TMenuItem *LimparMapa1;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall GameLoopTimer(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall RemoverObjeto1Click(TObject *Sender);
  void __fastcall Bloco1Click(TObject *Sender);
  void __fastcall Placa1Click(TObject *Sender);
  void __fastcall N11Click(TObject *Sender);
  void __fastcall N21Click(TObject *Sender);
  void __fastcall N31Click(TObject *Sender);
  void __fastcall N41Click(TObject *Sender);
  void __fastcall N51Click(TObject *Sender);
  void __fastcall N61Click(TObject *Sender);
  void __fastcall N71Click(TObject *Sender);
  void __fastcall N81Click(TObject *Sender);
  void __fastcall N91Click(TObject *Sender);
  void __fastcall N101Click(TObject *Sender);
  void __fastcall N12Click(TObject *Sender);
  void __fastcall N22Click(TObject *Sender);
  void __fastcall N32Click(TObject *Sender);
  void __fastcall N42Click(TObject *Sender);
  void __fastcall N13Click(TObject *Sender);
  void __fastcall N23Click(TObject *Sender);
  void __fastcall ModoDesenho1Click(TObject *Sender);
  void __fastcall ModoApagar1Click(TObject *Sender);
  void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
  void __fastcall GameWalkTimer(TObject *Sender);
  void __fastcall GamePadTimer(TObject *Sender);
  void __fastcall PararMusicadefundo1Click(TObject *Sender);
  void __fastcall LimparMapa1Click(TObject *Sender);

private:  // User declarations
public:   // User declarations
  TBitmap *offScreen;
  __fastcall ThGame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE ThGame *hGame;
//---------------------------------------------------------------------------
// Mensagem exibida na tela do jogo
String MsgText;
unsigned long int MsgDelay;

// Rota do A* a ser executada passo a passo
String walk_pos;
int walk_n;

// Posição (Bloco) do mouse sobre o mapa
TPoint MousePos;

// Posição (Bloco) do Joystick sobre o mapa
TPoint Pad;
// Indice do objeto a ser desenhado no mapa, com o joystick
int PadObject;
// Indica se um joystick foi encontrado
bool PadON;

// Modo de desenho e apagar para o mouse
bool DrawMode, EraseMode;

// Carrega os objetos do jogo
void LoadObjects();

// Envia uma mensagem para o jogo, com um determinado delay
void GameMsg(String Text, unsigned long Time);

// Adiciona um objeto pelo identificador ao mapa
void AddObject(int i);

// Faz o personagem caminhar dado uma direção
void walk(int Pos);

// Faz o personagem caminhar de um ponto a outro utilizando o A*
void walkPos(int x, int y);

// Carrega o mapa, ao inicializar o jogo
void MapLoad();

// Salva o mapa, ao finalizar o jogo
void MapSave();
//---------------------------------------------------------------------------
#endif
