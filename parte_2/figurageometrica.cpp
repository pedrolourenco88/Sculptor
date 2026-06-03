# include "figurageometrica.h"

// ==========================================
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

// ==========================================
PutBox::PutBox(int x0, int x1, int y0, int y1, int z0, int z1, float r, float g, float b, float a) {
    // guardo os limites de repetição da caixa (exclusivos dela)
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->z0 = z0;
    this->z1 = z1;
    
    // guardo as cores (que herdei da classe mãe FiguraGeometrica)
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void PutBox::draw(Sculptor &t) {
    // atualizo a cor do motor e passo os limites pra ele montar a caixa.
    t.setColor(r, g, b, a);
    t.putBox(x0, x1, y0, y1, z0, z1);
}

CutBox::CutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    // guardo apenas o volume espacial que vai ser removido.
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->z0 = z0;
    this->z1 = z1;
}

void CutBox::draw(Sculptor &t){
    // mando o motor varrer esses limites dando "show = false".
    t.cutBox(x0, x1, y0, y1, z0, z1);
}

// ==========================================
PutSphere::PutSphere(int xcenter, int ycenter, int zcenter, int radius, float r, float g, float b, float a){
    // guardo o centro, o tamanho (raio) e a cor.
    this->xcenter = xcenter;
    this->ycenter = ycenter;
    this->zcenter = zcenter;
    this->radius = radius;

    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void PutSphere::draw(Sculptor &t){
    // repasso pro motor fazer a matemática da Bounding Box e desenhar.
    t.setColor(r,g,b,a);
    t.putSphere(xcenter, ycenter, zcenter, radius);
}

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

// ==========================================
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