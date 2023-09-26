#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale.h>
#include <queue>
#include <stdio.h>
#include <vector>
#include <algorithm> // Para a função transform
#include <cctype>    // Para a função tolower
#include <string>    // Para manipulação de strings
using namespace std;

#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___


struct Vertice {
  int numero;
  std::string nome;
};

class TGrafo {
private:
  int n;     // quantidade de vértices
  int m;
  int **adj; // matriz de adjacência
  int peso;
  int *visitado;


public:
  TGrafo(int n);
  void adicionaVertice();
  int addcidade(const std::string &nome);
  void removeVertice(const std::string &nome);
  void insereA(int v, int w, int peso);
  void removeA(int v, int w);
  void show(const std::vector<Vertice> &vertices);
  void showMatriz(const std::vector<Vertice> &vertices);
  ~TGrafo();
  void lerArquivo(const std::string &nomeArquivo);
  void executarMenu();
  void imprimirGrafoParaArquivo(const std::string &nomeArquivo, int tipoGrafo) const;
  int Conectividade();
  int buscaemLargura();
  void limparGrafo();
  bool desconexo();
  bool C1();
  bool C2();
  bool C3();
  void conectividade();

  void mostrarArquivo(const std::string &nomeArquivo);
  int getNumVertices() const { return n; }
  int getNumArestas() const { return m; }

  int getPesoAresta(int v, int w) const {
    if (v >= 0 && v < n && w >= 0 && w < n) {
      return adj[v][w];
    }
    return std::numeric_limits<int>::infinity(); // Retorna infinito se a aresta
                                                 // não existir
  }

};

std::vector<Vertice>vertices; // Vetor de estruturas para armazenar números e nomes
void TGrafo::limparGrafo() {
    // Limpe os vetores de vértices e arestas, ou faça qualquer outra operação de limpeza necessária.
    vertices.clear();
    // Limpe a matriz de adjacência (ou qualquer outra estrutura que você esteja usando para representar o grafo).
    // Lembre-se de atualizar n para 0 ou o valor inicial apropriado.
    n = 0;
    // Outras operações de limpeza, se necessário.
}
void TGrafo::imprimirGrafoParaArquivo(const std::string &nomeArquivo, int tipoGrafo) const {
    // Abre o arquivo para escrita
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    // Imprime o tipo de grafo
    arquivo << tipoGrafo << std::endl;

    // Imprime o número de vértices
    arquivo << n << std::endl;

    // Imprime os vértices no formato "NUMERO NOME"
    for (int i = 0; i < n; i++) {
        arquivo << vertices[i].numero << " " << vertices[i].nome << std::endl;
    }

    // Imprime o número de arestas
    arquivo << m << std::endl;

    // Imprime as arestas no formato "INICIO FIM PESO"
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int peso = getPesoAresta(i, j);
            if (peso != std::numeric_limits<int>::infinity()) {
                arquivo << i << " " << j << " " << peso << std::endl;
            }
        }
    }

    // Fecha o arquivo
    arquivo.close();
}
// Construtor do TGrafo, responsável por
// Criar a matriz de adjacência v x v do Grafo
TGrafo::TGrafo(int n) {
  visitado = new int[n];
  this->n = n;
  // No início dos tempos não há arestas
  this->m = 0;
  // aloca da matriz do TGrafo
  int **adjac = new int *[n];
  for (int i = 0; i < n; i++)
    adjac[i] = new int[n];
  adj = adjac;
  // Inicia a matriz com zeros
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adj[i][j] = 0;
}

