#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Sculptor::Sculptor(int _nx, int _ny, int _nz){//construtor
    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;

    this->r = 0.0;
    this->g = 0.0;
    this->b = 0.0;
    this->a = 0.0;

    v = new Voxel**[_nx];
    for(int i=0; i<_nx; i++){
        v[i] = new Voxel*[_ny];
        for(int j=0; j<_ny; j++){
            v[i][j] = new Voxel[_nz];
            for(int k=0; k<_nz; k++){
                v[i][j][k].r = 0.0;
                v[i][j][k].g = 0.0;
                v[i][j][k].b = 0.0;
                v[i][j][k].a = 0.0; 
                v[i][j][k].show = false;   
            }
        }
    }
}

Sculptor::~Sculptor(){//destrutor
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
           delete[] v[i][j];  
        }
        delete[] v[i];
    }
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float a){
    this-> r = r;
    this-> g = g;
    this-> b = b;
    this-> a = a;
}

void Sculptor::putVoxel(int x, int y, int z){ 
    if((x>=0 && x<nx) && (y>=0 && y<ny) && (z>=0 && z<nz)){ 
        v[x][y][z].show = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z){
    if((x>=0 && x<nx) && (y>=0 && y<ny) && (z>=0 && z<nz)) 
        v[x][y][z].show = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    // iterar apeans dentro da caiza que delimita a esfera
    float minX = xcenter - radius;
    float maxX = xcenter + radius;
    float minY = ycenter - radius;
    float maxY = ycenter + radius;
    float minZ = zcenter - radius;
    float maxZ = zcenter + radius;

    if((((x-xcenter)*(x-xcenter))+((y-ycenter)*(y-ycenter))+((z-zcenter)*(z-zcenter)))<=(radius*radius)){
        
    }






}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
  
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
  
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
  
}

void Sculptor::writeOFF(const char* filename){
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
    int quantidade_vertices_ativos = quantidade_ativos * 8;
    int quantidade_faces_ativos = quantidade_ativos * 6;

    std::ofstream file(filename);
    file << std::fixed << std::setprecision(1);
    file << "OFF" << std::endl;
    file << quantidade_vertices_ativos << " " << quantidade_faces_ativos << " 0" << std::endl;

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
    int indice = 0;
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].show == true){
                    file << 4 << " " << indice+0 << " " << indice+3 << " " << indice+2 << " " << indice+1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+4 << " " << indice+5 << " " << indice+6 << " " << indice+7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+3 << " " << indice+7 << " " << indice+6 << " " << indice+2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+1 << " " << indice+2 << " " << indice+6 << " " << indice+5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+0 << " " << indice+4 << " " << indice+7 << " " << indice+3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    file << 4 << " " << indice+0 << " " << indice+1 << " " << indice+5 << " " << indice+4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    indice += 8;
                }
            }
        }
    }
    file.close();
}
