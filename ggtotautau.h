
#ifndef GGTOTAUTAU_H
#define GGTOTAUTAU_H

#include "pandora.h"
#include "processes.h"


class ggtotautau: public twototwommt{

  /*  integration variables:
            cos theta =  tanh( (2 Y[1]-1) * 10)   
        to give the cross section in the CM up to 10^-5 rad   
            Y[2] gives the species:  
    (0,0.25)-> mu_L, (0.25,0.5)-> tau_L, (0.5,0.75)-> mu_R, (0.75,1.0)->tau_R

	    */      
 public:
 
  ggtotautau();
  ggtotautau(double thetamin);
 
  /*  uses constructors and validEvent inherited from twototwozzt  */

  int computeKinematics(double & J, DVector & X, double s, double beta);
  void crosssection();
  LEvent buildEvent();

  void produceOnly(int Only);
    /*   call with muOnly or tauOnly to get a unique lepton   */

  double dsigmadcost(double cost, double s);
     /* returns the unpolarized differential cross section as a 
	  function of cos theta     */

protected:

  noodle N;
  double casesUsed;
  int ID, isLeft;
  void readcode(double y);
     /*  fills the particle code and the handedness
	                 associated with a value of Y[2]  */
  double prefactor();
  void amplitudes();
      /*  for Camps[i][j]  
        i = 1:  gLgR     2: gRgL
        j = 1 refers to the unique final helicity state */

};
#endif      /*   GGTOTAUTAU_H     */
