#include "cutvoxel.h"

CutVoxel::CutVoxel(int x, int y, int z){
    // corte não tem cor. guardo só a coordenada que quero apagar.
    this->x = x;
    this->y = y;
    this->z = z;
}

void CutVoxel::draw(Sculptor &t){
    // mando o motor desligar o bloco nesta posição.
    t.cutVoxel(x, y, z);
}