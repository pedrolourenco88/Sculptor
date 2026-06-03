#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    //construtor. inicializo as dimensões da malha 3D.
    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;

    //zero a cor inicial do pincel.
    this->r = 0.0;
    this->g = 0.0;
    this->b = 0.0;
    this->a = 0.0;

    // alocação dinâmica da matriz 3D array de ponteiros para arrays.
    v = new Voxel**[_nx];
    for(int i=0; i<_nx; i++){
        v[i] = new Voxel*[_ny];
        for(int j=0; j<_ny; j++){
            v[i][j] = new Voxel[_nz];
            for(int k=0; k<_nz; k++){
                // garanto que a matriz nasça limpa. blocos invisíveis e sem cor.
                v[i][j][k].r = 0.0;
                v[i][j][k].g = 0.0;
                v[i][j][k].b = 0.0;
                v[i][j][k].a = 0.0; 
                v[i][j][k].show = false;   
            }
        }
    }
}

Sculptor::~Sculptor(){
    //destrutor. desaloco a memória de dentro para fora (Z -> Y -> X) para evitar Memory Leak.
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
           delete[] v[i][j];  
        }
        delete[] v[i];
    }
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float a){
    // atualizo a cor de estado do motor. próximos blocos ativos herdarão isto.
    this-> r = r;
    this-> g = g;
    this-> b = b;
    this-> a = a;
}

