//TODO: Make sure all simulators are set to DUMP_OFF before submission, they create an additional output file
/*
compile with:
make command and included Makefile
g++ testDesign.cpp -I"libLCS/" -L"libLCS/lib" -l LCS
*/
// Usage: ./parser design_file fault_file
// fixed sizes of arrays - might be too small/large
// doesn't do anything with top 4 # lines of gate design file

#include <string>
#include <lcs/lcs.h>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace lcs;

//Will map gate numbers to objects
typedef std::map<int,Bus<1> >BusMap;
typedef std::map<int,Buffer<> >BuffMap;
typedef std::map<int,Not<> >NotMap;
typedef std::map<int,And<2> >AndMap;
typedef std::map<int,Or<2> >OrMap;
typedef std::map<int,Nand<2> >NAndMap;
typedef std::map<int,Nor<2> >NOrMap;
typedef std::map<int,Xor<2> >XOrMap;
//typedef std::map<int,NXOrs<1> >NXOrMap;
typedef std::map<int,DFlipFlop<> >DFFMap;

struct gate1in {
  int id;
  int dep1;
};

struct gate2in {
  int id;
  int dep1;
  int dep2;
};

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


int main (int argc, char * argv[]) {

    char line[100];
    char *line2;
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
    int fault_counter = 0;
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
	printf("Auto input count: %d\n",totalinputs);
      }

      if (strstr(line, " output") != NULL) {
	data = strsep(&line2," outputs");
	data = strsep(&line2,"# ");
	totaloutputs = atoi(data);
	printf("Auto output count: %d\n",totaloutputs);
      }

      if (strstr(line, " flip-flop") != NULL) {
	data = strsep(&line2," D-type");
	data = strsep(&line2,"# ");
	totalflipflops = atoi(data);
	printf("Auto flip flop count: %d\n",totalflipflops);
      }

      if (strstr(line, " gates") != NULL) {
	data = strsep(&line2,"(");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalbuffs = atoi(data);
	printf("Auto buff count: %d\n",totalbuffs);
	
	data = strsep(&line2, "+");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalnots = atoi(data);
	printf("Auto not count: %d\n",totalnots);

        data = strsep(&line2, "+");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalands = atoi(data);
	printf("Auto and count: %d\n",totalands);
	
        data = strsep(&line2, "+");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalnands = atoi(data);
	printf("Auto nand count: %d\n",totalnands);

        data = strsep(&line2, "+");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalors = atoi(data);
	printf("Auto or count: %d\n",totalors);
	
	data = strsep(&line2, "+");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalnors = atoi(data);
	printf("Auto nor count: %d\n",totalnors);
	
	data = strsep(&line2, "+");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalxors = atoi(data);
	printf("Auto xor count: %d\n",totalxors);
	
	data = strsep(&line2, "+");
	data = strsep(&line2," ");
	data = strsep(&line2," ");
	totalnxors = atoi(data);
	printf("Auto xor count: %d\n",totalnxors);

      }
    }

    int input_array[totalinputs];           // data to be passed to algorithm
    int output_array[totaloutputs];          // data to be passed to algorithm
    int flipflop_array[totalflipflops][5];     // data to be passed to algorithm
    int buff_array[totalbuffs][2];         // data to be passed to algorithm
    int not_array[totalnots][2];          // data to be passed to algorithm
    int and_array[totalands][3];          // data to be passed to algorithm
    int nand_array[totalnands][3];         // data to be passed to algorithm
    int or_array[totalors][3];           // data to be passed to algorithm
    int nor_array[totalnors][3];          // data to be passed to algorithm
    int xor_array[totalxors][3];          // data to be passed to algorithm
    int nxor_array[totalnxors][3];         // data to be passed to algorithm
    
    rewind(fp);
    while (fgets(line, sizeof(line), fp) != NULL) {

      line2 = line;
      
      if (strstr(line, "INPUT(") != NULL) {
	data = strsep(&line2,"(");
	data = strsep(&line2,")");
	input_array[input_counter] = atoi(data);
	input_counter++;
      }

      else if (strstr(line, "OUTPUT(") != NULL) {
	data = strsep(&line2,"(");
	data = strsep(&line2,")");
	output_array[output_counter] = atoi(data);
	output_counter++;
      }

      else if (strstr(line, "= DFF") != NULL) {
	data = strsep(&line2, " ");
	flipflop_array[flipflop_counter][4] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ",");
	flipflop_array[flipflop_counter][1] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ",");
	flipflop_array[flipflop_counter][2] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ",");
	flipflop_array[flipflop_counter][3] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ")");
	flipflop_array[flipflop_counter][0] = atoi(data);
	flipflop_counter++;
      }

      else if (strstr(line, "= BUFF") != NULL) {
	data = strsep(&line2," ");
	buff_array[buff_counter][1] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ")");
	buff_array[buff_counter][0] = atoi(data);
	
	//Buffs[buff_counter].id =
	//Buffs[buff_counter].dep1 = atoi(data);
	
	buff_counter++;
      }

      else if (strstr(line, "= NOT") != NULL) {
	data = strsep(&line2," ");
	not_array[not_counter][1] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ")");
	not_array[not_counter][0] = atoi(data);
	not_counter++;
      }

      else if (strstr(line, "= AND") != NULL) {
	data = strsep(&line2," ");
        and_array[and_counter][2] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ", ");
        and_array[and_counter][0] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ")");
	and_array[and_counter][1] = atoi(data);
	and_counter++;
      }

      else if (strstr(line, "= NAND") != NULL) {
	data = strsep(&line2," ");
        nand_array[nand_counter][2] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ", ");
        nand_array[nand_counter][0] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ")");
	nand_array[nand_counter][1] = atoi(data);
	nand_counter++;
      }

      else if (strstr(line, "= OR") != NULL) {
	data = strsep(&line2," ");
	or_array[or_counter][2] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ", ");
	or_array[or_counter][0] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ")");
	or_array[or_counter][1] = atoi(data);
	or_counter++;
      }

      else if (strstr(line, "= NOR") != NULL) {
	data = strsep(&line2," ");
        nor_array[nor_counter][2] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ", ");
        nor_array[nor_counter][0] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ")");
	nor_array[nor_counter][1] = atoi(data);
	nor_counter++;
      }

      else if (strstr(line, "= XOR") != NULL) {
	data = strsep(&line2," ");
        xor_array[xor_counter][2] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ", ");
        xor_array[xor_counter][0] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ")");
	xor_array[xor_counter][1] = atoi(data);
	xor_counter++;
      }

      else if (strstr(line, "= NXOR") != NULL) {
	data = strsep(&line2," ");
        nxor_array[nxor_counter][2] = atoi(data);
	data = strsep(&line2, "(");
	data = strsep(&line2, ", ");
        nxor_array[nxor_counter][0] = atoi(data);
	data = strsep(&line2, " ");
	data = strsep(&line2, ")");
	nxor_array[nxor_counter][1] = atoi(data);
	nxor_counter++;
      }

      else {

      }

    }
    
    int count = 0;
    char c;
    
    for (c = getc(fp2); c != EOF; c = getc(fp2)) {
      if (c == '\n') {
	count = count + 1;
      }
    }
    rewind(fp2);

    //    printf("count is: %d\n",count);

    char *fault_array[count][3];
    char *fault_array2[count][3];
    
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
      printf("%d\n",input_array[i]);
    }

    printf("\nList of OUTPUT PORTS:\n");
    for (int i = 0; i<output_counter; i++) {
      printf("%d\n",output_array[i]);
    }

    printf("\nList of DFFS:\n");
    for (int i = 0; i<flipflop_counter; i++) {
      printf("Input Signal:    %d    ",flipflop_array[i][0]);
      printf("    Clock Signal:    %d    ",flipflop_array[i][1]);
      printf("    Reset Signal:    %d    ",flipflop_array[i][2]);
      printf("    Enable Signal:    %d    ",flipflop_array[i][3]);
      printf("    Output Signal:    %d\n",flipflop_array[i][4]);
    }

    printf("\nList of BUFFS:\n");
    for (int i = 0; i<buff_counter; i++) {
      printf("Input Signal:    %d    ",buff_array[i][0]);
      printf("    Output Signal:    %d\n",buff_array[i][1]);
    }

    printf("\nList of NOTS:\n");
    for (int i = 0; i<not_counter; i++) {
      printf("Input Signal:    %d    ",not_array[i][0]);
      printf("    Output Signal:    %d\n",not_array[i][1]);
    }

    printf("\nList of ANDS:\n");
    for (int i = 0; i<and_counter; i++) {
      printf("Input Signal 1:    %d    ",and_array[i][0]);
      printf("    Input Signal 2:    %d    ",and_array[i][1]);
      printf("    Output Signal:    %d\n",and_array[i][2]);
    }

    printf("\nList of NANDS:\n");
    for (int i = 0; i<nand_counter; i++) {
      printf("Input Signal 1:    %d    ",nand_array[i][0]);
      printf("    Input Signal 2:    %d    ",nand_array[i][1]);
      printf("    Output Signal:    %d\n",nand_array[i][2]);
    }

    printf("\nList of ORS:\n");
    for (int i = 0; i<or_counter; i++) {
      printf("Input Signal 1:    %d    ",or_array[i][0]);
      printf("    Input Signal 2:    %d    ",or_array[i][1]);
      printf("    Output Signal:    %d\n",or_array[i][2]);
    }

    printf("\nList of NORS:\n");
    for (int i = 0; i<nor_counter; i++) {
      printf("Input Signal 1:    %d    ",nor_array[i][0]);
      printf("    Input Signal 2:    %d    ",nor_array[i][1]);
      printf("    Output Signal:    %d\n",nor_array[i][2]);
    }

    printf("\nList of XORS:\n");
    for (int i = 0; i<xor_counter; i++) {
      printf("Input Signal 1:    %d    ",xor_array[i][0]);
      printf("    Input Signal 2:    %d    ",xor_array[i][1]);
      printf("    Output Signal:    %d\n",xor_array[i][2]);
    }

    printf("\nList of NXORS:\n");
    for (int i = 0; i<nxor_counter; i++) {
      printf("Input Signal 1:    %d    ",nxor_array[i][0]);
      printf("    Input Signal 2:    %d    ",nxor_array[i][1]);
      printf("    Output Signal:    %d\n",nxor_array[i][2]);
    }
    
    printf("\nList of Faults:\n");
    for (int i = 0; i<fault_counter; i++) {
      printf("Fault Identifier:    %s    ",fault_array[i][0]);
      printf("Signal Injected:    %s    ",fault_array[i][1]);
      printf("Fault Type:    %s\n",fault_array[i][2]);
    }
    
    printf("Total fault count: %d\n",fault_counter);
    printf("Unofficial fault count: %d\n",count);
    

    fclose(fp);
    fclose(fp2);


  //TODO: We need to count elements before declaring arrays...
  //Here use the above counters 
    
  //Size of each of these arrays

  
    // const int numInputs = 3;
    //  const int numOutputs = 1;

  /*const int numBuffs = 0;
  const int numNots = 0;
  const int numAnds = 2;
  const int numOrs = 1;
  const int numNAnds = 0;
  const int numNOrs = 0;
  const int numXOrs = 0;
  const int numNXOrs = 0;
  const int numDFFs = 0;
  */

  const int numInputs = input_counter;
  const int numOutputs = output_counter;
  const int numBuffs = buff_counter;
  const int numNots = not_counter;
  const int numAnds = and_counter;
  const int numOrs = or_counter;
  const int numNAnds = nand_counter;
  const int numNOrs = nor_counter;
  const int numXOrs = xor_counter;
  const int numNXOrs = nxor_counter;
  const int numDFFs = flipflop_counter;

  //Every gate and input/output needs a bus associated with it
  const int numBus = numInputs + numOutputs + numBuffs + numNots + numAnds
  + numOrs + numNAnds + numNOrs + numXOrs + numNXOrs + numDFFs;

  //Array values from the parser
  /*
  int Inputs[numInputs]= {10001,10002,10003};
  int Outputs[numOutputs] = {50001};
  gate1in Buffs[numBuffs] = {};
  gate1in Nots[numNots] = {};
  gate2in Ands[numAnds] = {{20001, 10001, 10002},{20002,10001,10002}};
  gate2in Ors [numOrs]= {{50001,20001,20002}};
  gate2in NAnds[numNAnds] = {};
  gate2in NOrs[numNOrs] = {};
  gate2in XOrs[numXOrs] = {};
  gate2in NXOrs[numNXOrs] = {};
  gate2in DFFs[numDFFs] = {};
  */

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
  
  for (int i = 0; i<numInputs; i++) {
    Inputs[i] = input_array[i];
  }

  for (int i = 0; i<numOutputs; i++) {
    Outputs[i] = output_array[i];
  }
  
  for (int i = 0; i<numBuffs; i++) {
    Buffs[i].id = buff_array[i][1];
    Buffs[i].dep1 = buff_array[i][0];
    //std::cout << "Buff ID: " << Buffs[i].id << std::endl;
    //std::cout << "Buff Dep1: " << Buffs[i].dep1 << std::endl;
  }

  
  for (int i = 0; i<numNots; i++) {
    Nots[i].id = not_array[i][1];
    Nots[i].dep1 = not_array[i][0];
  }

  for (int i = 0; i<numAnds; i++) {
    Ands[i].id = and_array[i][2];
    Ands[i].dep1 = and_array[i][0];
    Ands[i].dep2 = and_array[i][1];
    //std::cout << "And ID: " << Ands[i].id << std::endl;
    //std::cout << "And Dep1: " << Ands[i].dep1 << std::endl;
    //std::cout << "And Dep2: " << Ands[i].dep2 << std::endl;
  }

  for (int i = 0; i<numOrs; i++) {
    Ors[i].id = or_array[i][2];
    Ors[i].dep1 = or_array[i][0];
    Ors[i].dep2 = or_array[i][1];
  }

  for (int i = 0; i<numNAnds; i++) {
    NAnds[i].id = nand_array[i][2];
    NAnds[i].dep1 = nand_array[i][0];
    NAnds[i].dep2 = nand_array[i][1];
  }
  
  for (int i = 0; i<numNOrs; i++) {
    NOrs[i].id = nor_array[i][2];
    NOrs[i].dep1 = nor_array[i][0];
    NOrs[i].dep2 = nor_array[i][1];
  }

  for (int i = 0; i<numXOrs; i++) {
    XOrs[i].id = xor_array[i][2];
    XOrs[i].dep1 = xor_array[i][0];
    XOrs[i].dep2 = xor_array[i][1];
  }
  
  for (int i = 0; i<numNXOrs; i++) {
    NXOrs[i].id = nxor_array[i][2];
    NXOrs[i].dep1 = nxor_array[i][0];
    NXOrs[i].dep2 = nxor_array[i][1];
  }

  // need DFF's next

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

  //Only after everything has a bus can we safely cross assignements for everything else
  //Otherwise, we may try and reference a Gate ID that hasn't been assigned

