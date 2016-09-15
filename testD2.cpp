#include <lcs/lcs.h>
#include <vector>
#include <map>
using namespace lcs;

typedef std::map<int,Bus<1> >BusMap;

struct gate1in {
  int id;
  int dep1;
};
struct gate2in {
  int id;
  int dep1;
  int dep2;
};

int main()
{
  const int numInputs = 3;
  const int numOutputs = 0;
  const int numBuffs = 0;
  const int numNots = 0;
  const int numAnds = 2;
  const int numOrs = 1;
  const int numNAnds = 0;
  const int numNOrs = 0;
  const int numXOrs = 0;
  const int numNXOrs = 0;
  const int numDFFs = 0;

  //Every gate and input/output needs a bus associated with it
  const int numBus = numInputs + numOutputs + numBuffs + numNots + numAnds
  + numOrs + numNAnds + numNOrs + numXOrs + numNXOrs + numDFFs;

  int Inputs[numInputs]= {10001,10002,10003};
  int Outputs[numOutputs] = {};
  gate1in Buffs[numBuffs] = {};
  gate1in Nots[numNots] = {};
  gate2in Ands[numAnds] = {{20001, 10001, 10002},{20002,10001,10002}};
  gate2in Ors [numOrs]= {{50001,20001,20002}};
  gate2in NAnds[numNAnds] = {};
  gate2in NOrs[numNOrs] = {};
  gate2in XOrs[numXOrs] = {};
  gate2in NXOrs[numNXOrs] = {};
  gate2in DFFs[numDFFs] = {};

  BusMap buses;
  //We will add each type of gate to the buses and its own respective array
  for (int i=0; i < numInputs; ++i){
    Bus<1> x;
    buses[Inputs[i]] =x;
  }
  for (int i=0; i < numOutputs; ++i){
    Bus<1> x;
    buses[Outputs[i]] =x;
  }
  for (int i=0; i < numBuffs; ++i){
    Bus<1> x;
    buses[Buffs[i].id] =x;
  }
  for (int i=0; i < numNots; ++i){
    Bus<1> x;
    buses[Nots[i].id] =x;
  }
  for (int i=0; i < numAnds; ++i){
    Bus<1> x;
    buses[Ands[i].id] =x;
  }
  for (int i=0; i < numOrs; ++i){
    Bus<1> x;
    buses[Ors[i].id] =x;
  }
  for (int i=0; i < numNAnds; ++i){
    Bus<1> x;
    buses[NAnds[i].id] =x;
  }
  for (int i=0; i < numNOrs; ++i){
    Bus<1> x;
    buses[NOrs[i].id] =x;
  }
  for (int i=0; i < numXOrs; ++i){
    Bus<1> x;
    buses[XOrs[i].id] =x;
  }
  for (int i=0; i < numNXOrs; ++i){
    Bus<1> x;
    buses[NXOrs[i].id] =x;
  }
  for (int i=0; i < numDFFs; ++i){
    //dffs[DFFs[i]] = <1>;
    Bus<1> x;
    buses[DFFs[i].id] =x;
  }
}
