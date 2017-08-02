
#ifndef EEMINUSTOPAIRS_H
#define EEMINUSTOPAIRS_H

#include "pandora.h"
#include "processes.h"

class eeminustollbar: public twototwommt{

  /*  integration variables:

            cos theta   = 2 X[1] - 1    in the CM
            X[2] gives the species:  
    (0,0.25)-> mu_L, (0.25,0.5)-> tau_L, (0.5,0.75)-> mu_R, (0.75,1.0)->tau_R

	    */      

 public:
 
  eeminustollbar();
  eeminustollbar(double thetamin);
 
 /* the second of these computes the cross section over
          ECM > ECMmin.  The default value is ECMmin = 2 GeV.
                                                           */
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
  int isLeft;
  void readcode(double y);
     /*  fills the particle code and the handedness
	                 associated with a value of Y[2]  */
  double prefactor();
  void amplitudes();
      /*  for Camps[i][j]  
        i = 1:  e-Le+R      2: e-Re+L
        j = 1 refers to the unique final helicity state */
};

#endif      /*   EEMINUSTOPAIRS_H     */
