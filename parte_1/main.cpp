#include "sculptor.h"
int main(){
  
  Sculptor trono(10,10,10);
    trono.setColor(1.0,0.0,0.0,0.5); 
    trono.putBox(0,9,0,9,0,9);
    trono.cutBox(1,8,1,9,1,9);
    trono.writeOFF("tronoverde.off");

  Sculptor sol(50,50,50);
    sol.setColor(1.0,1.0,0.0,1.0);
    sol.putSphere(25,25,25,21);
    sol.cutSphere(25,25,25,18);
    sol.cutBox(0,49,29,49,0,49);
    sol.cutBox(0,49,0,21,0,49);
    sol.writeOFF("anel.off");
  return 0;
}
