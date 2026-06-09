#include"cutsphere.h"

CutSphere::CutSphere(int xcenter, int ycenter, int zcenter, int radius){
    // Guardo só a geometria base da esfera pra remoção.
    this->xcenter = xcenter;
    this->ycenter = ycenter;
    this->zcenter = zcenter;
    this->radius = radius;
}

void CutSphere::draw(Sculptor &t){
    // mando o motor esculpir/remover usando a equação da esfera.
    t.cutSphere(xcenter,ycenter,zcenter,radius);
}