// Destructor, responsável por
// liberar a memória alocada para a matriz
TGrafo::~TGrafo() {
  n = 0;
  m = 0;
  delete[] * adj;
  #include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale.h>
#include <queue>
#include <stdio.h>
#include <vector>
#include <algorithm> // Para a função transform
#include <cctype>    // Para a função tolower
#include <string>    // Para manipulação de strings
using namespace std;

#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___


struct Vertice {
  int numero;
  std::string nome;
};

class TGrafo {
private:
  int n;     // quantidade de vértices
  int m;
  int **adj; // matriz de adjacência
  int peso;
  int *visitado;


public:
  TGrafo(int n);
  void adicionaVertice();
  int addcidade(const std::string &nome);
  void removeVertice(const std::string &nome);
  void insereA(int v, int w, int peso);
  void removeA(int v, int w);
  void show(const std::vector<Vertice> &vertices);
  ~TGrafo();
  void lerArquivo(const std::string &nomeArquivo);
  void executarMenu();
  void imprimirGrafoParaArquivo(const std::string &nomeArquivo, int tipoGrafo) const;
  int Conectividade();
  int buscaemLargura();
  void limparGrafo();
  bool desconexo();
  bool C1();
  bool C2();
  bool C3();
  void conectividade();

  void mostrarArquivo(const std::string &nomeArquivo);
  int getNumVertices() const { return n; }
  int getNumArestas() const { return m; }

  int getPesoAresta(int v, int w) const {
    if (v >= 0 && v < n && w >= 0 && w < n) {
      return adj[v][w];
    }
    return std::numeric_limits<int>::infinity(); // Retorna infinito se a aresta
                                                 // não existir
  }

};

std::vector<Vertice>vertices; // Vetor de estruturas para armazenar números e nomes
void TGrafo::limparGrafo() {
    // Limpe os vetores de vértices e arestas, ou faça qualquer outra operação de limpeza necessária.
    vertices.clear();
    // Limpe a matriz de adjacência (ou qualquer outra estrutura que você esteja usando para representar o grafo).
    // Lembre-se de atualizar n para 0 ou o valor inicial apropriado.
    n = 0;
    // Outras operações de limpeza, se necessário.
}
void TGrafo::imprimirGrafoParaArquivo(const std::string &nomeArquivo, int tipoGrafo) const {
    // Abre o arquivo para escrita
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    // Imprime o tipo de grafo
    arquivo << tipoGrafo << std::endl;

    // Imprime o número de vértices
    arquivo << n << std::endl;

    // Imprime os vértices no formato "NUMERO NOME"
    for (int i = 0; i < n; i++) {
        arquivo << vertices[i].numero << " " << vertices[i].nome << std::endl;
    }

    // Imprime o número de arestas
    arquivo << m << std::endl;

    // Imprime as arestas no formato "INICIO FIM PESO"
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int peso = getPesoAresta(i, j);
            if (peso != std::numeric_limits<int>::infinity()) {
                arquivo << i << " " << j << " " << peso << std::endl;
            }
        }
    }

    // Fecha o arquivo
    arquivo.close();
}
// Construtor do TGrafo, responsável por
// Criar a matriz de adjacência v x v do Grafo
TGrafo::TGrafo(int n) {
  visitado = new int[n];
  this->n = n;
  // No início dos tempos não há arestas
  this->m = 0;
  // aloca da matriz do TGrafo
  int **adjac = new int *[n];
  for (int i = 0; i < n; i++)
    adjac[i] = new int[n];
  adj = adjac;
  // Inicia a matriz com zeros
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adj[i][j] = 0;
}

// Destructor, responsável por
// liberar a memória alocada para a matriz
TGrafo::~TGrafo() {
  n = 0;
  m = 0;
  delete[] * adj;
  delete[] visitado;
  std::cout << "espaço liberado";
}

// Insere uma aresta no Grafo tal que
// v é adjacente a w
void TGrafo::insereA(int v, int w, int peso) {
  //verifica se existe 2 vertices para criar uma aresta
  if (n < 1) {
    cout << "Você precisa de pelo menos 3 vértices para adicionar uma aresta." << endl;
    exit(1);
  }
  // testa se nao temos a aresta
  if (adj[v][w] == std::numeric_limits<int>::infinity()) {
    adj[v][w] = peso;
    m++; // atualiza qtd arestas
  }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w) {
  // Testa se temos a aresta
  if (adj[v][w] != std::numeric_limits<float>::infinity()) {
    adj[v][w] = 0;
    m--; // Atualiza a quantidade de arestas
  //for q percorre
    cout << "Aresta entre " << vertices[v].nome << " e " << vertices[w].nome << " removida com sucesso!"
         << endl;
  } else {
    cout << "Aresta entre " << vertices[v].nome << " e " << vertices[w].nome << " não existe." << endl;
  }
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida
void TGrafo::show(const std::vector<Vertice> &vertices) {
  std::cout << "n: " << n << std::endl;
  std::cout << "m: " << m << std::endl;
  for (int i = 0; i < n; i++) {
    for (int w = 0; w < n; w++) {
      int peso = getPesoAresta(i, w);
      if (peso > 0) {
        std::cout << "\nDistancia de " << vertices[i].nome << " para "<< vertices[w].nome << " é de " << peso << " km\n";
      }
    }
  }
}
int TGrafo::addcidade(const std::string &nome) {
    // Cria uma nova matriz com tamanho aumentado (n + 1)
    int **newAdj = new int *[n + 1];
    for (int i = 0; i < n + 1; i++)
        newAdj[i] = new int[n + 1];

    // Copia os elementos da matriz original para a nova matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            newAdj[i][j] = adj[i][j];
        }
    }

    // Inicializa a nova linha e coluna para 0 (sem conexões)
    for (int i = 0; i < n + 1; i++) {
        newAdj[n][i] = 0; // Nova linha
        newAdj[i][n] = 0; // Nova coluna
    }

    // Copia as arestas da matriz original para a nova matriz
    for (int i = 0; i < n; i++) {
        newAdj[i][n] = 0; // Nova coluna (saída do novo vértice)
        newAdj[n][i] = 0; // Nova linha (entrada para o novo vértice)
    }

    // Liberar a matriz original
    for (int i = 0; i < n; i++)
        delete[] adj[i];
    delete[] adj;

    // Atualiza a matriz para a nova matriz
    adj = newAdj;
    n++;

    // Atualiza o nome do vértice recém-adicionado e insere no final do vetor
    vertices.push_back({n - 1, nome});

    // Retorna a posição onde o vértice foi inserido (índice baseado em zero)
    return n - 1;
}
void mostrarArquivo(const std::string &nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);

  if (!arquivo.is_open()) {
    std::cerr << "Erro ao abrir o arquivo." << std::endl;
    return;
  }

  // Lê e mostra o conteúdo do arquivo linha por linha
  std::string linha;
  while (std::getline(arquivo, linha)) {
    std::cout << linha << std::endl;
  }

  arquivo.close();
}

