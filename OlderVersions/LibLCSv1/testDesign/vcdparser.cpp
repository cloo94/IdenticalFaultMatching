// VCD DUMP PARSER
// compile with: g++ -o vcdparser vcdparser.cpp -I"libLCS/" -L"libLCS/lib" -l LCS
// when running this file, all the vcd dumps need to be in a ./dumps directory

#include <string>
#include <lcs/lcs.h>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>

using namespace lcs;

struct output {
  int input00; // corresponds to 0 for a 1 input gate
  int input01; // dont care about this for a 1 input gate
  int input10; // dont care about this for a 1 input gate
  int input11; // corresponds to 1 for a 1 input gate 
};

typedef std::map<int,output> VCDMap; // int = gate number/ID, output = outputs for the 4 given possible inputs

int main() {  // need to do this for all vcd files
  
  VCDMap gate;
  FILE *fp;
  char line[100];
  char prev_line[100];
  char *line2;
  char *data;
  output output;

  // { everything else needs to be in a loop for all dump files

    
  if (!(fp = fopen("dump.vcd","r"))) {  // changes with name of dump file
    perror("Error opening file");
    exit(1);
  }
  
  while (fgets(line, sizeof(line), fp) != NULL) {

    // FOR 2 INPUT GATES
    
    if (strstr(line, "b00 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) { // this should never be the case
	line2 = line;
	data = strsep(&line2,"Output"); 
	//printf("this is the data for b00 input (there is a # timestamp below): Needs to be same as above\n");
	output.input00 = atoi(data);
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b00 input (there is NOT a # timestamp below): %s\n",data);
	output.input00 = atoi(data);
      }
    }

    else if (strstr(line, "b01 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b01 input (there is a # timestamp below): Needs to be same as above\n");
	output.input01 = output.input00;
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b01 input (there is NOT a # timestamp below): %s\n",data);
	output.input01 = atoi(data);
      }
    }

    else if (strstr(line, "b10 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b10 input (there is a # timestamp below): Needs to be same as above\n");
	output.input10 = output.input01;
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b10 input (there is NOT a # timestamp below): %s\n",data);
	output.input10 = atoi(data);
      }
    }

    else if (strstr(line, "b11 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b11 input (there is a # timestamp below): Needs to be same as above\n");
	output.input11 = output.input10;
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b11 input (there is NOT a # timestamp below): %s\n",data);
	output.input11 = atoi(data);
      }
    }

    // FOR 1 INPUT GATES
    
    else if (strstr(line, "b0 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) { // this should never be the case
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b0 input (there is a # timestamp below): Needs to be same as above\n");
	output.input00 = atoi(data);
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b0 input (there is NOT a # timestamp below): %s\n",data);
	output.input00 = atoi(data);
      }
      output.input01 = 2; // dont care state
      output.input10 = 2; // dont care state      
    }
    
    else if (strstr(line, "b1 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b1 input (there is a # timestamp below): Needs to be same as above\n");
	output.input11 = output.input00;
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b1 input (there is NOT a # timestamp below): %s\n",data);
	output.input11 = atoi(data);
      }
      output.input01 = 2; // dont care state
      output.input10 = 2; // dont care state
    }   
       
    else {
      
    }
  }
  
  gate[50] = output; // gate id 50 (50 is just a random value)
  std::cout << "This is the b00 Output: " << gate[50].input00 << std::endl;
  std::cout << "This is the b01 Output: " << gate[50].input01 << std::endl; // a value of 2 means it is a dont care state (1 input gate)
  std::cout << "This is the b10 Output: " << gate[50].input10 << std::endl; // a value of 2 means it is a dont care state (1 input gate)
  std::cout << "This is the b11 Output: " << gate[50].input11 << std::endl;

  // } end loop for all dump files

  // once this loops, at this point should have all fault-free design knowledge
  // next need to start injecting faults one by one, comparing the VCDMap's starting at the faulty gate and all further children

  // for fault-free design knowledge: this file assumes we have the following info: all the vcd dump files, separately named labeled with their gate id (output port) (i.e. dump50000.vcd, dump 50001.vcd)
  // for fault comparisons: this file assumes we have the following info: access to the children of all gates, and can check, from the faulty gate onwards, the parsed vcd dump file info of the circuit with a fault and the fault-free circuit

  /* for each fault:
     generate a VCDMap (from files labeled dumpfault1.vcd, dumpfault2.vcd, whatever the fault id is)
     compare logic values to the next fault - compare VCDMaps starting at children onwards
     if they are the same, then they are identical faults, store this info somewhere
  */

  // to identify a fault: check first born childs of both faults, if their outputs are identical, then proceed to check later relationships (i.e. if 3rd born + 1st born child are the same, check those). if not, break immediately - not identical

  /* looking through all dump files in a directory - dont need
  DIR *dpdf;
  struct dirent *epdf;

  dpdf = opendir("./dumps");
  if (dpdf != NULL){
    while (epdf = readdir(dpdf)){
      printf("Filename: %s",epdf->d_name);
      // std::cout << epdf->d_name << std::endl;
    }
  }
  closedir(dpdf);
  */
  
  /* check if gates are identical
  if (gate[id1].input00 == gate[id2].input00 && gate[id1].input01 == gate[id2].input01 && gate[id1].input10 == gate[id2].input10 && gate[id1].input11 == gate[id2].input11) {
    // these faults AT THAT PARTICULAR GATE are identical, need to check this for all first born childs and shared descendants
  }
  else {
    // they are not
  }
  */
  

  return 0;

}
