#include "pandora.h"
#include "ebeams.h"
#include "gnuplot.h"
#include "eeminustopairs.h"

void printLVector(LVector & lV) {
  for (int i = 1; i < 4; i++) {
    cout << " " << lV[i];
  }
  cout << " " << lV[0];
//  cout << lV;
}

        
void generateLHE(pandorasBox & box, double energy){


       cout << "<LesHouchesEvents version=\"1.0\">" << endl << "<init>" << endl;
       cout << " 11 -11 " << energy/2.0 << " " << energy/2.0 << " 0 0 -1 -1 3 1" << endl;
       cout << " 50 5 1 80" << endl << "</init>" << endl;
       int Nevents = 10000;
       int i;

       for ( i = 0; i < Nevents; i++) {
          cout << "<event>" << endl << " 4 80 1 -1 -1 -1" << endl;
          LEvent LE = box.getEvent();
          LEvent LInit = box.initialvectors();
          LVector t1 = LE.readout(1);
          LVector t2 = LE.readout(2);
          LVector g1 = LInit.readout(3);
          LVector g2 = LInit.readout(4);
//          cout << g1 << g2;
          cout << " 11 -1 0 0 0 0"; printLVector(g1);
          cout << " 0 0. 9." << endl;
          cout << " -11 -1 0 0 0 0"; printLVector(g2);
          cout << " 0 0. 9." << endl;
          cout << " " << ((LE.chain(1) < -12) ? -15:15) << " 1 1 2 0 0"; printLVector(t1);
          cout << " 1.7768 0. " << (-1 - 2*(LE.chain(1)%2)) << endl;
          cout << " " << ((LE.chain(2) < -12) ? -15:15) << " 1 1 2 0 0"; printLVector(t2);
          cout << " 1.7768 0. " << (-1 - 2*(LE.chain(2)%2)) << endl;
          cout << "</event>" << endl;
       }

       cout << "</LesHouchesEvents>";
}

void generateEvents(pandorasBox & box){


       int Nevents = 10;
       int i;

       for ( i = 0; i < Nevents; i++) {
          LEvent LE = box.getEvent();
          LEvent LInit = box.initialvectors();
          LVector t1 = LE.readout(1);
          LVector t2 = LE.readout(2);
          LVector g1 = LInit.readout(3);
          LVector g2 = LInit.readout(4);
          cout << LInit << endl << LE << endl << endl;
       }

}

int main(int argv, char* argc[]){

       double ECM = atof(argc[1]);

       //Energy of beam, electron beam polarization, laser polarization, initial particle(photon), final particle(photon/electron), and optionally the value of xzero (defaulted to xTelnov = 2 + sqrt(8)
//       simplepbeam B1(ECM/2.0, 0);
//       simplepbeam B2(ECM/2.0, 0);
       ebeam B1(ECM/2.0, -.8, electron, electron);
       ebeam B2(ECM/2.0, -.8, positron, positron);

       /*To get peak at enpoint, set ePolarization = - lPolarization
       for + helicity photons at high energy, take ePolarization > 0

       xzero = 4 E(beam) * w(laser) / m_e^2

       Electron treatment has ISR but not beamstrahlung
        */


         //Can turn off ISR and Compton effects(for delta function of photon energy)          
//       B1.ISRoff(); B1.Comptonoff();
//       B2.ISRoff(); B2.Comptonoff();

       //theta min
       eeminustollbar rxn5(0.0);

       pandora P(B1,B2,rxn5);
       //pandora P2(B1, B2, rxn6);
       //pandora P3(B1, B2, rxn7);

       P.quiet();
       int Nprepare = 100000;

       P.prepare(Nprepare);
       //P2.prepare(Nprepare);
       //P3.prepare(Nprepare);

       pandorasBox box;
       box.add(P); //box.add(P2); box.add(P3);


       generateEvents(box);
//       generateLHE(box, ECM);
       return 0;

}



