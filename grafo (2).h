/*
  Augusto Esteves Carrera - 32114842
  Henrique Lee Amorim - 32151071
  Lorenzo Percussi - 32167318
  Samy Idesis - 32164025

 Alterações:
 dia 24/11 = implementação do algoritmo de coloração sequencial e das checagens eulerianas - augusto, samy
 dia 25/11 = implementação da solução do problema inicial (caminho minimo) e da checagem de grau do vertice = lorenzo e henrique
*/

#include <algorithm> // Para a função transform
#include <cctype>    // Para a função tolower
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string> // Para manipulação de strings
#include <vector>
#include <set>

using namespace std;

#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

struct Vertice {
  int numero;
  std::string nome;
};

class TGrafo {
private:
  int n; // quantidade de vértices
  int m;
  int **adj; // matriz de adjacência
  int peso;
  std::vector<int> distancia;
  std::vector<int> predecessores;
  std::vector<bool> visitado;

  void inicializarDijkstra();
  void relaxamento(int u, int v, int peso);

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
  void imprimirGrafoParaArquivo(const std::string &nomeArquivo,
                                int tipoGrafo) const;
  int buscaemLargura();
  void limparGrafo();
  int conectividade();
  void coloracaoSequencial();
  bool ehGrafoEuleriano();
  bool admitePercursoEuleriano();
  bool temPercursoEuleriano();
  void mostrarArquivo(const std::string &nomeArquivo);
  int getNumVertices() const { return n; }
  int getNumArestas() const { return m; }
  std::vector<int> dijkstra(int origem, int destino);

  int getPesoAresta(int v, int w) const {
    if (v >= 0 && v < n && w >= 0 && w < n) {
      return adj[v][w];
    }
    return std::numeric_limits<int>::infinity(); // Retorna infinito se a aresta
                                                 // não existir
  }
};

std::vector<Vertice>
    vertices; // Vetor de estruturas para armazenar números e nomes
void TGrafo::limparGrafo() {
  // Limpe os vetores de vértices e arestas, ou faça qualquer outra operação de
  // limpeza necessária.
  vertices.clear();
  // Limpe a matriz de adjacência (ou qualquer outra estrutura que você esteja
  // usando para representar o grafo). Lembre-se de atualizar n para 0 ou o
  // valor inicial apropriado.
  n = 0;
  // Outras operações de limpeza, se necessário.
}
void TGrafo::imprimirGrafoParaArquivo(const std::string &nomeArquivo,
                                      int tipoGrafo) const {
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
  std::cout << "espaço liberado";
}

// Insere uma aresta no Grafo tal que
// v é adjacente a w
void TGrafo::insereA(int v, int w, int peso) {
  // verifica se existe 2 vertices para criar uma aresta
  if (n < 1) {
    cout << "Você precisa de pelo menos 3 vértices para adicionar uma aresta."
         << endl;
    return;
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
         // for q percorre
    cout << "Aresta entre " << vertices[v].nome << " e " << vertices[w].nome
         << " removida com sucesso!" << endl;
  } else {
    cout << "Aresta entre " << vertices[v].nome << " e " << vertices[w].nome
         << " não existe." << endl;
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
        std::cout << "\nDistancia de " << vertices[i].nome << " para "
                  << vertices[w].nome << " é de " << peso << " km\n";
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
        std::cout << "Adj[" << vertices[i].numero << "," << vertices[w].numero
                  << "] = " << peso << " ";
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
  std::transform(nomeMinusc.begin(), nomeMinusc.end(), nomeMinusc.begin(),
                 ::tolower);

  int verticeIndex =
      -1; // Inicialize como -1 para indicar que o vértice não foi encontrado

  // Encontre o índice do vértice com o nome correspondente (em minúsculas)
  for (int i = 0; i < n; i++) {
    std::string nomeVertice = vertices[i].nome;
    std::transform(nomeVertice.begin(), nomeVertice.end(), nomeVertice.begin(),
                   ::tolower);
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

// Update the TGrafo::conectividade function
int TGrafo::conectividade() {
    // C0 - Desconexo: Verifique se existe ao menos um par de vértices não unidos por uma cadeia.
for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
    if (i != j && adj[i][j] == std::numeric_limits<int>::infinity()) {
      cout << "Categoria de Conectividade: C0 - Desconexo" << endl;
        return 0;
    }
  }
}

    // C1 - Simplesmente Conexo: Verifique se todo par de vértices é unido por ao menos uma cadeia.
bool simplesmenteConexo = true;
for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
    if (i != j && adj[i][j] == std::numeric_limits<int>::infinity()) {
      simplesmenteConexo = false;
      break;
    }
  }
  if (!simplesmenteConexo) break;
}

