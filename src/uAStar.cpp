#pragma hdrstop
#include "uAStar.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
Nodo::Nodo(int x, int y, int level, int priority)
{
  this->x = x;
  this->y = y;
  this->level = level;
  this->priority = priority;
}
//---------------------------------------------------------------------------
bool AStar::search(const int startX, const int startY, const int finishX, const int finishY)
{
  // Rota
  route = "";
  /*
    Direções de movimento:
    Right -> +1
    Left  -> -1
    Up    -> +1
    Down  -> -1
  */
  int dx[4] = {+1, +0, -1, +0};
  int dy[4] = {+0, +1, +0, -1};
  // Mapa de nodos abertos
  int map_open[GAME_WIDTH][GAME_HEIGHT];
  // Mapa de nodos fechados
  int map_closed[GAME_WIDTH][GAME_HEIGHT];
  // Mapa de direções
  int map_dir[GAME_WIDTH][GAME_HEIGHT];
  // Nodos
  Nodo *father, *child;
  // Variáveis temporarias para posições e lados
  int i, j, x, y, cx, cy;
  // Heap com nodos abertos, que ainda não foram avaliados
  std::priority_queue<Nodo> heap[2];
  // Heap index
  int index = 0;

  // Zera os mapas
  for (y = 0; y < GAME_HEIGHT; y++) {
    for (x = 0; x < GAME_WIDTH; x++) {
      map_open[x][y] = map_closed[x][y] = map_dir[x][y] = 0;
    }
  }

  // Cria o nodo inicial e pôe na fila e lista de nodos abertos
  father = new Nodo(startX, startY, 0, 0);
  father->setPriority(finishX, finishY);
  heap[index].push(*father);
  // Marca o nodo aberto
  map_open[x][y] = father->getPriority();
  delete father;

  // Busca do A*
  while (!heap[index].empty()) {
    // Pega o nodo corrente (menor prioridade) da fila de nodos abertos
    father = new Nodo(
      heap[index].top().getX(),
      heap[index].top().getY(),
      heap[index].top().getLevel(),
      heap[index].top().getPriority()
    );
    x = father->getX();
    y = father->getY();
    // Remove o nodo da fila
    heap[index].pop();
    map_open[x][y] = 0;
    // Marca o nodo fechado
    map_closed[x][y] = 1;
    // Encerra a busca se encontrou o estado final
    if (x == finishX && y == finishY) {
      // Gera a lista de direções do fim para o inicio
      while (!(x == startX && y == startY)) {
        j = map_dir[x][y];
        route = AnsiString((j + 2) % 4) + route;
        x += dx[j];
        y += dy[j];
      }
      delete father;
      // Esvazia a heap
      while (!heap[index].empty()) {
        heap[index].pop();
      }
      return true;
    }

    // Gera os movimentos (nodos filhos), com todas possíveis direções
    for (i = 0; i < 4; i++) {
      cx = x + dx[i];
      cy = y + dy[i];
      if (!(cx < 0 || cx > GAME_WIDTH - 1 || cy < 0 || cy > GAME_HEIGHT - 1 || map_objects[cx][cy] == 1 || map_closed[cx][cy] == 1)) {
        // Gera o nodo filho
        child = new Nodo(cx, cy, father->getLevel(), father->getPriority());
        child->setLevel();
        child->setPriority(finishX, finishY);

        // Pôe na fila e lista de nodos abertos se não estiver
        if (map_open[cx][cy] == 0) {
          map_open[cx][cy] = child->getPriority();
          heap[index].push(*child);

          // Marca a direção no nodo pai
          map_dir[cx][cy] = (i + 2) % 4;
        } else if (map_open[cx][cy]>child->getPriority()) {
          // Atualiza a prioridade
          map_open[cx][cy] = child->getPriority();
          // Atualiza a direção no nodo pai
          map_dir[cx][cy] = (i + 2) % 4;

          /*
            Substitui o nodo:
            fazendo o esvaziamento de uma heap para a outra.
            Exceto o nodo a ser substituido, que será ignorado.
            E adiciona o novo nodo;
          */
          while (!(heap[index].top().getX() == cx && heap[index].top().getY() == cy)) {
            heap[1 - index].push(heap[index].top());
            heap[index].pop();
          }
          // Remove o nodo procurado (que será substituido)
          heap[index].pop();

          // Esvazia a heap de maior tamanho para a de menor
          if (heap[index].size() > heap[1 - index].size()) {
            index = 1 - index;
          }
          while (!heap[index].empty()) {
            heap[1 - index].push(heap[index].top());
            heap[index].pop();
          }
          index = 1 - index;
          // Adiciona o melhor nodo (nodo que substitui)
          heap[index].push(*child);
        }
        delete child;
      }
    }
    delete father;
  }
  return false;
}