void TGrafo::removeVertice(const std::string &nome) {
    // Converter o nome inserido pelo usuário para letras minúsculas
    std::string nomeMinusc = nome;
    std::transform(nomeMinusc.begin(), nomeMinusc.end(), nomeMinusc.begin(), ::tolower);

    int verticeIndex = -1; // Inicialize como -1 para indicar que o vértice não foi encontrado

    // Encontre o índice do vértice com o nome correspondente (em minúsculas)
    for (int i = 0; i < n; i++) {
        std::string nomeVertice = vertices[i].nome;
        std::transform(nomeVertice.begin(), nomeVertice.end(), nomeVertice.begin(), ::tolower);
        if (nomeMinusc == nomeVertice) {
            verticeIndex = i;
            break;
        }
    }

    if (verticeIndex == -1) {
        cout << "Vértice com o nome '" << nome << "' não encontrado." << endl;
        return;
    }

    // Remova o vértice do vetor de vértices
    vertices.erase(vertices.begin() + verticeIndex);
    n--;

    // Redimensione a matriz de adjacência para refletir a remoção do vértice
    for (int i = verticeIndex; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = adj[i + 1][j];
        }
    }
    for (int j = verticeIndex; j < n; j++) {
        for (int i = 0; i < n; i++) {
            adj[i][j] = adj[i][j + 1];
        }
    }

    // Atualize a contagem de arestas (m) adequadamente
    m = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != std::numeric_limits<int>::infinity()) {
                m++;
            }
        }
    }

    cout << nome << " removido com sucesso!" << endl;
}
void TGrafo::adicionaVertice() {
  // Cria uma nova matriz com tamanho aumentado (n + 1)
  int **newAdj = new int *[n + 1];
  for (int i = 0; i < n + 1; i++)
    newAdj[i] = new int[n + 1];

  // Copia os elementos da matriz original para a nova matriz
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      newAdj[i][j] = adj[i][j];
    }
  }

  // Inicializa a nova linha e coluna para 0 (sem conexões)
  for (int i = 0; i < n + 1; i++) {
    newAdj[n][i] = 0; // Nova linha
    newAdj[i][n] = 0; // Nova coluna
  }

  // Liberar a matriz original
  for (int i = 0; i < n; i++)
    delete[] adj[i];
  delete[] adj;

  // Atualiza a matriz para a nova matriz
  adj = newAdj;
  n++;
  m = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (adj[i][j] == 1) {
        m++;
      }
    }
  }
}
//// implementacao samy