if (simplesmenteConexo) {
// C2 - Semi Fortemente Conexo: Verifique se todo par de vértices é atingível a partir do outro.
bool semiFortementeConexo = true;
  for (int i = 0; i < n; i++) {
    if (!semiFortementeConexo) {
      for (int j = 0; j < n; j++) {
        if (i != j && (adj[i][j] != std::numeric_limits<int>::infinity() || adj[j][i] != std::numeric_limits<int>::infinity())) {
          semiFortementeConexo = false;
          break;
        }
      }
    }
  }

if (semiFortementeConexo) {
// C3 - Fortemente Conexo: Se chegou aqui, é fortemente conexo.
  cout << "Categoria de Conectividade: C2 - semiFortemente Conexo" << endl;
    return 2;
}else {
      cout << "Categoria de Conectividade: C1 - simplesmente Conexo" << endl;
      return 1;
 }
}
else { //Se não entrou nos outros
      cout << "Categoria de Conectividade: C3 - Fortemente Conexo" << endl;
      return 3;
    }
}

void TGrafo::coloracaoSequencial() {
  // Vetor para armazenar as cores dos vértices
  std::vector<int> cores(n, -1);

  // Loop para colorir os vértices
  for (int i = 0; i < n; i++) {
    // Conjunto para armazenar as cores disponíveis
    std::set<int> coresDisponiveis;

    // Verifica as cores já atribuídas aos vértices adjacentes
    for (int j = 0; j < n; j++) {
      if (adj[i][j] != std::numeric_limits<int>::infinity() && cores[j] != -1) {
        coresDisponiveis.insert(cores[j]);
      }
    }

    // Encontra a primeira cor disponível
    int cor = 0;
    while (coresDisponiveis.find(cor) != coresDisponiveis.end()) {
      cor++;
    }

    // Atribui a cor encontrada ao vértice
    cores[i] = cor;
  }

  // Mostra as cores atribuídas aos vértices
  std::cout << "Cores atribuídas aos vértices:" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "Vértice " << vertices[i].nome << ": Cor " << cores[i] << std::endl;
  }
}

bool TGrafo::ehGrafoEuleriano() {
    // Um grafo é euleriano se todos os vértices têm grau par
    for (int i = 0; i < n; i++) {
        int grau = 0;
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != std::numeric_limits<int>::infinity()) {
                grau++;
            }
        }
        if (grau % 2 != 0) {
            cout << "O grafo não é euleriano, pois o vértice " << vertices[i].nome << " tem grau ímpar." << endl;
            return false;
        }
    }

    cout << "O grafo é euleriano." << endl;
    return true;
}

bool TGrafo::temPercursoEuleriano() {
    // Um grafo tem percurso euleriano se for conectado e no máximo dois vértices têm grau ímpar
    if (conectividade() == 0) {
        cout << "O grafo não tem percurso euleriano, pois não é conectado." << endl;
        return false;
    }

    int verticesImpares = 0;
    for (int i = 0; i < n; i++) {
        int grau = 0;
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != std::numeric_limits<int>::infinity()) {
                grau++;
            }
        }
        if (grau % 2 != 0) {
            verticesImpares++;
            if (verticesImpares > 2) {
                cout << "O grafo não tem percurso euleriano, pois mais de dois vértices têm grau ímpar." << endl;
                return false;
            }
        }
    }

    cout << "O grafo tem percurso euleriano." << endl;
    return true;
}

bool TGrafo::admitePercursoEuleriano() {
    // Um grafo admite percurso euleriano se for conexo e no máximo dois vértices têm grau ímpar
    if (conectividade() != 3) {
        cout << "O grafo não admite percurso euleriano, pois não é fortemente conexo." << endl;
        return false;
    }

    int verticesImpares = 0;
    for (int i = 0; i < n; i++) {
        int grau = 0;
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != std::numeric_limits<int>::infinity()) {
                grau++;
            }
        }
        if (grau % 2 != 0) {
            verticesImpares++;
            if (verticesImpares > 2) {
                cout << "O grafo não admite percurso euleriano, pois mais de dois vértices têm grau ímpar." << endl;
                return false;
            }
        }
    }

    cout << "O grafo admite percurso euleriano." << endl;
    return true;
}
void TGrafo::inicializarDijkstra() {
    distancia.assign(n, std::numeric_limits<int>::max());
    predecessores.assign(n, -1);
    visitado.assign(n, false);
}

void TGrafo::relaxamento(int u, int v, int peso) {
    if (!visitado[v] && distancia[u] + peso < distancia[v]) {
        distancia[v] = distancia[u] + peso;
        predecessores[v] = u;
    }
}

std::vector<int> TGrafo::dijkstra(int origem, int destino) {
    inicializarDijkstra();

    distancia[origem] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> filaPrioridade;
    filaPrioridade.push({0, origem});

    while (!filaPrioridade.empty()) {
        int u = filaPrioridade.top().second;
        filaPrioridade.pop();

        if (visitado[u]) {
            continue;
        }

        visitado[u] = true;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] != std::numeric_limits<int>::infinity()) {
                relaxamento(u, v, adj[u][v]);
                filaPrioridade.push({distancia[v], v});
            }
        }
    }

    return predecessores;
}



#endif