//We made need this code to store different gates in different ways
/*
  BuffMap buffs;
  NotMap nots;
  AndMap ands;
  OrMap ors;
  NAndMap nands;
  NOrMap nors;
  XOrMap xors;
  DFFMap dffs;

  for (int i=0; i < numBuffs; ++i){
    //Buffer<> x(buses[Buffs[i].id],buses[Buffs[i].dep1]);
    //buffs[Buffs[i].id] =x;
  }
  for (int i=0; i < numNots; ++i){
    Not<> x(buses[Nots[i].id],buses[Nots[i].dep1]);
    //nots[Nots[i].id] =x;
  }
  for (int i=0; i < numAnds; ++i){
    And<2> x(buses[Ands[i].id],(buses[Ands[i].dep1],buses[Ands[i].dep2]));
    //ands[Ands[i].id] =x;
  }
  for (int i=0; i < numOrs; ++i){
    std::cout << Ors[i].id << '\n';
    Or<2> og(buses[Ors[i].id],(buses[Ors[i].dep1],buses[Ors[i].dep2]));
    //ors[Ors[i].id] =x;
  }
  for (int i=0; i < numNAnds; ++i){
    Nand<2> x(buses[NAnds[i].id],(buses[NAnds[i].dep1],buses[NAnds[i].dep2]));
    //nands[NAnds[i].id] =x;
  }
  for (int i=0; i < numNOrs; ++i){
    Nor<2> x(buses[NOrs[i].id],(buses[NOrs[i].dep1],buses[NOrs[i].dep2]));
    //nors[NOrs[i].id] =x;
  }
  for (int i=0; i < numXOrs; ++i){
    Xor<2> x(buses[XOrs[i].id],(buses[XOrs[i].dep1],buses[XOrs[i].dep2]));
    //xors[XOrs[i].id] =x;
  }
/*
  for (int i=0; i < numNXOrs; ++i){
    Bus<1> x(NXOrs[i].id,(buses[NXOrs[1].dep1],buses[NXOrs[2].dep2]));
    buses[NXOrs[i].id] =x;
  }
*/
/*
  for (int i=0; i < numDFFs; ++i){
    //dffs[DFFs[i]] = <1>;
    DFlipFlop<> x(DFFs[i].id,(buses[DFFs[i].dep1],buses[DFFs[i].dep2]));
    dffs[DFFs[i].id] =x;
  }
*/
    //Creates arrays of inputs and outputs for use in the change monitors
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

    /* TODO: Add DFF support
    for (int i=0; i < numDFFs; ++i){
      //dffs[DFFs[i]] = <1>;
      DFlipFlop<> x(DFFs[i].id,(buses[DFFs[i].dep1],buses[DFFs[i].dep2]));
      dffs[DFFs[i].id] =x;
    }
    */

    //TODO: Add a universal simulator to test any number of values
    /*
    Bus<1> ins[3] = {buses[10001],buses[10002],buses[10003]};
    ChangeMonitor<numInputs> inputMonitor((buses[10001],buses[10002],buses[10003]), "Input", DUMP_OFF);


    ChangeMonitor<numOutputs> a((buses[50001]),"Output", DUMP_OFF);

    Tester<numInputs> tester((buses[10001],buses[10002],buses[10003])); //Template parameter 2 indicates the bus width of our input

    Simulation::setStopTime(1000);
    Simulation::start();
    */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    return 0;
}