int buscaEmLargura(int origem, int destino, int n, int **adj) {
  // Vetor para marcar os vértices como visitados
  int *visitado = new int[n];

  for (int i = 0; i < n; i++)
    visitado[i] = 0;

  // Fila para a BFS
  std::queue<int> fila;
  fila.push(origem);
  visitado[origem] = 1;

  while (!fila.empty()) {
    int verticeAtual = fila.front();
    fila.pop();

    // Verifique se o vértice atual é o destino
    if (verticeAtual == destino) {
      return 1; // Encontrou o destino
    }

    // Percorra todos os vizinhos do vértice atual
    for (int i = 0; i < n; i++) {
      int vizinho = adj[verticeAtual][i];
      if (visitado[vizinho] == 0) {
        fila.push(vizinho);
        visitado[vizinho] = 1;
      }
    }
  }

  return 0; // O destino não foi encontrado
}









bool TGrafo::desconexo() {
  if (n == 0) {
    return true; // Grafo vazio = desconexo (1)
  }
  
  int verticeInicial = 0;
  for (int i = 0; i < n; i++) {
    visitado[i] = 0; // Use o vetor visitado da classe TGrafo
  }

  std::queue<int> fila; //busca em largura a partir da fila
  fila.push(verticeInicial);
  visitado[verticeInicial] = 1;

  while (!fila.empty()) {
    int verticeAtual = fila.front();
    fila.pop();
    for (int i = 0; i < n; i++) { //varrendo vizinhos do verticeAtual
      if (adj[verticeAtual][i] != 0 && visitado[i] == 0) {
        fila.push(i);
        visitado[i] = 1;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (visitado[i] == 0) {
      return true; //(2)
    }
  }

  return false;
}

bool TGrafo::C1(){
  if (n == 0 || desconexo()) //não pode ser nenhum dos desses casos
    return false;

  for (int v = 0; v < n; v++) { // verificação de sf-conexo
    for (int w = 0; w < n; w++) {
      if (v != w) {
        // Verifique se há um caminho de v para w
        if (v != w && !buscaEmLargura(v, w, n, adj) && !buscaEmLargura(w, v, n, adj)) { //não há caminho em nenhum sentido para o par, portanto não é
          return true;
        }
      }
    }
  }
  return false;
}

bool TGrafo::C2(){
  if (n == 0)
    return false; // vazio

  // semi-fortemente conexo
  for (int v = 0; v < n; v++) {
    for (int w = 0; w < n; w++) {
      if (v != w) {
        if (v != w && !buscaEmLargura(v, w, n, adj) && !buscaEmLargura(w, v, n, adj)) {
          return false;
        }
      }
    }
  }

  // fortemente conexo
  for (int v = 0; v < n; v++) {
    for (int w = 0; w < n; w++) {
      if (v != w) {
        if (v != w && !buscaEmLargura(v, w, n, adj) || !buscaEmLargura(w, v, n, adj))
           return true; //não é fortemente conexo
      }
    }
  }
  return false;
}

bool TGrafo::C3(){
  if (n == 0 || !C2())
    return false;

  for (int v = 0; v < n; v++) {
    for (int w = 0; w < n; w++) {
      if (v != w) {
        if (v != w && !buscaEmLargura(v, w, n, adj) || !buscaEmLargura(w, v, n, adj)) {
          return false;
        }
      }
    }
  }
  return true;
}


void TGrafo::conectividade() {
    if (desconexo()) {
        cout << "\nA conexidade do grafo é: C0\n";
    } else if (C1()) {
        cout << "\nA conexidade do grafo é: C1\n";
    } else if (C2()) {
        cout << "\nA conexidade do grafo é: C2\n";
    } else if (C3()) {
        cout << "\nA conexidade do grafo é: C3\n";
    }
}
#endif

  std::cout << "espaço liberado";
}

// Insere uma aresta no Grafo tal que
// v é adjacente a w
void TGrafo::insereA(int v, int w, int peso) {
  //verifica se existe 2 vertices para criar uma aresta
  if (n < 1) {
    cout << "Você precisa de pelo menos 3 vértices para adicionar uma aresta." << endl;
    exit(1);
  }
  // testa se nao temos a aresta
  if (adj[v][w] == std::numeric_limits<int>::infinity()) {
    adj[v][w] = peso;
    m++; // atualiza qtd arestas
  }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w) {
  // Testa se temos a aresta
  if (adj[v][w] != std::numeric_limits<float>::infinity()) {
    adj[v][w] = 0;
    m--; // Atualiza a quantidade de arestas
  //for q percorre
    cout << "Aresta entre " << vertices[v].nome << " e " << vertices[w].nome << " removida com sucesso!"
         << endl;
  } else {
    cout << "Aresta entre " << vertices[v].nome << " e " << vertices[w].nome << " não existe." << endl;
  }
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida
void TGrafo::show(const std::vector<Vertice> &vertices) {
  std::cout << "n: " << n << std::endl;
  std::cout << "m: " << m << std::endl;
  for (int i = 0; i < n; i++) {
    for (int w = 0; w < n; w++) {
      int peso = getPesoAresta(i, w);
      if (peso > 0) {
        std::cout << "\nDistancia de " << vertices[i].nome << " para "<< vertices[w].nome << " é de " << peso << " km\n";
      }
    }
  }
}
void TGrafo::showMatriz(const std::vector<Vertice> &vertices) {
    std::cout << "n: " << n << std::endl;
  std::cout << "m: " << m << std::endl;
  for (int i = 0; i < n; i++) {
    for (int w = 0; w < n; w++) {
      int peso = getPesoAresta(i, w);
      if (peso > 0) {
                std::cout << "Adj[" << vertices[i].numero << "," << vertices[w].numero << "] = " << peso << " ";
            } 
        }
    }
    cout << "\nfim da impressao do grafo." << endl;
}
int TGrafo::addcidade(const std::string &nome) {
    // Cria uma nova matriz com tamanho aumentado (n + 1)
    int **newAdj = new int *[n + 1];
    for (int i = 0; i < n + 1; i++)
        newAdj[i] = new int[n + 1];

    // Copia os elementos da matriz original para a nova matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            newAdj[i][j] = adj[i][j];
        }
    }

    // Inicializa a nova linha e coluna para 0 (sem conexões)
    for (int i = 0; i < n + 1; i++) {
        newAdj[n][i] = 0; // Nova linha
        newAdj[i][n] = 0; // Nova coluna
    }

    // Copia as arestas da matriz original para a nova matriz
    for (int i = 0; i < n; i++) {
        newAdj[i][n] = 0; // Nova coluna (saída do novo vértice)
        newAdj[n][i] = 0; // Nova linha (entrada para o novo vértice)
    }

    // Liberar a matriz original
    for (int i = 0; i < n; i++)
        delete[] adj[i];
    delete[] adj;

    // Atualiza a matriz para a nova matriz
    adj = newAdj;
    n++;

    // Atualiza o nome do vértice recém-adicionado e insere no final do vetor
    vertices.push_back({n - 1, nome});

    // Retorna a posição onde o vértice foi inserido (índice baseado em zero)
    return n - 1;
}
void mostrarArquivo(const std::string &nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);

  if (!arquivo.is_open()) {
    std::cerr << "Erro ao abrir o arquivo." << std::endl;
    return;
  }

  // Lê e mostra o conteúdo do arquivo linha por linha
  std::string linha;
  while (std::getline(arquivo, linha)) {
    std::cout << linha << std::endl;
  }

  arquivo.close();
}

