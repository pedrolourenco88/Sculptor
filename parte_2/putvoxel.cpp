#include"putvoxel.h"

PutVoxel::PutVoxel(int x, int y, int z,float r, float g, float b, float a){
    // guardo a posição exata e a cor dentro do objeto para usar depois.
    this->x = x;
    this->y = y;
    this->z = z;
    
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void PutVoxel::draw(Sculptor &t){
    //passo a minha cor pro motor e mando ele mostrar o bloco.
    t.setColor(r, g, b, a);
    t.putVoxel(x, y, z);
}