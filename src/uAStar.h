#ifndef uAStarH
#define uAStarH
//---------------------------------------------------------------------------
#include <queue>
#include "uGame.h"
//---------------------------------------------------------------------------
// Representação de cada estado possível dentro do mapa
class Nodo {
  private:
    // Posições
    int x, y;
    // Distância total já viajada para alcançar o nodo
    int level;
    /*
      priority = level + estimativa da distância restante
      Menor = Alta prioridade
    */
    int priority;
    // Heurística: Distância Manhattan
    inline const int heuristic(const int &x, const int &y) const {
      return abs(x - this->x) + abs(y - this->y);
    }

  public:
    Nodo(int x, int y, int level, int priority);
    inline void setPriority(const int &x, const int &y) { priority = level + heuristic(x, y); }
    inline void setLevel() { level++; };
    inline int getX() const { return x; }
    inline int getY() const { return y; }
    inline int getLevel() const { return level; }
    inline int getPriority() const { return priority; }
};
//---------------------------------------------------------------------------
// Determina a prioridade para a fila de prioridades (Heap mínimo)
bool operator<(const Nodo &a, const Nodo &b) {
  return a.getPriority() > b.getPriority();
}
//---------------------------------------------------------------------------
class AStar {
  private:
    /*
      Mapa que endica onde há objetos:
      0 = Posição Livre
      1 = Posição ocupada
    */
    int map_objects[GAME_WIDTH][GAME_HEIGHT];
    String route;
  public:
    bool search(const int startX, const int startY, const int finishX, const int finishY);
    inline void setMap(int i, int j, int v) { map_objects[i][j] = v; }
    inline String &getRoute() { return route; }
};
//---------------------------------------------------------------------------
#endif