void TGrafo::removeVertice(const std::string &nome) {
    // Converter o nome inserido pelo usuário para letras minúsculas
    std::string nomeMinusc = nome;
    std::transform(nomeMinusc.begin(), nomeMinusc.end(), nomeMinusc.begin(), ::tolower);

    int verticeIndex = -1; // Inicialize como -1 para indicar que o vértice não foi encontrado

    // Encontre o índice do vértice com o nome correspondente (em minúsculas)
    for (int i = 0; i < n; i++) {
        std::string nomeVertice = vertices[i].nome;
        std::transform(nomeVertice.begin(), nomeVertice.end(), nomeVertice.begin(), ::tolower);
        if (nomeMinusc == nomeVertice) {
            verticeIndex = i;
            break;
        }
    }

    if (verticeIndex == -1) {
        cout << "Vértice com o nome '" << nome << "' não encontrado." << endl;
        return;
    }

    // Remova o vértice do vetor de vértices
    vertices.erase(vertices.begin() + verticeIndex);
    n--;

    // Redimensione a matriz de adjacência para refletir a remoção do vértice
    for (int i = verticeIndex; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = adj[i + 1][j];
        }
    }
    for (int j = verticeIndex; j < n; j++) {
        for (int i = 0; i < n; i++) {
            adj[i][j] = adj[i][j + 1];
        }
    }

    // Atualize a contagem de arestas (m) adequadamente
    m = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != std::numeric_limits<int>::infinity()) {
                m++;
            }
        }
    }

    cout << nome << " removido com sucesso!" << endl;
}
void TGrafo::adicionaVertice() {
  // Cria uma nova matriz com tamanho aumentado (n + 1)
  int **newAdj = new int *[n + 1];
  for (int i = 0; i < n + 1; i++)
    newAdj[i] = new int[n + 1];

  // Copia os elementos da matriz original para a nova matriz
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      newAdj[i][j] = adj[i][j];
    }
  }

  // Inicializa a nova linha e coluna para 0 (sem conexões)
  for (int i = 0; i < n + 1; i++) {
    newAdj[n][i] = 0; // Nova linha
    newAdj[i][n] = 0; // Nova coluna
  }

  // Liberar a matriz original
  for (int i = 0; i < n; i++)
    delete[] adj[i];
  delete[] adj;

  // Atualiza a matriz para a nova matriz
  adj = newAdj;
  n++;
  m = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (adj[i][j] == 1) {
        m++;
      }
    }
  }
}
//// implementacao samy

