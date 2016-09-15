// VCD DUMP PARSER
// compile with: g++ -o vcdparser vcdparser.cpp -I"libLCS/" -L"libLCS/lib" -l LCS

#include <string>
#include <lcs/lcs.h>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace lcs;

struct outputs {
  int input00;
  int input01;
  int input10;
  int input11;
};

typedef std::map<int,outputs> VCDMap; // int = gate number/ID, outputs = outputs for the 4 given possible inputs

int main() {  // need to do this for all vcd files
  
  VCDMap thisgate;
  FILE *fp;
  char line[100];
  char prev_line[100];
  char *line2;
  char *data;
  outputs thisoutput;

  // { this needs to be a loop, until bottom, for all dump files
  
  if (!(fp = fopen("dump.vcd","r"))) {  // changes with name of dump file
    perror("Error opening file");
    exit(1);
  }
  
  while (fgets(line, sizeof(line), fp) != NULL) {

    if (strstr(line, "b00 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) { // this should never be the case
	line2 = line;
	data = strsep(&line2,"Output"); 
	//printf("this is the data for b00 input (there is a # timestamp below): Needs to be same as above\n");
	thisoutput.input00 = atoi(data);
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b00 input (there is NOT a # timestamp below): %s\n",data);
	thisoutput.input00 = atoi(data);
      }
    }

    else if (strstr(line, "b01 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b01 input (there is a # timestamp below): Needs to be same as above\n");
	thisoutput.input01 = thisoutput.input00;
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b01 input (there is NOT a # timestamp below): %s\n",data);
	thisoutput.input01 = atoi(data);
      }
    }

    else if (strstr(line, "b10 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b10 input (there is a # timestamp below): Needs to be same as above\n");
	thisoutput.input10 = thisoutput.input01;
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b10 input (there is NOT a # timestamp below): %s\n",data);
	thisoutput.input10 = atoi(data);
      }
    }

    else if (strstr(line, "b11 Input") != NULL) {
      if ((fgets(line, sizeof(line), fp) != NULL) && strstr(line, "#") != NULL) {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b11 input (there is a # timestamp below): Needs to be same as above\n");
	thisoutput.input11 = thisoutput.input10;
      } else {
	line2 = line;
	data = strsep(&line2,"Output");
	//printf("this is the data for b11 input (there is NOT a # timestamp below): %s\n",data);
	thisoutput.input11 = atoi(data);
      }
    }
    
    else {
      
    }
  }
  
  thisgate[50] = thisoutput; // gate id 50
  std::cout << "This is the b00 Output: " << thisgate[50].input00 << std::endl;
  std::cout << "This is the b01 Output: " << thisgate[50].input01 << std::endl;
  std::cout << "This is the b10 Output: " << thisgate[50].input10 << std::endl;
  std::cout << "This is the b11 Output: " << thisgate[50].input11 << std::endl;

  // } end loop for all dump files
  return 0;

}
