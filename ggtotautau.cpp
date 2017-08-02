
#include "ggtotautau.h"

ggtotautau::ggtotautau(): twototwommt(2,1, mtau, mtau), N(4){ 
  name = copy(" gamma gamma -> l+l- ");
  DVector w(1,4);
  w.fill(4, 0.0, 1.0, 0.0, 1.0);
  N.fill(w);
  n++;       /* add an integration variable for the noodle   */
  casesUsed = 2.0;
  ID1 = 15;   /* for definiteness */
  ID2 = -15; 
}

ggtotautau::ggtotautau(double thetamin): 
              twototwommt(2,1,mtau,mtau,thetamin), N(4){ 
  name = copy(" gamma gamma -> tau+tau- ");
  DVector w(1,4);
  w.fill(4, 0.0, 1.0, 0.0, 1.0);
  N.fill(w);
  n++;       /* add an integration variable for the noodle   */
  casesUsed = 2.0;
  ID1 = 15;   /* for definiteness */
  ID2 = -15; 
}

      
void ggtotautau::produceOnly(int Only){
  DVector w(1,4);
  switch (Only){
     case allStates:
         w.fill(4, 1.0, 1.0, 1.0, 1.0);
         casesUsed = 4.0;
         break;
     case muOnly :
         w.fill(4, 1.0, 0.0, 1.0, 0.0);
         casesUsed = 2.0;
         break;
     case tauOnly :
         w.fill(4, 0.0, 1.0, 0.0, 1.0);
         casesUsed = 2.0;
         break;
     default:
         therror("  This case of Only is not defined for e+e- -> l+l-.  ");
  }
  N.fill(w);
}

void ggtotautau::readcode(double y){
  int i = N.choose(y);
  switch(i){
    case 1:
     ID1 = 13; ID2 = -13; isLeft = 1;
     break;
    case 2:
     ID1 = 15; ID2 = -15; isLeft = 1;
     break;
    case 3:
     ID1 = 13; ID2 = -13; isLeft = 0;
     break;
    case 4:
     ID1 = 15; ID2 = -15; isLeft = 0;
    break;
   }
}

int ggtotautau::computeKinematics(double & J, DVector & X, double S, 
                                                               double beta){
  int valid = twototwommt::computeKinematics(J,X,S,beta);
  if (valid == 0) return 0;
  readcode(X[2]);
  J *= casesUsed; 
  return 1;
}

double ggtotautau::prefactor(){
  const double pref = PI * alpha * alpha * fb/2.0;
  double C = pref/s;
  return C;
}

void ggtotautau::amplitudes(){
  if (isLeft == 1){
       Camps[1][1] = 2.0 * sint/(1.0 - cost);
       Camps[2][1] = 2.0 * sint/(1.0 + cost);
   } else {
       Camps[1][1] = 2.0 * sint/(1.0 + cost);
       Camps[2][1] = 2.0 * sint/(1.0 - cost);
   }
}

void ggtotautau::crosssection(){
   cs.zero();
   amplitudes();
   double pref = prefactor();
   cs[-1][1] =  pref * norm(Camps[1][1]);
   cs[1][-1] =  pref * norm(Camps[2][1]);
}

double ggtotautau::dsigmadcost(double Cost, double S){
   s = S;
   cost = Cost;
   sint = sqrt(1.0 - cost*cost);
   isLeft = 1;
   double cross = simplecrosssection(); 
   isLeft = 0;
   cross += simplecrosssection();
   return cross *2.0;  /*  two lepton flavors  */
}

LEvent ggtotautau::buildEvent(){
   LEvent LE = twototwommt::buildEvent();
   if (ID1 == 15){
     if (isLeft == 1){
         LE.setchain(1,taumL);
         LE.setchain(2,taupR);
     } else {
         LE.setchain(1,taumR);
         LE.setchain(2,taupL);
     }
   }
   return LE;
}

