// g++ testDesign.cpp -I"libLCS/" -L"libLCS/lib" -l LCS

#include <string>
#include <lcs/lcs.h>
#include <vector>
#include <map>
using namespace lcs;

//Will map gate numbers to objects
typedef std::map<int,Bus<1> >BusMap;

//Defines BUFF gate
void bufGate(Bus<1> &out, Bus<1> in1)
{
  out.cass<0>(in1);
}
//Defines NOTGate
void notGate(Bus<1> &out, Bus<1> in1)
{
  out.cass<0>(~in1);
}
//Defines our OR gate
void orGate(Bus<1> &out, Bus<1> in1, Bus<1> in2)
{
  out.cass<0>(in1 | in2);
}
//Defines AND gate
void andGate(Bus<1> &out, Bus<1> in1, Bus<1> in2)
{
  out.cass<0>(in1 & in2);
}
//Defines NOR gate
void norGate(Bus<1> &out, Bus<1> in1, Bus<1> in2)
{
  out.cass<0>(~(in1 | in2));
}
//Defines NAND gate
void nandGate(Bus<1> &out, Bus<1> in1, Bus<1> in2)
{
  out.cass<0>(~(in1 & in2));
}
//Defines XOR gate
void xorGate(Bus<1> &out, Bus<1> in1, Bus<1> in2)
{
  out.cass<0>(in1 ^ in2);
}
//Defines NXOR gate
void nxorGate(Bus<1> &out, Bus<1> in1, Bus<1> in2)
{
  out.cass<0>(~(in1 ^ in2));
}
//Defines DFF gate




void



int main() {

  BusMap buses;

  Bus<1> inputs[numInputs];
  Bus<1> outputs[numOutputs];
  for (int i=0; i < numInputs; ++i){
    inputs[i] = buses[Inputs[i]];
  }
  for (int i=0; i < numOutputs; ++i){
    outputs[i] = buses[Outputs[i]];
  }

  //Assigns all of our gate to various values
  for (int i=0; i < numBuffs; ++i){
    bufGate(buses[Buffs[i].id],buses[Buffs[i].dep1]);
  }
  for (int i=0; i < numNots; ++i){
    notGate(buses[Nots[i].id],buses[Nots[i].dep1]);
    //nots[Nots[i].id] =x;
  }
  for (int i=0; i < numAnds; ++i){
    andGate(buses[Ands[i].id],buses[Ands[i].dep1],buses[Ands[i].dep2]);
  }
  for (int i=0; i < numOrs; ++i){
    orGate(buses[Ors[i].id],buses[Ors[i].dep1],buses[Ors[i].dep2]);
    //ors[Ors[i].id] =x;
  }
  for (int i=0; i < numNAnds; ++i){
    nandGate(buses[NAnds[i].id],buses[NAnds[i].dep1],buses[NAnds[i].dep2]);
    //nands[NAnds[i].id] =x;
  }
  for (int i=0; i < numNOrs; ++i){
    norGate(buses[NOrs[i].id],buses[NOrs[i].dep1],buses[NOrs[i].dep2]);
    //nors[NOrs[i].id] =x;
  }
  for (int i=0; i < numXOrs; ++i){
    xorGate(buses[XOrs[i].id],buses[XOrs[i].dep1],buses[XOrs[i].dep2]);
    //xors[XOrs[i].id] =x;
  }
  for (int i=0; i < numNXOrs; ++i){
    nxorGate(buses[NXOrs[i].id],buses[NXOrs[1].dep1],buses[NXOrs[2].dep2]);
    //buses[NXOrs[i].id] =x;
  }
  return 0;
}
