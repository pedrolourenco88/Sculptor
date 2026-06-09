#include"putellipsoid.h"

PutEllipsoid::PutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz, float r, float g, float b, float a){
    // guardo o centro e os 3 raios individuais (pra poder achatar/esticar) mais a cor.
    this->xcenter = xcenter;
    this->ycenter = ycenter;
    this->zcenter = zcenter;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;

    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void PutEllipsoid::draw(Sculptor &t){
    //delega pro motor aplicar a cor e gerar a curva assimétrica.
    t.setColor(r,g,b,a);
    t.putEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
}