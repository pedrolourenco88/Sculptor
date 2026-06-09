#include "cutellipsoid.h"

CutEllipsoid::CutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    // guardo as propriedades de assimetria
    this->xcenter = xcenter;
    this->ycenter = ycenter;
    this->zcenter = zcenter;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
}

void CutEllipsoid::draw(Sculptor &t){
    // mando o motor apagar os blocos que satisfazem a equação do elipsoide.
    t.cutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz);
}