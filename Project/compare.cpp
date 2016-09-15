#include <iostream>
#include <fstream>

#include <string>
#include<vector>

using namespace std;

vector< vector<int> >faultClasses;

bool isMatch(){
  // 1. Open the file
  // 2. Read the output(courtesy of abc)
  // 3. Return true if match, false otherwise
  string result;
  ifstream inFile;
  inFile.open("testOuts.txt");
  getline(inFile,result);

  inFile.close();
  remove("testOuts.txt"); //Delete this file when we're done
  if (result == "These networks are equivalent after structural hashing."){
    return true;
  }
  return false;
}
//C externs
extern "C" {
 void compare(char[], char[]);
}

// C++ externs
extern int parse(int, char*[]);

int main(int argc, char *argv[])
{
  //These constants need to be defined at parse or calculated

  //++++++++++++++++const int totalFaults = 2;

  /////////////////////////////////////////////////////////////

  const int totalFaults = parse(argc,argv);

  //For each fault:
    //  1.  Compare each fault to the first element of each existing fault class
    //  2.  If the fault doesn't fit a fault class, assign it to a new class
  bool foundClass = false; //Will tell us when a vector finds a match
  for (int i = 0; i < totalFaults; ++i){
    foundClass = false; //
    //Test against first member of each fault class
    for (int a = 0; a < faultClasses.size(); ++a){
      //Calls the abc output, which writes info to an output file


      string string1 = string("faultdesign") + to_string(i+1) + string(".bench");
      string string2 =  string("faultdesign") + to_string(faultClasses[a][0]) + string(".bench");

      char str1[100];
      char str2[100];

      for(int z=0;z<=string1.size();++z){
        str1[z] = string1[z];
      }
      for(int z=0;z<=string2.size();++z){
        str2[z] = string2[z];
      }


      std::cout << "Comparing fault pairs" << "\n";

      compare(str1,str2);

      foundClass = isMatch();
      //If there's a class match, then stop searching and break
      if (foundClass){
        faultClasses[a].push_back(i+1); //Faults index at 1, need to increase i
        //break; //End loop
      }
    }
    //If a class match wasn't found, create a new class
    if (!foundClass){
      std::cout<<"Adding new class" << "\n";
      vector<int> newClass = {i+1}; //Fault lists index at 1, so their names are different
      faultClasses.push_back(newClass);
    }
    std::cout << "found class?" << foundClass <<"\n";
  }
  std::cout << "Number of classes:  " << faultClasses.size() << "\n";
  std::cout << "Outputting file..." << "\n";
//Now print each fault class on a line in our output file
  //Initialize a file
  ofstream outfile;
  outfile.open("faultPairs.txt");

  for (int j = 0; j < faultClasses.size(); ++j){
    //write all the pairs for that class
    for (int a = 1; a < faultClasses[j].size(); ++a){//This should eliminate size 1 classes
      std::cout << "Pair: " << faultClasses[j][0] << faultClasses[j][a] << "\n";
      outfile << faultClasses[j][0] << " " << faultClasses[j][a] << "\n";
    }
  }

  outfile.close();

  return 0;
}
