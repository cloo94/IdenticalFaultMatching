/*
Compile with:
g++ 1-bit_testFor.cpp  -I"/home/doug/Programs/libLCS-0.0.59/" -L"/home/doug/Programs/libLCS-0.0.59/lib" -l LCS
*/

#include <lcs/lcs.h>
#include <vector>
#include <map>

using namespace lcs;

void orGate(Bus<1> &out, Bus<1> in1, Bus<1> in2)
{
  out.cass<0>(in1 | in2);
}

int main()
{
  //Bus<1> a,b,c,d,e,f;
  //Bus<1> ins[4] = {b,c,e,f};
  //Bus<1> orGates[2];
  Bus<1> buses[6];
  /*for (int i=0; i<2; ++i){
    Or<2> x(a,(ins[i],ins[i+1]));
    std::cout << &x << '\n';
    orGates[i] = a;
  }*/
  /*
  buses[0].cass<0>(buses[1] | buses[2]);  //Or<2> ors[2] = {a,a};
  buses[3].cass<0>(buses[4] | buses[5]);
  */



  for (int i=0; i<6; i += 3){
    orGate(buses[i],buses[i+1],buses[i+2]);
  }

  ChangeMonitor<4> inputMonitor((buses[1],buses[2],buses[4],buses[5]), "Input", DUMP_OFF);

  ChangeMonitor<2> outputMonitor((buses[0],buses[3]),"Output", DUMP_OFF);

  Tester<4> tester((buses[1],buses[2],buses[4],buses[5])); //Template parameter 2 indicates the bus width of our input

  Simulation::setStopTime(1000);
  Simulation::start();
}
