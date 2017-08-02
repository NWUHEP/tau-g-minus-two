#include "pandora.h"
#include "ebeams.h"
#include "gnuplot.h"
#include "eeminustopairs.h"

/* print the 4-vector components */
void printLVector(LVector & lV) {
  for (int i = 1; i < 4; i++) {
    cout << " " << lV[i];
  }
  cout << " " << lV[0];
}

/*For printing out information in LHE format, can redirect code's output to lhef */ 
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

/*For generating events to test with */
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

       ebeam B1(ECM/2.0, -.8, electron, electron);
       ebeam B2(ECM/2.0, -.8, positron, positron);


         //Can turn off ISR         
//       B1.ISRoff(); 
//       B2.ISRoff();

       //theta min = 0.0
       eeminustollbar rxn5(0.0);

       pandora P(B1,B2,rxn5);

       P.quiet(); //turn of preparing print statements
       int Nprepare = 100000;

       P.prepare(Nprepare);

       pandorasBox box;
       box.add(P);

       //switching between printing lhe format and test event format
       generateEvents(box);
//       generateLHE(box, ECM);
       return 0;

}



