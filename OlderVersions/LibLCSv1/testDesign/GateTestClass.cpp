// g++ GateTestClass.cpp -I"libLCS/" -L"libLCS/lib" -l LCS

#include <string>
#include <lcs/lcs.h>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace lcs;


class Gate; //Forward Declaration of Gates
typedef std::map<int,Gate >BusMap; // Map for gates
BusMap Gates; //the dictionary that will store all the gates under their  values

//insepcts an int vector to determine if a new element already exists there, if not, the element is added
void addUnique(std::vector<int> &total, int val) {
  bool isPresent;
  //Searches the length of the vector for an item
  for (int i=0; i < total.size(); ++i){
    if (total[i] == val){
      isPresent = true;
    }
  }
  //If item exists, do nothing, else add it
  if (~isPresent) {
    total.push_back(val);
  }
}

class Gate {
  public:
    int id; // number of the gate
    int dep1;
    int dep2;
    Bus<1> out; //The actual value, stored as a bus
    std::vector<int> children;  //Where all of the arrays that are dependant on this are stored

    std::vector<int> addChild(int newChild) {
      //children.resize(children.size()+1); could also resize this
      children.push_back(newChild);
    }
    //Defines  functions for recursive searching
    //Goes through each child item in an object, looks up those gates by id, and then displays their children
    std::vector<int> return_children(std::vector<int> children, std::vector<int> &total) {
      for (int i=0; i < children.size(); ++i) {
        std::cout << "Finding Child" << std::endl;
        Gate newGate = Gates[children[i]];
        std::vector<int> newChildren = newGate.children;
        //Add children elements to toal one at a time
        //TODO, check for overlap in dependencies, eliminate if you can (speed runtime)
        for (int j=0; j < children.size(); ++j) {
          total.push_back(newChildren[j]);
        }
        newGate.return_children(newChildren,total);
      }
    }

    //Defines functions for producing gate truth values
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
    //TODO Define DFF gate
};
//Definition of the formatted inputs from the parser to the Gate class
struct gate1in {
  int id;
  int dep1;
};
struct gate2in {
  int id;
  int dep1;
  int dep2;
};


