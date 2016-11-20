Busca de caminhos em mapas com A*

O trabalho proposto foi desenvolvido em C++ para o sistema operacional Microsoft Windows utilizando a IDE Embarcadero C++ XE3.

A parte gráfica do jogo foi implementada utilizando a classe de desenho canvas contida em objetos gráficos da IDE.

O mapa do jogo como padrão tem as dimensões de 40 x 20 células, podendo ser customizado antes de ser compilado (uGame.h, GAME_WIDTH e GAME_HEIGHT).
Objetos podem ser adicionados ao mapa clicando com o botão direiro e no menu selecionando o objeto desejado, para remover um objeto o processo é o mesmo, contendo ainda os modos desenho e apagar, para agilizar a construção de mapas com blocos.

O personagem pode ser controlado utilizando as setas direcionais do teclado ou então com o mouse clincando onde se deseja ir (esse método) utiliza o algoritmo A* para calcular uma rota eficiente que desvie de todos objetos. Quando o A* é utilizado, na barra de título do programa é exibido o número de movimentos e a rota em forma de string, onde 0 = ir para direita, 1 = ir para baixo, 2 = ir para esquerda e 3 = ir para acima.

A*:
 - Utiliza a distância Manhattan para calcular a heurística
 - Utiliza uma fila de prioridades (Heap Mínimo) para avaliar cada “geração” de movimentos possíveis.

A interface gráfica foi inspirada em pokemon com gráficos encontrados na internet.

Para executar no Windows, basta dar um click duplo em Game.exe não necessitando da IDE instalada, e em ambiente linux utilizado wine.

Vídeo: https://www.youtube.com/watch?v=1ucxxXA6rXA

06/02/2014
