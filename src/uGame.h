#ifndef uGameH
#define uGameH
//---------------------------------------------------------------------------
#include "uFunction.h"
//---------------------------------------------------------------------------
// Configurações
   const GAME_WIDTH      =  40;
   const GAME_HEIGHT     =  20;
   const GAME_SIZE       =  32;
   const GAME_WALK_DELAY = 200;

// Movimentos
   const int DIR_RIGHT   =   0;
   const int DIR_DOWN    =   1;
   const int DIR_LEFT    =   2;
   const int DIR_UP      =   3;

// Indice de Objetos
   const int BLOCK       =  29;
   const int PLAQUE      =  30;
   const int CURSOR      =  31;
   const int BACKGROUND  =  32;

// Número de Objetos
   const int N_OBJECT    =  33;
//---------------------------------------------------------------------------
// Representação de objetos
class TGameObject {
  public:
    // Identificão de objetos, útil para carregar e salvar o mapa
    int id;
    // Imagem do objeto
    TPicture *picture;
    TGameObject(int id, String filename);
    TGameObject(int id, TPicture *picture);
    TGameObject(const TGameObject &obj);
    ~TGameObject();
};
//---------------------------------------------------------------------------
// Representação do mapa
class TMap {
  public:
    // mapa: GAME_WIDTH x GAME_HEIGHT
    TGameObject *grid[GAME_WIDTH][GAME_HEIGHT];
    TMap();
    ~TMap();
    // Retorna o objeto contido em uma posição do mapa
    TGameObject *getBlock(int x, int y);
    // Coloca um objeto em uma posição do mapa
    void setBlock(int x, int y, TGameObject *b);
};
//---------------------------------------------------------------------------
class TPerson {
  public:
    // Posição Atual
    int x, y;
    /*
      Indice Gráfico:
      Indentificador que ira representar movimentos,
      Onde:
        01, 02, 03 -> Movimentos para esquerda;
        04, 05, 06 -> Movimentos para cima;
        07, 08, 09 -> Movimentos para direita;
        10, 11, 12 -> Movementos para baixo.

    */
    int index;
    // Nome do personagem
    String name;
    TPerson();
};
//---------------------------------------------------------------------------
// Lista de Objetos / Imagens
  TGameObject *Object[N_OBJECT];
// Mapa do jogo
  TMap *Map;
// Personagem do jogo
  TPerson *Person;
//---------------------------------------------------------------------------
#endif
