// g++ -std=c++11 faultparser.cpp -o faultparser
// Usage: ./faultparser fault_description.txt

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>


void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {  // http://stackoverflow.com/questions/1494399/how-do-i-search-find-and-replace-in-a-standard-string
  size_t pos = 0;
  while((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
}


int main (int argc, char * argv[]) {

  char line[100];
  char *line2;
  char *data;
  FILE *fp;
  int totalfaults = 0;  // NEEDS TO BE PASSED ON
  int fault_counter = 0;  // NEEDS TO BE PASSED ON
  char c;
  //  char *design_file = argv[1];
  char *fault_file = argv[1];

  
  char line3[100];
  char *line4;
  char *data2;
  FILE *fp2;

  
  /*
  if (argc != 3) {
    printf("Error: Please input a gate design file and fault description file\n");
    exit(1);
  }

  if (!(fp = fopen(design_file,"r"))) {
    perror("Error opening file");
    exit(1);
  }
  */

  if (argc != 2) {
    printf("Error: Please input a fault description file\n");
    exit(1);
  }
  
  if (!(fp = fopen(fault_file,"r"))) {
    perror("Error opening file");
    exit(1);
  }

  for (c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n') {
      totalfaults++;
    }
  }
  rewind(fp);

  char *fault_array[totalfaults][3];
  char *fault_array2[totalfaults][3];


  std::string filename1 = "test";
  std::string filename2;
  std::string filename3 = ".bench";
  std::string filename;

  while (fgets(line, sizeof(line), fp) != NULL) {  // for each fault in the fault_description.txt file

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
    strncpy(fault_array[fault_counter][0],fault_array2[fault_counter][0],strlen(fault_array2[fault_counter][0])+1);
    
    fault_array[fault_counter][1] = (char *)malloc(sizeof(char) * strlen(fault_array2[fault_counter][1]));
    strncpy(fault_array[fault_counter][1],fault_array2[fault_counter][1],strlen(fault_array2[fault_counter][1])+1);



    filename2 = std::string(fault_array[fault_counter][0]);
    filename = filename1 + filename2 + filename3;
    std::ifstream src("design_04.bench", std::ios::binary);  // DEPENDS ON NAME OF GATE DESIGN FILE
    std::ofstream dst(filename, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    std::string theoutfile = "faultdesign" + filename2 + filename3;
    std::ofstream outFile(theoutfile,std::ios::binary);  //std::ofstream::binary //theoutfile
    std::ifstream readFile(filename,std::ios::binary);  //std::ifstream::binary
    std::string readout;
    std::string search;
    std::string replace;

    std::string newgate;

    if (fault_array[fault_counter][2] == "RDOB_AND") {
      newgate = "AND";
    } else if (fault_array[fault_counter][2] == "RDOB_NAND") {
      newgate = "NAND";
    } else if (fault_array[fault_counter][2] == "RDOB_OR") {
      newgate = "OR";
    } else if (fault_array[fault_counter][2] == "RDOB_NOR") {
      newgate = "NOR";
    } else if (fault_array[fault_counter][2] == "RDOB_XOR") {
      newgate = "XOR";
    } else if (fault_array[fault_counter][2] == "RDOB_NXOR") {
      newgate = "NXOR";
    } else if (fault_array[fault_counter][2] == "RDOB_NOT") {
      newgate = "NOT";
    } else if (fault_array[fault_counter][2] == "RDOB_BUFF") {
      newgate = "BUFF";
    } else if (fault_array[fault_counter][2] == "SA0") {
      newgate = "SA0";
    } else if (fault_array[fault_counter][2] == "SA1") {
      newgate = "SA1";
    } else if (fault_array[fault_counter][2] == "NEG") {
      newgate = "NEG";
    } else {
    }
    
        
    search = std::string(fault_array[fault_counter][1]) + " = ";
    replace = std::string(fault_array[fault_counter][1]) + " = " + newgate;
    //search = "2404 = BUFF";
    //replace = "2404 = NOT";

    char *searchfor = new char[search.length()+1];
    std::strcpy(searchfor,search.c_str());
    
    char *replacewith = new char[replace.length()+1];
    std::strcpy(replacewith,replace.c_str());
        
    std::string holder;
    std::string holder2;
    std::string thedata;

    
    std::string filename_char = filename;
    const char *filename_c = filename_char.c_str();
    
    if (!(fp2 = fopen(filename_c,"r"))) {
      perror("Error opening file");
      exit(1);
    }

    std::string input_checker;
    input_checker = "PUT(" + std::string(fault_array[fault_counter][1]) + ")";
    char *inputchecker = new char[input_checker.length()+1];
    std::strcpy(inputchecker,input_checker.c_str());
    
    
    const std::string& lookfor = std::string(fault_array[fault_counter][1]);
    const std::string& gate1 = "GATE1";
    const std::string& gate2 = "GATE2";

    std::string test1;
    test1 = std::string(fault_array[fault_counter][1]);
    char *test2 = new char[test1.length()+1];
    std::strcpy(test2,test1.c_str());

    std::string line5;
    std::string test3 = search + "BUFF";
    std::string test4 = search + "NOT";
    char *test5 = new char[test3.length()+1];
    std::strcpy(test5,test3.c_str());
    char *test6 = new char[test4.length()+1];
    std::strcpy(test6,test4.c_str());
    
        
    fault_counter++;
    int stop = 0;
    
    while (fgets(line3, sizeof(line3), fp2) != NULL) {  // for each line 

      line4 = line3;
      
      if ((strstr(line3, searchfor) != NULL) && (newgate != "SA0") && (newgate != "SA1") && (newgate != "NEG")) {

	data2 = strtok(line4,"(");
	data2 = strtok(NULL,")");
	char begin[2] = "(";
	char end[2] = ")";
	char *data3 = strcat(begin,data2);
	char *data4 = strcat(data3,end);
	
	std::string finalreplace;
	finalreplace = replace + std::string(data4);
	
	outFile << finalreplace << std::endl;
	//}

	//line5 = std::string(line3);
	
      } else if ((strstr(line3, test2) != NULL) && (strstr(line3, inputchecker) == NULL) && (strstr(line3, searchfor) == NULL)) {  // ELSE IF ITS NOT THE GATE W/ SA0 SA1 OR NEG, print out the line, else delete that line

	line5 = std::string(line3);
	
	if (newgate == "SA0") {
	  ReplaceStringInPlace(line5, lookfor, gate2);
	  //std::cout << "For file " << theoutfile << " SA0 at gate " << lookfor << " line: " << line5;
	  outFile << line5;
	} else if (newgate == "SA1") {
	  ReplaceStringInPlace(line5, lookfor, gate2);
	  //std::cout << "For file " << theoutfile << " SA1 at gate " << lookfor << " line: " << line5;
	  outFile << line5;
	} else if (newgate == "NEG") {
          ReplaceStringInPlace(line5, lookfor, gate1);
	  //std::cout << "For file " << theoutfile << " NEG at gate " << lookfor << " line: " << line5;
	  outFile << line5;
	} else {
	}
	
      } else if ((strstr(line3, test5) != NULL) || (strstr(line3, test6) != NULL)) {

	line5 = std::string(line3);
	line4 = line3;
	
	
	if (newgate == "SA0") {
	  //std::cout << "For file " << theoutfile << " SA0 at BUFF/NOT gate " << lookfor << " line: " << line5;
	  outFile << lookfor << " = BUFF(GATE2)" << std::endl;
	} else if (newgate == "SA1") {
	  //std::cout << "For file " << theoutfile << " SA1 at BUFF/NOT gate " << lookfor << " line: " << line5;
	  outFile << lookfor << " = BUFF(GATE2)" << std::endl;
	} else if ((newgate == "NEG") && (strstr(line3, test5) != NULL)) { // = BUFF
	  
	  data2 = strtok(line4,"(");
	  data2 = strtok(NULL,")");
	  std::string thedata;
	  thedata = std::string(data2);
	  stop = 1;
	  
	  //std::cout << "For file " << theoutfile << " NEG at BUFF gate " << lookfor << " line: " << line5;
	  outFile << lookfor << " = NOT(" << thedata<< ")" << std::endl;
	} else if ((newgate == "NEG") && (strstr(line3, test6) != NULL)) {  // = NOT

          data2 = strtok(line4,"(");
	  data2 = strtok(NULL,")");
	  std::string thedata;
	  thedata = std::string(data2);
	  stop = 1;
	  
	  //std::cout << "For file " << theoutfile << " NEG at NOT gate " << lookfor << " line: " << line5;
	  outFile << lookfor << " = BUFF(" << thedata << ")" << std::endl;
	} else {
	}
	
      }	else {
	outFile << line3;
      }
      
    }
    
    
    if (newgate == "SA0") {
      outFile << "GATE1 = NOT(" << lookfor << ")" << std::endl;
      outFile << "GATE2 = NXOR(GATE1, " << lookfor << ")" << std::endl;
    } else if (newgate == "SA1") {
      outFile << "GATE1 = NOT(" << lookfor << ")" << std::endl;
      outFile << "GATE2 = XOR(GATE1, " << lookfor << ")" << std::endl;
    } else if ((newgate == "NEG") && (stop == 0)) {
      outFile << "GATE1 = NOT(" << lookfor << ")" << std::endl;
    } else {
    }
    
    
    fclose(fp2);
    remove(filename.c_str());
    //fault_counter++;
  }
  

  /* Prints out the parsed information */
  
  /*
  printf("\nList of Faults:\n");
  for (int i = 0; i<fault_counter; i++) {
    printf("Fault Identifier:    %s    ",fault_array[i][0]);
    printf("Signal Injected:    %s    ",fault_array[i][1]);
    printf("Fault Type:    %s\n",fault_array[i][2]);
  }

  printf("Total actual fault count: %d\n",fault_counter);
  printf("Unofficial fault count: %d\n",totalfaults);
  */
  
  fclose(fp);
    
}