void Sculptor::putVoxel(int x, int y, int z){ 
    // blindagem de memória. só escrevo na matriz se a coordenada existir de fato. os limites da matriz.
    if((x>=0 && x<nx) && (y>=0 && y<ny) && (z>=0 && z<nz)){ 
        v[x][y][z].show = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z){
    //apenas desligo o bloco, sem mexer na cor.
    if((x>=0 && x<nx) && (y>=0 && y<ny) && (z>=0 && z<nz)) 
        v[x][y][z].show = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    // itero sobre o volume estrito da caixa e... pinto
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    // mesma varredura de volume, mas repassando o trabalho de desligar para o cutVoxel.
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    // Bounding Box. calculo os limites da caixa externa para não varrer a matriz inteira mais uma vez
    int minX = xcenter - radius;
    int maxX = xcenter + radius;
    int minY = ycenter - radius;
    int maxY = ycenter + radius;
    int minZ = zcenter - radius;
    int maxZ = zcenter + radius;

    for(int i=minX; i<=maxX; i++){
        for(int j=minY; j<=maxY; j++){
            for(int k=minZ; k<=maxZ; k++){
               // inequação da esfera com multiplicação direta. nao usar pow()
               if((((i-xcenter)*(i-xcenter))+((j-ycenter)*(j-ycenter))+((k-zcenter)*(k-zcenter)))<=(radius*radius)){
                    putVoxel(i,j,k);
                }
            }
        } 
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    // mesma lógica da Bounding Box e da inequação, mas para esculpir/remover.
    int minX = xcenter - radius;
    int maxX = xcenter + radius;
    int minY = ycenter - radius;
    int maxY = ycenter + radius;
    int minZ = zcenter - radius;
    int maxZ = zcenter + radius;

    for(int i=minX; i<=maxX; i++){
        for(int j=minY; j<=maxY; j++){
            for(int k=minZ; k<=maxZ; k++){
               if((((i-xcenter)*(i-xcenter))+((j-ycenter)*(j-ycenter))+((k-zcenter)*(k-zcenter)))<=(radius*radius)){
                    cutVoxel(i,j,k);
                }
            }
        } 
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    // Bounding Box assimétrica. cada eixo usa seu próprio raio limitador.
    int minX = xcenter - rx;
    int maxX = xcenter + rx;
    int minY = ycenter - ry;
    int maxY = ycenter + ry;
    int minZ = zcenter - rz;
    int maxZ = zcenter + rz;

    for(int i=minX; i<=maxX; i++){
        for(int j=minY; j<=maxY; j++){
            for(int k=minZ; k<=maxZ; k++){
               // inequação do elipsoide. O (float) impede que a divisão entre inteiros trunque e destrua a curva.
               if((((i-xcenter)*(i-xcenter))/(float)(rx*rx)+((j-ycenter)*(j-ycenter))/(float)(ry*ry)+((k-zcenter)*(k-zcenter))/(float)(rz*rz))<= 1){
                    putVoxel(i,j,k);
                }
            }
        } 
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    // Mesma lógica de Bounding Box assimétrica e casting, mas para remoção.
    int minX = xcenter - rx;
    int maxX = xcenter + rx;
    int minY = ycenter - ry;
    int maxY = ycenter + ry;
    int minZ = zcenter - rz;
    int maxZ = zcenter + rz;

    for(int i=minX; i<=maxX; i++){
        for(int j=minY; j<=maxY; j++){
            for(int k=minZ; k<=maxZ; k++){
               if((((i-xcenter)*(i-xcenter))/(float)(rx*rx)+((j-ycenter)*(j-ycenter))/(float)(ry*ry)+((k-zcenter)*(k-zcenter))/(float)(rz*rz))<= 1){
                    cutVoxel(i,j,k);
                }
            }
        } 
    }
}

void Sculptor::writeOFF(const char* filename){
    //varrer a matriz inteira contando apenas quem está visível.
    int quantidade_ativos = 0;
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].show == true){
                    quantidade_ativos++;
                }
            }
        }
    }
    // cada cubo tem exatos 8 vértices e 6 faces.
    int quantidade_vertices_ativos = quantidade_ativos * 8;
    int quantidade_faces_ativos = quantidade_ativos * 6;

    std::ofstream file(filename);
    
    // força o C++ a sempre imprimir um decimal. para o MeshLab entender que as cores estão entre 0.0 e 1.0.
    file << std::fixed << std::setprecision(1);//representação do sofrimento 
    
    // cabeçalho obrigatório do formato .OFF
    file << "OFF" << std::endl;
    file << quantidade_vertices_ativos << " " << quantidade_faces_ativos << " 0" << std::endl;

    // escrever no arquivo as coordenadas (X, Y, Z) dos 8 vértices para cada voxel ativo.
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].show == true){
                    file << i-0.5 << " " << j+0.5 << " " << k-0.5 << std::endl;
                    file << i-0.5 << " " << j-0.5 << " " << k-0.5 << std::endl;
                    file << i+0.5 << " " << j-0.5 << " " << k-0.5 << std::endl;
                    file << i+0.5 << " " << j+0.5 << " " << k-0.5 << std::endl;

                    file << i-0.5 << " " << j+0.5 << " " << k+0.5 << std::endl;
                    file << i-0.5 << " " << j-0.5 << " " << k+0.5 << std::endl;
                    file << i+0.5 << " " << j-0.5 << " " << k+0.5 << std::endl;
                    file << i+0.5 << " " << j+0.5 << " " << k+0.5 << std::endl;
                }
            }
        }
    }
    
    //mapear como os vértices se ligam para formar as 6 faces.
    int indice = 0;
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].show == true){
                    // 4 (vértices por face)  |  índices dos vértices em anti-horário | Cores RGBA
                    file << 4 << " " << indice+0 << " " << indice+3 << " " << indice+2 << " " << indice+1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+4 << " " << indice+5 << " " << indice+6 << " " << indice+7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+3 << " " << indice+7 << " " << indice+6 << " " << indice+2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+1 << " " << indice+2 << " " << indice+6 << " " << indice+5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+0 << " " << indice+4 << " " << indice+7 << " " << indice+3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+0 << " " << indice+1 << " " << indice+5 << " " << indice+4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    
                    // salto os 8 vértices para mapear o próximo bloco de forma isolada.
                    indice += 8;
                }
            }
        }
    }
    file.close();
}