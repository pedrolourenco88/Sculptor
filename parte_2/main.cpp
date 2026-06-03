#include <iostream>
#include <fstream>
#include <sstream> // fatiador de strings. essencial para extrair as variáveis do texto
#include <string>
#include <vector>
#include "sculptor.h"
#include "figurageometrica.h"
// g++ -Wall -Wextra -O2 main.cpp sculptor.cpp figurageometrica.cpp -o escultor
int main(){
  
  //tenta abrir o arquivo de configuração de onde as instruções virão.
  std::ifstream file("anel.txt");

  //aborto a execução imediatamente se o arquivo não existir. 
  //evita que o programa tente ler o vazio e cause Segmentation Fault.
  if(!file.is_open()){
    std::cout << "deu ruim, man. pode não!" << std::endl;
    return 1;
  }

  //fila de execução guarda ponteiros da classe base.
  std::vector<FiguraGeometrica*> figuras;
  
  //o motor nasce nulo. Só vou instancia-lo quando ler as dimensões reais do comando 'dim' do doc.
  Sculptor *motor = nullptr;

  std::string linha, comando;
  
  //le o arquivo linha por linha até o fim (EOF).
  while(std::getline(file, linha)){// vai pegar o conteudo da linha até o \n e mandar para a variavel linha
    std::stringstream ss(linha); // transfere apenas os caracteres para ss
    ss >> comando; // extrai a primeira palavra para definir a rota de execução.

    //criação do espaço 3D
    if(comando == "dim"){
      int nx, ny,nz;
      ss >> nx >> ny >> nz;// o >> continua a extranção de onde o anterior parou
      motor = new Sculptor(nx, ny, nz);
    }
 
    // extraio os parâmetros exatos da string original, crio o objeto na Heap usando 'new' 
    // e empurro o ponteiro para a fila. agora nenhuma figura é desenhada ainda.
    else if(comando == "putVoxel"){
      int x, y, z;
      float r, g, b, a;
      ss >> x >> y >> z >> r >> g >> b >> a;
      figuras.push_back(new PutVoxel(x, y, z, r, g, b, a));
    }

    else if(comando == "cutVoxel"){
      int x, y, z;
      ss >> x >> y >> z;
      figuras.push_back(new CutVoxel(x, y, z));
    }
    
    else if(comando == "putBox"){
      int x0, x1, y0, y1, z0, z1;
      float r, g, b, a;
      ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
      figuras.push_back(new PutBox(x0, x1, y0, y1, z0, z1, r, g, b, a));
    }

    else if(comando == "cutBox"){
      int x0, x1, y0, y1, z0, z1;
      ss >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
      figuras.push_back(new CutBox(x0, x1, y0, y1, z0, z1));
    }

    else if(comando == "putSphere"){
      int x, y, z, radius;
      float r, g, b, a;
      ss >> x >> y >> z >> radius >> r >> g >> b >> a;
      figuras.push_back(new PutSphere(x, y, z, radius, r, g, b, a));
    }

    else if(comando == "cutSphere"){
      int x, y, z, radius;
      ss >> x >> y >> z >> radius;
      figuras.push_back(new CutSphere(x, y, z, radius));
    }

    else if(comando == "putEllipsoid"){
      int xcenter, ycenter, zcenter, rx, ry, rz ;
      float r, g, b, a;
      ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz >> r >> g >> b >> a;
      figuras.push_back(new PutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz, r, g, b, a));
    }

    else if(comando == "cutEllipsoid"){
      int xcenter, ycenter, zcenter, rx, ry, rz ;
      ss >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz;
      figuras.push_back(new CutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz));
    }
  }
  file.close(); // libera o arquivo de texto do SO.

  //garanto que o txt tinha o comando 'dim' e o motor foi criado antes de tentar usá-lo.
  if (motor != nullptr) {
    // teve um warning aqui pois .size() retorna o tipo size_t que é diferente do int
    // varro o vetor. o C++ invoca o draw() da subclasse correspondente.
    for (size_t i = 0; i < figuras.size(); i++) {
      figuras[i]->draw(*motor); // o C++ descobre sozinho qual draw() chamar, não é magia é tecnologia
    }
  
    // traduz a malha de voxels resultante para as faces geométricas do arquivo .off.
    motor->writeOFF("escultura_prime.off");

    // destruo os objetos que instanciei via 'new' nos 'else if' para devolver a memória RAM, que ta caro, ao sistema.
    for (size_t i = 0; i < figuras.size(); i++) { // aqui também teve warning.
      delete figuras[i];
    }
    // por fim, destruo o próprio motor (chama o ~Sculptor automaticamente limpando a matriz 3D).
    delete motor;
    }
  return 0; // execução ocorreu sem erros S2
}