#include "grafo.h"
int main() {
  int tipoGrafo, nVertice, nAresta;
  TGrafo grafo(0);
  setlocale(LC_ALL, "Portuguese");
  char escolha = 'z';
  while (escolha != 'j') {
    std::cout << "Menu Distancia Maiores Cidades:" << std::endl;
        std::cout << "a) Ler dados do arquivo grafo.txt" << std::endl;
        std::cout << "b) Gravar dados no arquivo grafo.txt" << std::endl;
        std::cout << "c) Inserir vértice" << std::endl;
        std::cout << "d) Inserir aresta" << std::endl;
        std::cout << "e) Remover vértice" << std::endl;
        std::cout << "f) Remover aresta" << std::endl;
        std::cout << "g) Mostrar conteúdo do arquivo" << std::endl;
        std::cout << "h) Mostrar grafo" << std::endl;
        std::cout << "i) Apresentar a conexidade do grafo e o reduzido" << std::endl;
        std::cout << "j) Encerrar a aplicação" << std::endl;
    
        std::cout << "Escolha uma opção (a-j): ";
    cin >> escolha;

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
        std::string nomeArquivo = "grafoteste.txt"; 
        mostrarArquivo(nomeArquivo);
        break;
  
      }
      case 'h': {
        grafo.show(vertices); // Passe o vetor 'vertices' como argumento
        grafo.showMatriz(vertices);
        break;
      }
      case 'i': {
        grafo.conectividade();
        break;
  
        }
      case 'j': {
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