int main (int argc, char * argv[]) {

  char line[100];
  char *line2;
  char *data;
  FILE *fp;
  FILE *fp2;
  char *design_file = argv[1];
  char *fault_file = argv[2];
  int totalinputs = 0;
  int totaloutputs = 0;
  int totalflipflops = 0;
  int totalbuffs = 0;
  int totalnots = 0;
  int totalands = 0;
  int totalnands = 0;
  int totalors = 0;
  int totalnors = 0;
  int totalxors = 0;
  int totalnxors = 0;

  if (argc != 3) {
    printf("Error: Please input a gate design file and fault description file\n");
    exit(1);
  }

  if (!(fp = fopen(design_file,"r"))) {
    perror("Error opening file");
    exit(1);
  }

  if (!(fp2 = fopen(fault_file,"r"))) {
    perror("Error opening file");
    exit(1);
  }

  while (fgets(line, sizeof(line), fp) != NULL) {

    line2 = line;

    if (strstr(line, " input") != NULL) {
      data = strsep(&line2," inputs");
      data = strsep(&line2,"# ");
      totalinputs = atoi(data);
      //printf("input count: %d\n",totalinputs);
    }

    if (strstr(line, " output") != NULL) {
      data = strsep(&line2," outputs");
      data = strsep(&line2,"# ");
      totaloutputs = atoi(data);
      //printf("output count: %d\n",totaloutputs);
    }

    if (strstr(line, " flip-flop") != NULL) {
      data = strsep(&line2," D-type");
      data = strsep(&line2,"# ");
      totalflipflops = atoi(data);
      //printf("flip flop count: %d\n",totalflipflops);
    }

    if (strstr(line, " gates") != NULL) {
      data = strsep(&line2,"(");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalbuffs = atoi(data);
      //printf("buff count: %d\n",totalbuffs);

      data = strsep(&line2, "+");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalnots = atoi(data);
      //printf("not count: %d\n",totalnots);

      data = strsep(&line2, "+");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalands = atoi(data);
      //printf("and count: %d\n",totalands);

      data = strsep(&line2, "+");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalnands = atoi(data);
      //printf("nand count: %d\n",totalnands);

      data = strsep(&line2, "+");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalors = atoi(data);
      //printf("or count: %d\n",totalors);

      data = strsep(&line2, "+");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalnors = atoi(data);
      //printf("nor count: %d\n",totalnors);

      data = strsep(&line2, "+");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalxors = atoi(data);
      //printf("xor count: %d\n",totalxors);

      data = strsep(&line2, "+");
      data = strsep(&line2," ");
      data = strsep(&line2," ");
      totalnxors = atoi(data);
      //printf("nxor count: %d\n",totalnxors);

    }
  }

  const int numInputs = totalinputs;
  const int numOutputs = totaloutputs;
  const int numBuffs = totalbuffs;
  const int numNots = totalnots;
  const int numAnds = totalands;
  const int numOrs = totalors;
  const int numNAnds = totalnands;
  const int numNOrs = totalnors;
  const int numXOrs = totalxors;
  const int numNXOrs = totalnxors;
  const int numDFFs = totalflipflops;
  
  rewind(fp);

  int Inputs[numInputs];
  int Outputs[numOutputs];
  gate1in Buffs[numBuffs];
  gate1in Nots[numNots];
  gate2in Ands[numAnds];
  gate2in Ors [numOrs];
  gate2in NAnds[numNAnds];
  gate2in NOrs[numNOrs];
  gate2in XOrs[numXOrs];
  gate2in NXOrs[numNXOrs];
  gate2in DFFs[numDFFs];

  int input_counter = 0;
  int output_counter = 0;
  int flipflop_counter = 0;
  int buff_counter = 0;
  int not_counter = 0;
  int and_counter = 0;
  int nand_counter = 0;
  int or_counter = 0;
  int nor_counter = 0;
  int xor_counter = 0;
  int nxor_counter = 0;
  
  while (fgets(line, sizeof(line), fp) != NULL) {

    line2 = line;

    if (strstr(line, "INPUT(") != NULL) {
      data = strsep(&line2,"(");
      data = strsep(&line2,")");
      Inputs[input_counter] = atoi(data);
      input_counter++;
    }

    else if (strstr(line, "OUTPUT(") != NULL) {
      data = strsep(&line2,"(");
      data = strsep(&line2,")");
      Outputs[output_counter] = atoi(data);
      output_counter++;
    }

    else if (strstr(line, "= DFF") != NULL) {
      data = strsep(&line2, " ");
      
      //      DFFs[flipflop_counter].id = atoi(data);
      //      flipflop_array[flipflop_counter][4] = atoi(data);
      
      data = strsep(&line2, "(");
      data = strsep(&line2, ",");
      //DFFS[flipflop_counter]. = atoi(data);
      //flipflop_array[flipflop_counter][1] = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ",");
      //DFFS[flipflop_counter]. = atoi(data);
      //flipflop_array[flipflop_counter][2] = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ",");
      //DFFS[flipflop_counter]. = atoi(data);
      //flipflop_array[flipflop_counter][3] = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ")");
      //DFFS[flipflop_counter]. = atoi(data);
      //flipflop_array[flipflop_counter][0] = atoi(data);
      flipflop_counter++;
    }

    else if (strstr(line, "= BUFF") != NULL) {
      data = strsep(&line2," ");
      Buffs[buff_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ")");
      Buffs[buff_counter].dep1 = atoi(data);
      buff_counter++;
    }

    else if (strstr(line, "= NOT") != NULL) {
      data = strsep(&line2," ");
      Nots[not_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ")");
      Nots[not_counter].dep1 = atoi(data);
      not_counter++;
    }

    else if (strstr(line, "= AND") != NULL) {
      data = strsep(&line2," ");
      Ands[and_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ", ");
      Ands[and_counter].dep1 = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ")");
      Ands[and_counter].dep2 = atoi(data);
      and_counter++;
    }

    else if (strstr(line, "= NAND") != NULL) {
      data = strsep(&line2," ");
      NAnds[nand_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ", ");
      NAnds[nand_counter].dep1 = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ")");
      NAnds[nand_counter].dep2 = atoi(data);
      nand_counter++;
    }

    else if (strstr(line, "= OR") != NULL) {
      data = strsep(&line2," ");
      Ors[or_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ", ");
      Ors[or_counter].dep1 = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ")");
      Ors[or_counter].dep2 = atoi(data);
      or_counter++;
    }

    else if (strstr(line, "= NOR") != NULL) {
      data = strsep(&line2," ");
      NOrs[nor_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ", ");
      NOrs[nor_counter].dep1 = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ")");
      NOrs[nor_counter].dep2 = atoi(data);
      nor_counter++;
    }

    else if (strstr(line, "= XOR") != NULL) {
      data = strsep(&line2," ");
      XOrs[xor_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ", ");
      XOrs[xor_counter].dep1 = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ")");
      XOrs[xor_counter].dep2 = atoi(data);
      xor_counter++;
    }

    else if (strstr(line, "= NXOR") != NULL) {
      data = strsep(&line2," ");
      NXOrs[nxor_counter].id = atoi(data);
      data = strsep(&line2, "(");
      data = strsep(&line2, ", ");
      NXOrs[nxor_counter].dep1 = atoi(data);
      data = strsep(&line2, " ");
      data = strsep(&line2, ")");
      NXOrs[nxor_counter].dep2 = atoi(data);
      nxor_counter++;
    }

    else {

    }

  }

  int totalfaults = 0;
  int fault_counter = 0;
  char c;

  for (c = getc(fp2); c != EOF; c = getc(fp2)) {
    if (c == '\n') {
      totalfaults++;
    }
  }
  rewind(fp2);

  char *fault_array[totalfaults][3];
  char *fault_array2[totalfaults][3];

  while (fgets(line, sizeof(line), fp2) != NULL) {

    line2 = line;
    data = strtok(line2,"\t");
    fault_array2[fault_counter][0] = data;
    data = strtok(NULL,"\t");
    fault_array2[fault_counter][1] = data;
    data = strtok(NULL,"\t");
    fault_array2[fault_counter][2] = data;

    if (strstr(data, "SA0") != NULL) {
      fault_array[fault_counter][2] = (char*)"SA0";
    } else if (strstr(data, "SA1") != NULL) {
      fault_array[fault_counter][2] = (char*)"SA1";
    } else if (strstr(data, "NEG") != NULL) {
      fault_array[fault_counter][2] = (char*)"NEG";
    } else if (strstr(data, "RDOB_AND") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_AND";
    } else if (strstr(data, "RDOB_NAND") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_NAND";
    } else if (strstr(data, "RDOB_OR") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_OR";
    } else if (strstr(data, "RDOB_NOR") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_NOR";
    } else if (strstr(data, "RDOB_XOR") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_XOR";
    } else if (strstr(data, "RDOB_NXOR") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_NXOR";
    } else if (strstr(data, "RDOB_NOT") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_NOT";
    } else if (strstr(data, "RDOB_BUFF") != NULL) {
      fault_array[fault_counter][2] = (char*)"RDOB_BUFF";
    } else {
    }

    fault_array[fault_counter][0] = (char *)malloc(sizeof(char) * strlen(fault_array2[fault_counter][0]));
    strncpy(fault_array[fault_counter][0],fault_array2[fault_counter][0],strlen(fault_array2[fault_counter][0]));

    fault_array[fault_counter][1] = (char *)malloc(sizeof(char) * strlen(fault_array2[fault_counter][1]));
    strncpy(fault_array[fault_counter][1],fault_array2[fault_counter][1],strlen(fault_array2[fault_counter][1]));

    fault_counter++;

  }

  /* Prints out the parsed information */

  printf("\nList of INPUT PORTS:\n");
  for (int i = 0; i<input_counter; i++) {
    printf("%d\n",Inputs[i]);
  }

  printf("\nList of OUTPUT PORTS:\n");
  for (int i = 0; i<output_counter; i++) {
    printf("%d\n",Outputs[i]);
  }

  /*
  printf("\nList of DFFS:\n");
  for (int i = 0; i<flipflop_counter; i++) {
    printf("Input Signal:    %d    ",flipflop_array[i][0]);
    printf("    Clock Signal:    %d    ",flipflop_array[i][1]);
    printf("    Reset Signal:    %d    ",flipflop_array[i][2]);
    printf("    Enable Signal:    %d    ",flipflop_array[i][3]);
    printf("    Output Signal:    %d\n",flipflop_array[i][4]);
  }
  */

  printf("\nList of BUFFS:\n");
  for (int i = 0; i<buff_counter; i++) {
    printf("ID:    %d    ",Buffs[i].id);
    printf("    Dep1:    %d\n",Buffs[i].dep1);
  }

  printf("\nList of NOTS:\n");
  for (int i = 0; i<not_counter; i++) {
    printf("ID:    %d    ",Nots[i].id);
    printf("    Dep1:    %d\n",Nots[i].dep1);
  }

  printf("\nList of ANDS:\n");
  for (int i = 0; i<and_counter; i++) {
    printf("ID:    %d    ",Ands[i].id);
    printf("    Dep1:    %d    ",Ands[i].dep1);
    printf("    Dep2:    %d\n",Ands[i].dep2);
  }

  printf("\nList of NANDS:\n");
  for (int i = 0; i<nand_counter; i++) {
    printf("ID:    %d    ",NAnds[i].id);
    printf("    Dep1:    %d    ",NAnds[i].dep1);
    printf("    Dep2:    %d\n",NAnds[i].dep2);
  }

  printf("\nList of ORS:\n");
  for (int i = 0; i<or_counter; i++) {
    printf("ID:    %d    ",Ors[i].id);
    printf("    Dep1:    %d    ",Ors[i].dep1);
    printf("    Dep2:    %d\n",Ors[i].dep2);
  }

  printf("\nList of NORS:\n");
  for (int i = 0; i<nor_counter; i++) {
    printf("ID:    %d    ",NOrs[i].id);
    printf("    Dep1:    %d    ",NOrs[i].dep1);
    printf("    Dep2:    %d\n",NOrs[i].dep2);
  }

  printf("\nList of XORS:\n");
  for (int i = 0; i<xor_counter; i++) {
    printf("ID:    %d    ",XOrs[i].id);
    printf("    Dep1:    %d    ",XOrs[i].dep1);
    printf("    Dep2:    %d\n",XOrs[i].dep2);
  }

  printf("\nList of NXORS:\n");
  for (int i = 0; i<nxor_counter; i++) {
    printf("ID:    %d    ",NXOrs[i].id);
    printf("    Dep1:    %d    ",NXOrs[i].dep1);
    printf("    Dep2:    %d\n",NXOrs[i].dep2);
  }

  printf("\nList of Faults:\n");
  for (int i = 0; i<fault_counter; i++) {
    printf("Fault Identifier:    %s    ",fault_array[i][0]);
    printf("Signal Injected:    %s    ",fault_array[i][1]);
    printf("Fault Type:    %s\n",fault_array[i][2]);
  }

  printf("Total fault count: %d\n",fault_counter);
  printf("Unofficial fault count: %d\n",totalfaults);

  fclose(fp);
  fclose(fp2);


  //We will add each type of gate to the buses and its own respective array
  //also adds and defines gate values
  for (int i=0; i < numInputs; ++i){
    Gate x;
    Gates[Inputs[i]] =x;
  }

  for (int i=0; i < numOutputs; ++i){
    Gate x;
    Gates[Outputs[i]] =x;
  }
 
  //Add all buffs to Gates
  for (int i=0; i < numBuffs; ++i){
    //Defines the gate
    Gate x;
    //Sets the gat in the ID defined (from the parser)
    Gates[Buffs[i].id] =x;
    //sets the out value
    Gates[Buffs[i].id].bufGate(Gates[Buffs[i].id].out,Gates[Buffs[i].dep1].out);
    //Sets dependencies
    Gates[Buffs[i].id].dep1 = Buffs[i].dep1;
    //Assigns children
    Gates[Buffs[i].dep1].addChild(Buffs[i].id);
  }
  //Add nots to Gates
  for (int i=0; i < numNots; ++i){
    Bus<1> x;
    Gates[Nots[i].id].out =x;
    Gates[Nots[i].id].notGate(Gates[Nots[i].id].out,Gates[Nots[i].dep1].out);
    Gates[Nots[i].id].dep1 = Nots[i].dep1;
    Gates[Nots[i].dep1].addChild(Nots[i].id);
  }
  //Add ANDS to Gates
  for (int i=0; i < numAnds; ++i){
    Bus<1> x;
    Gates[Ands[i].id].out =x;
    Gates[Ands[i].id].andGate(Gates[Ands[i].id].out,Gates[Ands[i].dep1].out,Gates[Ands[i].dep2].out);
    Gates[Ands[i].id].dep1 = Ands[i].dep1;
    Gates[Ands[i].id].dep2 = Ands[i].dep2;
    Gates[Ands[i].dep1].addChild(Ands[i].id);
    Gates[Ands[i].dep2].addChild(Ands[i].id);
  }
  //Adds ORS to Gates
  for (int i=0; i < numOrs; ++i){
    Bus<1> x;
    Gates[Ors[i].id].out =x;
    Gates[Ors[i].id].orGate(Gates[Ors[i].id].out,Gates[Ors[i].dep1].out,Gates[Ors[i].dep2].out);
    Gates[Ors[i].id].dep1 = Ors[i].dep1;
    Gates[Ors[i].id].dep2 = Ors[i].dep2;
    Gates[Ors[i].dep1].addChild(Ors[i].id);
    Gates[Ors[i].dep2].addChild(Ors[i].id);
  }
  //Adds NANDS to Gates
  for (int i=0; i < numNAnds; ++i){
    Bus<1> x;
    Gates[NAnds[i].id].out =x;
    Gates[NAnds[i].id].nandGate(Gates[NAnds[i].id].out,Gates[NAnds[i].dep1].out,Gates[NAnds[i].dep2].out);
    Gates[NAnds[i].id].dep1 = NAnds[i].dep1;
    Gates[NAnds[i].id].dep2 = NAnds[i].dep2;
    Gates[NAnds[i].dep1].addChild(NAnds[i].id);
    Gates[NAnds[i].dep2].addChild(NAnds[i].id);
  }
  //Adds NORS to Gates
  for (int i=0; i < numNOrs; ++i){
    Bus<1> x;
    Gates[NOrs[i].id].out =x;
    Gates[NOrs[i].id].norGate(Gates[NOrs[i].id].out,Gates[NOrs[i].dep1].out,Gates[NOrs[i].dep2].out);
    Gates[NOrs[i].id].dep1 = NOrs[i].dep1;
    Gates[NOrs[i].id].dep2 = NOrs[i].dep2;
    Gates[NOrs[i].dep1].addChild(NOrs[i].id);
    Gates[NOrs[i].dep2].addChild(NOrs[i].id);
  }
  //Adds XORS to Gates
  for (int i=0; i < numXOrs; ++i){
    Bus<1> x;
    Gates[XOrs[i].id].out =x;
    Gates[XOrs[i].id].xorGate(Gates[XOrs[i].id].out,Gates[XOrs[i].dep1].out,Gates[XOrs[i].dep2].out);
    Gates[XOrs[i].id].dep1 = XOrs[i].dep1;
    Gates[XOrs[i].id].dep2 = XOrs[i].dep2;
    Gates[XOrs[i].dep1].addChild(XOrs[i].id);
    Gates[XOrs[i].dep2].addChild(XOrs[i].id);
  }
  // Adds NXORS to Gates
  for (int i=0; i < numNXOrs; ++i){
    Bus<1> x;
    Gates[NXOrs[i].id].out =x;
    Gates[NXOrs[i].id].nxorGate(Gates[NXOrs[i].id].out,Gates[NXOrs[i].dep1].out,Gates[NXOrs[i].dep2].out);
    Gates[NXOrs[i].id].dep1 = NXOrs[i].dep1;
    Gates[NXOrs[i].id].dep2 = NXOrs[i].dep2;
    Gates[NXOrs[i].dep1].addChild(NXOrs[i].id);
    Gates[NXOrs[i].dep2].addChild(NXOrs[i].id);
  }
  
  //Adds DFFs to Gates
  for (int i=0; i < numDFFs; ++i){
    //dffs[DFFs[i]] = <1>;
    Bus<1> x;
    Gates[DFFs[i].id].out =x;
    //TODO support for DFF gate
  }
  
  
  return 0;
}