int buscaEmLargura(int origem, int destino, int n, int **adj) {
  // Vetor para marcar os vértices como visitados
  int *visitado = new int[n];

  for (int i = 0; i < n; i++)
    visitado[i] = 0;

  // Fila para a BFS
  std::queue<int> fila;
  fila.push(origem);
  visitado[origem] = 1;

  while (!fila.empty()) {
    int verticeAtual = fila.front();
    fila.pop();

    // Verifique se o vértice atual é o destino
    if (verticeAtual == destino) {
      return 1; // Encontrou o destino
    }

    // Percorra todos os vizinhos do vértice atual
    for (int i = 0; i < n; i++) {
      int vizinho = adj[verticeAtual][i];
      if (visitado[vizinho] == 0) {
        fila.push(vizinho);
        visitado[vizinho] = 1;
      }
    }
  }

  return 0; // O destino não foi encontrado
}









bool TGrafo::desconexo() {
  if (n == 0) {
    return true; // Grafo vazio = desconexo (1)
  }
  
  int verticeInicial = 0;
  for (int i = 0; i < n; i++) {
    visitado[i] = 0; // Use o vetor visitado da classe TGrafo
  }

  std::queue<int> fila; //busca em largura a partir da fila
  fila.push(verticeInicial);
  visitado[verticeInicial] = 1;

  while (!fila.empty()) {
    int verticeAtual = fila.front();
    fila.pop();
    for (int i = 0; i < n; i++) { //varrendo vizinhos do verticeAtual
      if (adj[verticeAtual][i] != 0 && visitado[i] == 0) {
        fila.push(i);
        visitado[i] = 1;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (visitado[i] == 0) {
      return true; //(2)
    }
  }

  return false;
}

bool TGrafo::C1(){
  if (n == 0 || desconexo()) //não pode ser nenhum dos desses casos
    return false;

  for (int v = 0; v < n; v++) { // verificação de sf-conexo
    for (int w = 0; w < n; w++) {
      if (v != w) {
        // Verifique se há um caminho de v para w
        if (v != w && !buscaEmLargura(v, w, n, adj) && !buscaEmLargura(w, v, n, adj)) { //não há caminho em nenhum sentido para o par, portanto não é
          return true;
        }
      }
    }
  }
  return false;
}

bool TGrafo::C2(){
  if (n == 0)
    return false; // vazio

  // semi-fortemente conexo
  for (int v = 0; v < n; v++) {
    for (int w = 0; w < n; w++) {
      if (v != w) {
        if (v != w && !buscaEmLargura(v, w, n, adj) && !buscaEmLargura(w, v, n, adj)) {
          return false;
        }
      }
    }
  }

  // fortemente conexo
  for (int v = 0; v < n; v++) {
    for (int w = 0; w < n; w++) {
      if (v != w) {
        if (v != w && !buscaEmLargura(v, w, n, adj) || !buscaEmLargura(w, v, n, adj))
           return true; //não é fortemente conexo
      }
    }
  }
  return false;
}

bool TGrafo::C3(){
  if (n == 0 || !C2())
    return false;

  for (int v = 0; v < n; v++) {
    for (int w = 0; w < n; w++) {
      if (v != w) {
        if (v != w && !buscaEmLargura(v, w, n, adj) || !buscaEmLargura(w, v, n, adj)) {
          return false;
        }
      }
    }
  }
  return true;
}


void TGrafo::conectividade() {
    if (!desconexo()) {
        cout << "\nA conexidade do grafo é: C1\n";
    } else if (C1()) {
        cout << "\nA conexidade do grafo é: C2\n";
    } else if (C2()) {
        cout << "\nA conexidade do grafo é: C0\n";
    } else if (C3()) {
        cout << "\nA conexidade do grafo é: C3\n";
    }
}
#endif
