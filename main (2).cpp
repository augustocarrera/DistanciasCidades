/*
  Augusto Esteves Carrera - 32114842
  Henrique Lee Amorim - 32151071
  Lorenzo Percussi - 32167318
  Samy Idesis - 32164025

 Alterações:
 dia 24/11 = implementação do algoritmo de coloração sequencial e das checagens eulerianas - augusto, samy
 dia 25/11 = implementação da solução do problema inicial (caminho minimo) e da checagem de grau do vertice = lorenzo e henrique
*/
#include "grafo.h"
int main() {
  int tipoGrafo, nVertice, nAresta;
  TGrafo grafo(0);
  setlocale(LC_ALL, "Portuguese");
  char escolha = 'z';
  while (escolha != 'j') {
    std::cout << "\nMenu Distancia Maiores Cidades:" << std::endl;
        std::cout << "a) Ler dados do arquivo grafo.txt" << std::endl;
        std::cout << "b) Gravar dados no arquivo grafo.txt" << std::endl;
        std::cout << "c) Inserir vértice" << std::endl;
        std::cout << "d) Inserir aresta" << std::endl;
        std::cout << "e) Remover vértice" << std::endl;
        std::cout << "f) Remover aresta" << std::endl;
        std::cout << "g) Mostrar conteúdo do arquivo" << std::endl;
        std::cout << "h) Mostrar grafo" << std::endl;
        std::cout << "i) Apresentar a conexidade do grafo e o reduzido" << std::endl;
        std::cout << "j) Coloração Sequencial" << std::endl;
        std::cout << "k) Euleriano" << std::endl;
        std::cout << "l) Caminho Mínimo (Dijkstra)" << std::endl;
        std::cout << "m) Grau do Vértice" << std::endl;
        std::cout << "n) Encerrar a aplicação" << std::endl;
        std::cout << "Escolha uma opção (a-n): ";
    std::cin >> escolha;

    escolha = std::tolower(escolha);
    switch (escolha) {
      case 'a': {
        grafo.limparGrafo();
        FILE *arquivo = fopen("grafo.txt", "rt");

    if (arquivo == NULL) {
        std::cout << "Arquivo nao encontrado" << std::endl;
        return -1;
    }

    char linha[500];
    int nVertice, nAresta;

    if (fgets(linha, sizeof(linha), arquivo)) {
        tipoGrafo = atoi(linha);
        if (fgets(linha, sizeof(linha), arquivo)) {
            nVertice = atoi(linha);
        }
    }



    for (int i = 0; i < nVertice; i++) {
    if (fgets(linha, sizeof(linha), arquivo)) {
        Vertice v;
        char *ptr = strchr(linha, ' '); // Encontra o primeiro espaço em branco
        if (ptr != nullptr) {
            *ptr = '\0'; // Substitui o primeiro espaço em branco por '\0' para separar o número e o nome
            v.numero = atoi(linha); // Converte o número para int
            v.nome = ptr + 1; // Obtém o rótulo do vértice (nome)

            //Acha o \n para remover
            size_t pos = v.nome.find('\n');
            // Verifique se o caractere de nova linha foi encontrado
            if (pos != std::string::npos) {
                // Remova o caractere de nova linha
                v.nome.erase(pos);
            }

            // Converter o nome do vértice para letras minúsculas
            std::transform(v.nome.begin(), v.nome.end(), v.nome.begin(), ::tolower);

            vertices.push_back(v);

            // Em seguida, adicione o vértice ao grafo se necessário
            grafo.adicionaVertice();
        }
    }
}

    if (fgets(linha, sizeof(linha), arquivo)) {
        nAresta = atoi(linha);
    }
    for (int j = 0; j < nAresta; j++) {
        if (fgets(linha, sizeof(linha), arquivo)) {
            char *ptr = strtok(linha, " ");
            int n = atoi(ptr);
            ptr = strtok(nullptr, " ");
            int m = atoi(ptr);
            ptr = strtok(nullptr, " ");
            int peso = atoi(ptr);
            grafo.insereA(n, m, peso);
        } else {
            break;
        }
    }

    fclose(arquivo);

    // Agora, você pode acessar os números e nomes dos vértices usando o vetor 'vertices'
    for (const Vertice& v : vertices) {
    std::cout << "\nNúmero: " << v.numero << ", Nome: " << v.nome << std::endl;
}
    break;
    return 0;
}

      case 'b': {
        grafo.imprimirGrafoParaArquivo("grafo.txt", tipoGrafo); // Passe o tipoGrafo como argumento
    break;
    
      }
      case 'c': {
    std::string nome;
      std::cout << "Digite o nome do vértice a ser adicionado: ";
      std::cin.ignore(); // Limpa o caractere de nova linha pendente
      std::getline(std::cin, nome);

      // Converter o nome para letras minúsculas
      std::transform(nome.begin(), nome.end(), nome.begin(), ::tolower);

      grafo.addcidade(nome);
      std::cout << "Vértice adicionado com sucesso" << std::endl;
      break;
}
      case 'd': {
        std::string cidadePartida, cidadeDestino;
    float distancia;
    
    std::cout << "Digite a cidade de partida: ";
    std::cin.ignore(); // Limpar o buffer de entrada
    std::getline(std::cin, cidadePartida);
    
    std::cout << "Digite a cidade de destino: ";
    std::getline(std::cin, cidadeDestino);
    
    std::cout << "Digite a distância: ";
    std::cin >> distancia;

    std::transform(cidadePartida.begin(), cidadePartida.end(), cidadePartida.begin(), ::tolower);
    std::transform(cidadeDestino.begin(), cidadeDestino.end(), cidadeDestino.begin(), ::tolower);
    // Encontrar os números correspondentes aos nomes das cidades
    int numeroPartida = -1;
    int numeroDestino = -1;
    
    for (const Vertice& v : vertices) {
        if (v.nome == cidadePartida) {
            numeroPartida = v.numero;
        }
        if (v.nome == cidadeDestino) {
            numeroDestino = v.numero;
        }
    }
    
    if (numeroPartida != -1 && numeroDestino != -1) {
        grafo.insereA(numeroPartida, numeroDestino, distancia);
        std::cout << "Aresta adicionada com sucesso" << std::endl;
    } else {
        std::cout << "Cidades não encontradas. Verifique os nomes." << std::endl;
    }
    
    break;
      }
      case 'e': {
        std::cout << "Qual vértice deseja remover?" << std::endl;
        std::string nome;
        std::cin.ignore(); // Limpar o buffer de entrada
        std::getline(std::cin, nome);
        
        // Converter o nome para letras minúsculas
        std::transform(nome.begin(), nome.end(), nome.begin(), ::tolower);
        
        grafo.removeVertice(nome);
        break;
      }
      case 'f': {
        std::string cidadePartida, cidadeDestino;
    
    std::cout << "Qual aresta deseja remover? (de qual cidade para qual)" << std::endl;
    std::cout << "Digite a cidade de partida: ";
    std::cin.ignore(); // Limpar o buffer de entrada
    std::getline(std::cin, cidadePartida);
    
    std::cout << "Digite a cidade de destino: ";
    std::getline(std::cin, cidadeDestino);
    
    // Converter a entrada do usuário para letras minúsculas
    std::transform(cidadePartida.begin(), cidadePartida.end(), cidadePartida.begin(), ::tolower);
    std::transform(cidadeDestino.begin(), cidadeDestino.end(), cidadeDestino.begin(), ::tolower);
    
    // Encontrar os números correspondentes aos nomes das cidades
    int numeroPartida = -1;
    int numeroDestino = -1;
    
    for (const Vertice& v : vertices) {
        std::string nomeVertice = v.nome;
        // Converter o nome do vértice para letras minúsculas para comparação
        std::transform(nomeVertice.begin(), nomeVertice.end(), nomeVertice.begin(), ::tolower);
        
        if (nomeVertice == cidadePartida) {
            numeroPartida = v.numero;
        }
        if (nomeVertice == cidadeDestino) {
            numeroDestino = v.numero;
        }
    }
    
    if (numeroPartida != -1 && numeroDestino != -1) {
        grafo.removeA(numeroPartida, numeroDestino);
    } else {
        std::cout << "Cidades não encontradas. Verifique os nomes." << std::endl;
    }
    
    break;
      }
      case 'g': {
        std::string nomeArquivo = "grafo.txt"; 
        mostrarArquivo(nomeArquivo);
        break;
  
      }
      case 'h': {
        grafo.show(vertices); // Passe o vetor 'vertices' como argumento
        //grafo.showMatriz(vertices);
        break;
      }
      case 'i': {
        grafo.conectividade();
        break;
  
        }
      case 'j': {
          grafo.coloracaoSequencial();
          break;
      }
      case 'k': {
          grafo.conectividade();
          if (grafo.ehGrafoEuleriano()) {
              if (grafo.temPercursoEuleriano()) {
              } else {
                  std::cout << "Não há percurso euleriano no grafo." << std::endl;
              }
          grafo.admitePercursoEuleriano();
          }
          break;
      }
      case 'l': {
          std::string cidadeOrigem, cidadeDestino;

          // Solicitar ao usuário os nomes das cidades de origem e destino
          std::cout << "Digite o nome da cidade de origem: ";
          std::cin.ignore(); // Limpar o buffer de entrada
          std::getline(std::cin, cidadeOrigem);

          std::cout << "Digite o nome da cidade de destino: ";
          std::getline(std::cin, cidadeDestino);

          // Converter os nomes para letras minúsculas
          std::transform(cidadeOrigem.begin(), cidadeOrigem.end(), cidadeOrigem.begin(), ::tolower);
          std::transform(cidadeDestino.begin(), cidadeDestino.end(), cidadeDestino.begin(), ::tolower);

          // Encontrar os números correspondentes aos nomes das cidades
          int numeroOrigem = -1;
          int numeroDestino = -1;

          for (const Vertice& v : vertices) {
              std::string nomeVertice = v.nome;
              // Converter o nome do vértice para letras minúsculas para comparação
              std::transform(nomeVertice.begin(), nomeVertice.end(), nomeVertice.begin(), ::tolower);

              if (nomeVertice == cidadeOrigem) {
                  numeroOrigem = v.numero;
              }
              if (nomeVertice == cidadeDestino) {
                  numeroDestino = v.numero;
              }
          }

          // Verificar se as cidades foram encontradas
          if (numeroOrigem != -1 && numeroDestino != -1) {
              // Executar o algoritmo de Dijkstra
              std::vector<int> predecessores = grafo.dijkstra(numeroOrigem, numeroDestino);

              // Exibir o caminho mínimo
              std::cout << "\nCaminho mínimo de " << cidadeOrigem << " para " << cidadeDestino << ": \n";
              int v = numeroDestino;
              std::stack<int> caminho;

              while (v != numeroOrigem) {
                  caminho.push(v);
                  v = predecessores[v];
              }

              std::cout << cidadeOrigem;
              while (!caminho.empty()) {
                  std::cout << " -> " << vertices[caminho.top()].nome;
                  caminho.pop();
              }

              std::cout << std::endl;
          } else {
              std::cout << "Cidades não encontradas. Verifique os nomes." << std::endl;
          }

          break;
      }


      case 'm': {
          std::string nomeVertice;
          std::cout << "Digite o nome do vértice para verificar o grau: ";
          std::cin.ignore(); // Limpar o buffer de entrada
          std::getline(std::cin, nomeVertice);

          // Converter o nome para letras minúsculas
          std::transform(nomeVertice.begin(), nomeVertice.end(), nomeVertice.begin(), ::tolower);

          // Encontrar o número correspondente ao nome do vértice
          int numeroVertice = -1;

          for (const Vertice& v : vertices) {
              if (v.nome == nomeVertice) {
                  numeroVertice = v.numero;
                  break;
              }
          }

          if (numeroVertice != -1) {
              int grau = 0;
              for (int i = 0; i < grafo.getNumVertices(); i++) {
                  if (grafo.getPesoAresta(numeroVertice, i) != std::numeric_limits<int>::infinity()) {
                      grau++;
                  }
              }
              std::cout << "O grau do vértice " << nomeVertice << " é " << grau << std::endl;
          } else {
              std::cout << "Vértice não encontrado. Verifique o nome." << std::endl;
          }

          break;
      }

      case 'n': {
        std::cout << "Encerrando a aplicação." << std::endl;
        break;;
      }
  
      default:{
        cout << "\nOpção inválida. Tente novamente." << endl;
        break;
      }
    }
  }
  return 0;
};
