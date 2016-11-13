#include <vcl.h>
#pragma hdrstop
#include "uMain.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
ThGame *hGame;
//---------------------------------------------------------------------------
__fastcall ThGame::ThGame(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
// Inicialização do jogo
void __fastcall ThGame::FormCreate(TObject *Sender)
{
  String Music = "musics/music_back.wav";
  sndPlaySound(Music.c_str(), SND_ASYNC | SND_LOOP);

  Pad.X = GAME_WIDTH / 2;
  Pad.Y = GAME_HEIGHT / 2;
  PadON = false;
  PadObject = BLOCK;

  int w = GAME_WIDTH * GAME_SIZE;
  int h = GAME_HEIGHT * GAME_SIZE;
  int hs = 0, z0 = 0;

  Height = h + 29;
  if (Height >= Screen->Height) {
    VertScrollBar->Range = h;
    Height = Screen->Height - 50;
    VertScrollBar->Increment = Height / 2;
    hs = 28;
    z0++;
  }

  Width = w + 6 + hs;
  if (Width > Screen->Width) {
    HorzScrollBar->Range = w;
    Width = Screen->Width;
    HorzScrollBar->Increment = Width / 2;
    z0++;
  }

  if (z0 == 2) {
    WindowState = wsMaximized;
  }

  Caption = Application->Title;

  LoadObjects();
  Person = new TPerson();
  Map = new TMap();
  MapLoad();
  Map->setBlock(Person->x, Person->y, Object[Person->index]);
  MsgText = "";
  MsgDelay = 0;
  offScreen = new TBitmap();
  offScreen->PixelFormat = pf24bit;
  offScreen->Width = GAME_WIDTH * GAME_SIZE;
  offScreen->Height = GAME_HEIGHT * GAME_SIZE;

  // Desenha as bordas de blocos automaticamente no mapa
  for (int i = 0; i < GAME_WIDTH; i++) {
    Map->setBlock(i, 0, Object[BLOCK]);
    Map->setBlock(i, GAME_HEIGHT - 1, Object[BLOCK]);
  }

  for (int i = 0; i < GAME_HEIGHT; i++) {
    Map->setBlock(0, i, Object[BLOCK]);
    Map->setBlock(GAME_WIDTH - 1, i, Object[BLOCK]);
  }

  GameLoop->Enabled = true;
  DrawMode = EraseMode = false;
  ModoDesenho1->Checked = DrawMode;
  ModoApagar1->Checked = EraseMode;
}
//---------------------------------------------------------------------------
// Loop principal do jogo, que faz o desenho na tela
void __fastcall ThGame::GameLoopTimer(TObject *Sender)
{
  int x = 0, y = 0, cx = 0, cy = 0;

  offScreen->Canvas->FillRect(offScreen->Canvas->ClipRect);

  for (int i = 0; i < GAME_WIDTH; i++) {
    for (int j = 0; j < GAME_HEIGHT; j++) {
      offScreen->Canvas->Draw(cx, cy, Object[BACKGROUND]->picture->Graphic);
      if (Map->getBlock(i, j)) {
        offScreen->Canvas->Draw(cx, cy, Map->getBlock(i, j)->picture->Graphic);
        if (Map->getBlock(i, j)->id >= 1 && Map->getBlock(i, j)->id <= 12) {
          x = cx;
          y = cy;
        }
      }
      cy += GAME_SIZE;
    }
    cy = 0;
    cx += GAME_SIZE;
  }

  offScreen->Canvas->Brush->Color = clBlack;
  offScreen->Canvas->Font->Color = clWhite;
  offScreen->Canvas->TextOutW(
    x + GAME_SIZE / 2 - Person->name.Length() / 2 * 5.5,
    y - GAME_SIZE / 2,
    Person->name
  );

  if (MsgDelay > 0) {
    offScreen->Canvas->TextOutW(
      x + GAME_SIZE / 2 - MsgText.Length() / 2 * 5.5,
      y - GAME_SIZE,
      MsgText
    );
    MsgDelay--;
  }

  if (PadON) {
    offScreen->Canvas->Draw(
      Pad.X * GAME_SIZE,
      Pad.Y * GAME_SIZE,
      Object[CURSOR]->picture->Graphic
    );
  }

  offScreen->Canvas->Brush->Color = clWhite;
  offScreen->Canvas->Font->Color = clBlack;
  offScreen->Canvas->TextOutW(
    HorzScrollBar->Position + 10,
    VertScrollBar->Position + 10,
    Person->name + ": X=" + IntToStr(Person->x) + " Y=" + IntToStr(Person->y)
  );

  BitBlt(
    Canvas->Handle,
    0,
    0,
    offScreen->Width,
    offScreen->Height,
    offScreen->Canvas->Handle,
    HorzScrollBar->Position,
    VertScrollBar->Position,
    SRCCOPY
  );
}
//---------------------------------------------------------------------------
// Finalização do jogo
void __fastcall ThGame::FormClose(TObject *Sender, TCloseAction &Action)
{
  GameLoop->Enabled = false;
  GameWalk->Enabled = false;
  GamePad->Enabled  = false;
  MapSave();
  for (int i = 0; i < N_OBJECT; i++) {
    delete Object[i];
  }
  delete Person;
  delete Map;
  delete offScreen;
  Application->Terminate();
}
//---------------------------------------------------------------------------
// Verifica se os direcionais do teclado foram precionados e faz o personagem caminhar
void __fastcall ThGame::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
  switch (Key) {
    case VK_RIGHT:
      walk(DIR_RIGHT);
      break;
    case VK_DOWN:
      walk(DIR_DOWN);
      break;
    case VK_LEFT:
      walk(DIR_LEFT);
      break;
    case VK_UP:
      walk(DIR_UP);
  }
}
//---------------------------------------------------------------------------
// Verifica se houve um click com o mouse
void __fastcall ThGame::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  MousePos.X = (HorzScrollBar->Position + X) / GAME_SIZE;
  MousePos.Y = (VertScrollBar->Position + Y) / GAME_SIZE;

  if (int(Button) == 0) {
    if (DrawMode) {
      if (!Map->getBlock(MousePos.X, MousePos.Y)) {
        Map->setBlock(MousePos.X, MousePos.Y, Object[BLOCK]);
      }
    } else if (EraseMode) {
      if (!(MousePos.X == Person->x && MousePos.Y == Person->y)) {
        Map->setBlock(MousePos.X, MousePos.Y, NULL);
      }
    } else {
      walkPos(MousePos.X, MousePos.Y);
    }
  }
}
//---------------------------------------------------------------------------
// Remove um objeto do mapa, cuidando para o personagem n ser apagado
void __fastcall ThGame::RemoverObjeto1Click(TObject *Sender)
{
  if (MousePos.X == Person->x && MousePos.Y == Person->y) {
    GameMsg("Você não pode apagar seu personagem.", 3000);
  } else {
    Map->setBlock(MousePos.X, MousePos.Y, NULL);
  }
}
//---------------------------------------------------------------------------
void __fastcall ThGame::Bloco1Click(TObject *Sender)
{
  AddObject(BLOCK);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::Placa1Click(TObject *Sender)
{
  AddObject(PLAQUE);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N11Click(TObject *Sender)
{
  AddObject(13);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N21Click(TObject *Sender)
{
  AddObject(14);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N31Click(TObject *Sender)
{
  AddObject(15);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N41Click(TObject *Sender)
{
  AddObject(16);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N51Click(TObject *Sender)
{
  AddObject(17);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N61Click(TObject *Sender)
{
  AddObject(18);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N71Click(TObject *Sender)
{
  AddObject(19);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N81Click(TObject *Sender)
{
  AddObject(20);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N91Click(TObject *Sender)
{
  AddObject(21);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N101Click(TObject *Sender)
{
  AddObject(22);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N12Click(TObject *Sender)
{
  AddObject(23);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N22Click(TObject *Sender)
{
  AddObject(24);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N32Click(TObject *Sender)
{
  AddObject(25);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N42Click(TObject *Sender)
{
  AddObject(26);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N13Click(TObject *Sender)
{
  AddObject(27);
}
//---------------------------------------------------------------------------
void __fastcall ThGame::N23Click(TObject *Sender)
{
  AddObject(28);
}
//---------------------------------------------------------------------------
// Ativa o modo desenho
void __fastcall ThGame::ModoDesenho1Click(TObject *Sender)
{
  EraseMode = false;
  DrawMode = !DrawMode;
  ModoDesenho1->Checked = DrawMode;
  ModoApagar1->Checked = EraseMode;
}
//---------------------------------------------------------------------------
// Ativa o modo apagar
void __fastcall ThGame::ModoApagar1Click(TObject *Sender)
{
  DrawMode = false;
  EraseMode = !EraseMode;
  ModoDesenho1->Checked = DrawMode;
  ModoApagar1->Checked = EraseMode;
}
//---------------------------------------------------------------------------
// Desliza o mapa com scroll do mouse, em caso de mapas grandes
void __fastcall ThGame::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
  int cod, msg, x;
  if (WindowFromPoint(Mouse->CursorPos) == this->Handle) {
    Handled = true;
    msg = Shift.Contains(ssShift)
      ? WM_HSCROLL
      : WM_VSCROLL;
    cod = WheelDelta < 0
      ? SB_LINEDOWN
      : SB_LINEUP;
    for (int i = 1; i < Mouse->WheelScrollLines; i++) {
      Perform(msg, cod, 0);
    }
    Perform(msg, SB_ENDSCROLL, 0);
  }
}
//---------------------------------------------------------------------------
// Timer (Thread) que verifica se há uma rota do A* a ser caminhada
void __fastcall ThGame::GameWalkTimer(TObject *Sender)
{
  walk(StrToInt(walk_pos[walk_n]));
  walk_n++;
  if (walk_n > walk_pos.Length()) {
    GameWalk->Enabled = false;
  }
}
//---------------------------------------------------------------------------
// Encerra a música de fundo
void __fastcall ThGame::PararMusicadefundo1Click(TObject *Sender)
{
  sndPlaySound(NULL, 0);
}
//---------------------------------------------------------------------------
/*
  Timer (Thread) que verifica se há um joystick de XBOX 360 conectado e
  o estado de cada botão realizando a função desejada
*/
void __fastcall ThGame::GamePadTimer(TObject *Sender)
{
  TJoy Joy;
  if (JoyStick(&Joy)) {
    PadON = true;
    if (Joy.A) {
      walkPos(Pad.X, Pad.Y);
    }

    if (Joy.B) {
      GameWalk->Enabled = false;
    }

    if (Joy.X) {
      if (!Map->getBlock(Pad.X, Pad.Y)) {
        Map->setBlock(Pad.X, Pad.Y, Object[PadObject]);
      }
    }

    if (Joy.Y) {
      if (!(Pad.X == Person->x && Pad.Y == Person->y)) {
        Map->setBlock(Pad.X, Pad.Y, NULL);
      }
    }

    if (Joy.Back) {

    }

    if (Joy.Start) {

    }

    if (Joy.LB) {
      PadObject--;
      if (PadObject < 13) {
        PadObject = 13;
      }
    }

    if (Joy.LT) {

    }

    if (Joy.RB) {
      PadObject++;
      if (PadObject > 30) {
        PadObject = 30;
      }
    }

    if (Joy.RT) {

    }

    if (Joy.Pad.Right) {
      walk(DIR_RIGHT);
    }

    if (Joy.Pad.Down) {
      walk(DIR_DOWN);
    }

    if (Joy.Pad.Left) {
      walk(DIR_LEFT);
    }

    if (Joy.Pad.Up) {
      walk(DIR_UP);
    }

    if (Joy.Analogic[0].Right) {
      Pad.x++;
      if (Pad.x >= GAME_WIDTH) {
        Pad.x = GAME_WIDTH - 1;
      }
    }

    if (Joy.Analogic[0].Down) {
      Pad.y++;
      if (Pad.y >= GAME_HEIGHT) {
        Pad.y = GAME_HEIGHT - 1;
      }
    }

    if (Joy.Analogic[0].Left) {
      Pad.x--;
      if (Pad.x < 0) {
        Pad.x = 0;
      }
    }

    if (Joy.Analogic[0].Up) {
      Pad.y--;
      if (Pad.y < 0) {
        Pad.y = 0;
      }
    }

    if (Joy.Analogic[1].Right) {

    }

    if (Joy.Analogic[1].Down) {

    }

    if (Joy.Analogic[1].Left) {

    }

    if (Joy.Analogic[1].Up) {

    }
  } else {
    PadON = false;
  }
}
//---------------------------------------------------------------------------
// Carrega os objetos do jogo
void LoadObjects()
{
  // Carrega os objetos;
  Object[0] = new TGameObject(0, NULL);

  for (int i = 1; i < 4; i++) {
    Object[i] = new TGameObject(i, "character/left/" + IntToStr(i));
    Object[i + 3] = new TGameObject(i + 3, "character/up/" + IntToStr(i));
    Object[i + 6] = new TGameObject(i + 6, "character/right/" + IntToStr(i));
    Object[i + 9] = new TGameObject(i + 9, "character/down/" + IntToStr(i));
  }

  for (int i = 13; i < 23; i++) {
    Object[i] = new TGameObject(i, "pokemon/" + IntToStr(i - 12));
  }

  for (int i = 23; i < 27; i++) {
    Object[i] = new TGameObject(i, "tree/" + IntToStr(i - 22));
  }

  for (int i = 27; i < 29; i++) {
    Object[i] = new TGameObject(i, "rock/" + IntToStr(i - 26));
  }

  Object[BLOCK] = new TGameObject(BLOCK, "block");
  Object[PLAQUE] = new TGameObject(PLAQUE, "plaque");
  Object[BACKGROUND] = new TGameObject(BACKGROUND, "background");
  Object[CURSOR] = new TGameObject(CURSOR, "cursor");
}
//---------------------------------------------------------------------------
// Envia uma mensagem para a tela do jogo
void GameMsg(String Text, unsigned long Time)
{
  MsgText = Text;
  MsgDelay = Time / hGame->GameLoop->Interval;
}
//---------------------------------------------------------------------------
// Adiciona um objeto ao mapa verificando se a posição não foi ocupada
void AddObject(int i)
{
  if (Map->getBlock(MousePos.X, MousePos.Y)) {
    GameMsg("Espaço no mapa ocupado.", 3000);
  } else {
    Map->setBlock(MousePos.X, MousePos.Y, Object[i]);
  }
}
//---------------------------------------------------------------------------
// Faz o personagem caminhar dado uma direção
void walk(int Pos)
{
  switch (Pos) {
    case DIR_RIGHT:
      if (!Map->getBlock(Person->x + 1, Person->y)) {
        Map->setBlock(Person->x, Person->y, NULL);
        Person->x++;
        if (Person->index < 7 || Person->index >= 9) {
          Person->index = 6;
        }
        Person->index++;
      }
      break;
    case DIR_DOWN:
      if (!Map->getBlock(Person->x, Person->y + 1)) {
        Map->setBlock(Person->x, Person->y, NULL);
        Person->y++;
        if (Person->index < 10 || Person->index >= 12) {
          Person->index = 9;
        }
        Person->index++;
      }
      break;
    case DIR_LEFT:
      if (!Map->getBlock(Person->x - 1, Person->y)) {
        Map->setBlock(Person->x, Person->y, NULL);
        Person->x--;
        if (Person->index < 1 || Person->index >= 3) {
          Person->index = 0;
        }
        Person->index++;
      }
      break;
    case DIR_UP:
      if (!Map->getBlock(Person->x, Person->y - 1)) {
        Map->setBlock(Person->x, Person->y, NULL);
        Person->y--;
        if (Person->index < 4 || Person->index >= 6) {
          Person->index = 3;
        }
        Person->index++;
      }
  }

  if (Person->x < 0) {
    Person->x = 0;
  }

  if (Person->x >= GAME_WIDTH) {
    Person->x = GAME_WIDTH - 1;
  }

  if (Person->y < 0) {
    Person->y = 0;
  }

  if (Person->y >= GAME_HEIGHT) {
    Person->y = GAME_HEIGHT - 1;
  }

  Map->setBlock(Person->x, Person->y, Object[Person->index]);
}
//---------------------------------------------------------------------------
// Faz o personagem caminhar de um ponto a outro utilizando o A*
void walkPos(int x, int y)
{
  hGame->GameWalk->Enabled = false;

  if (Person->x != x || Person->y != y) {
    AStar *S = new AStar();

    for (int i = 0; i < GAME_WIDTH; i++) {
      for (int j = 0; j < GAME_HEIGHT; j++) {
        S->setMap(i, j, 0);
        if (Map->getBlock(i, j) && Map->getBlock(i, j)->id > 12) {
          S->setMap(i, j, 1);
        }
      }
    }
    if (S->search(Person->x, Person->y, x, y)) {
      hGame->Caption = Application->Title + " -  " + "Movimentos: " + IntToStr(S->getRoute().Length()) + " | Rota: " + S->getRoute();
      walk_pos = S->getRoute();
      walk_n = 1;
      hGame->GameWalk->Interval = GAME_WALK_DELAY;
      hGame->GameWalk->Enabled = true;
    } else {
      GameMsg("Esse ponto não é acessível", 3000);
      hGame->Caption = Application->Title;
    }
    delete S;
  }
}
//---------------------------------------------------------------------------
// Carrega o mapa, utilizado ao inicializar o jogo
void MapLoad()
{
  if (FileExists("map.txt")) {
    TStringList *s = new TStringList();
    s->LoadFromFile("map.txt");
    if (s->Count > 1) {
      TStringList *temp = explode(s->Strings[0], " ");
      try {
        for (int i = 0; i < s->Count; i++) {
          temp = explode(s->Strings[i], " ");
          Map->setBlock(
            StrToInt(temp->Strings[0]),
            StrToInt(temp->Strings[1]),
            Object[StrToInt(temp->Strings[2])]
          );
        }
      } catch (...) {
        ShowMessage("\"map.txt\" inválido.");
      }
    }
  }
}
//---------------------------------------------------------------------------
// Salva o mapa, utilizado ao finalizar o jogo
void MapSave()
{
  TStringList *s = new TStringList();
  for (int i = 1; i < GAME_WIDTH - 1; i++) {
    for (int j = 1; j < GAME_HEIGHT - 1; j++) {
      if (Map->getBlock(i, j) && Map->getBlock(i, j)->id > 12) {
        s->Add(IntToStr(i) + " " + IntToStr(j) + " " + IntToStr(Map->getBlock(i, j)->id));
      }
    }
  }
  s->SaveToFile("map.txt");
}
void __fastcall ThGame::LimparMapa1Click(TObject *Sender)
{
  for (int i = 1; i < GAME_WIDTH - 1; i++) {
    for (int j = 1; j < GAME_HEIGHT - 1; j++) {
      if (Map->getBlock(i, j) && Map->getBlock(i, j)->id > 12) {
        Map->setBlock(i, j, NULL)
      }
    };
  }
}
//---------------------------------------------------------------------------
