#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>

using namespace std;

//Prototypes for manipulation of arrays
vector<int> arr_multiply(vector<int>, vector<int>);
vector<int> arr_add(vector<int>, vector<int>);
//Protoype of Polynomial
class Polynomial;

//Maps for locating values by their ids
map<int, Polynomial> functions;
map<int, Polynomial> outputs;

//Protypes for polynomial/gate classes
//Polynomial manipulation class
class Polynomial {
  //vector<int> args;
  public:
    int size;
    int *args = new int[2]; //Need a default value for pointer to delete
    int type;  //Records the gate type, used in evaluating
    int par1;
    int par2;
    //simplieifes getting from a pointer
    int get(int index){
      return *(args+index);
    }

    //Used for initial definition
    //Usually for concatenation of two previous arrays
    void define(int newSize,
                int arr1[],
                int arr2[]) {
        //Delete the array for reassignment
        delete [] args;

        size = newSize; //The size of the new ploly (we never compress)
        args = new int[size];

    }
    //Used to multiply two arrays together
    void define_product(int arr1Size,
                        int arr2Size,
                        int arr1[],
                        int arr2[]) {

        //Delete the array for reassignment
        delete [] args;

        size = arr1Size*arr2Size;
        args = new int[size];

        // Assigns each element to the product of its two item
        for (int a=0; a < arr1Size; ++a){
          for (int b = 0; b < arr2Size; ++b){
            cout << *(arr1+a) * *(arr2+b) << "\n";
            *(args +(a*arr2Size + b)) = *(arr1+a) * *(arr2+b);
          }
        }
    }

    //Polynomial evaluation function
    //Call this recursively on outputs to generate their value functions
    vector<int> evaluate(){
      cout << "Eval";
      vector<int> in1,in2,out;
      vector<int> coef1,coef2,coef3;//Coefficients for vector manipulations
      switch (type){
        //OUTPUT
        case 0:  //Handles like a buff
          out = functions[par1].evaluate();
          break;
        //BUFF
        case 1:
          out =functions[par1].evaluate();
          break;
        //NOT
        case 2:
          out = functions[par1].evaluate(); //Not gate modifer
          coef1 = {1};
          coef2 = {-1};
          out = arr_add(coef1,arr_multiply(out,coef2)); //Apply negative
          break;
        //and
        case 3:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          out = arr_multiply(in1,in2); //Apply product to arrays
          break;
        //OR
        case 4:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          coef1 = {-1};
          out = arr_add(arr_add(arr_multiply(coef1,arr_multiply(in1,in2)),in1),in2);
          break;
        //nand
        case 5:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          coef1 = {-1};
          coef2 = {1};
          out = arr_multiply(coef1,arr_multiply(in1,in2));
          out = arr_add(coef2,out);//add coefficient to the front
          break;
        //nor
        case 6:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          coef1 = {1};
          coef2 = {1};
          coef3 = {-1};
          out = arr_add(coef1,arr_add(arr_multiply(coef2,arr_multiply(in1,in2)),arr_add(arr_multiply(coef3,in1),arr_multiply(coef3,in2))));
          break;
        //XOR
        case 7:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          coef1 = {-2};
          out = arr_add(arr_multiply(coef1,arr_multiply(in1,in2)),arr_add(arr_multiply(in1,in1),arr_multiply(in2,in2)));
          break;
        //Nxor
        case 8:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          coef1 = {-2};
          coef2 = {1};
          coef3 = {-1};
          out = arr_add(coef2,arr_multiply(coef3,arr_add(arr_multiply(coef1,arr_multiply(in1,in2)),arr_add(arr_multiply(in1,in1),arr_multiply(in2,in2)))));
          break;
        // DFF
        case 9:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          break;
        // input
        case 10:
          out = {1};
          break;
        default:  //if an undeclared/broken type, treat it as an input
          out = {1};
    }
  return out;
  }
};









//MAIN FUNCTION/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//Sample of values
/*
//Array sizes
const int numInputs = 5;
const int numAnds = 1;
const int numNxors = 1;
const int numXors = 2;

vector< int > inputs = {100,101,228,229,105};
vector< vector<int> > ands = {{301,504,105}};
vector< vector<int> > nxors = {{502,100,101}};
vector< vector<int> > xors= {{503,228,229},{504,502,503}};
*/

//Array sizes
const int numInputs = 5;
const int numBuffs = 0;
const int numNots = 0;
const int numAnds = 1;
const int numNands = 0;
const int numOrs = 0;
const int numNors = 0;
const int numXors = 2;
const int numNxors = 1;

vector< int > inputs = {100,101,228,229,105};
vector< vector<int> > nots = {};
vector< int > buffs={};
vector< vector<int> > ands = {{301,504,105}};
vector< vector<int> > nands= {};
vector< vector<int> > ors = {};
vector< vector<int> > nors = {};
vector< vector<int> > xors= {{504,502,503},{502,100,101}};
vector< vector<int> > nxors = {{503,228,229}};




int main() {
  cout << "Starting assignment\n";

  for (int a = 0; a < numInputs; ++a){
    Polynomial gate;
    gate.type = 10;
    functions[inputs[a]] = gate;
  }
  for (int a = 0; a < numBuffs; ++a){
    Polynomial gate;
    gate.type = 1;
    functions[buffs[a]] = gate;
  }
  for (int a = 0; a < numNots; ++a){
    Polynomial gate;
    gate.type = 2;
    gate.par1 = nots[a][1];
    functions[nots[a][0]] = gate;
  }
  for (int a = 0; a < numAnds; ++a){
    Polynomial gate;
    gate.type = 3;
    gate.par1 = ands[a][1];
    gate.par2 = ands[a][2];
    functions[ands[a][0]] = gate;
    outputs[ands[a][0]] = gate;

    cout << gate.par1 << '\n';
    cout << gate.par2 << '\n';
    cout << "GATE\n";
  }
  for (int a = 0; a < numOrs; ++a){
    Polynomial gate;
    gate.type = 4;
    gate.par1 = ors[a][1];
    gate.par2 = ors[a][2];
    functions[ors[a][0]] = gate;
    outputs[ors[a][0]] = gate;

    cout << gate.par1 << '\n';
    cout << gate.par2 << '\n';
    cout << "GATE\n";
  }
  for (int a = 0; a < numNands; ++a){
    Polynomial gate;
    gate.type = 5;
    gate.par1 = nands[a][1];
    gate.par2 = nands[a][2];
    functions[nands[a][0]] = gate;
    outputs[nands[a][0]] = gate;

    cout << gate.par1 << '\n';
    cout << gate.par2 << '\n';
    cout << "GATE\n";
  }
  for (int a = 0; a < numNors; ++a){
    Polynomial gate;
    gate.type = 6;
    gate.par1 = nors[a][1];
    gate.par2 = nors[a][2];
    functions[nors[a][0]] = gate;
    outputs[nors[a][0]] = gate;

    cout << gate.par1 << '\n';
    cout << gate.par2 << '\n';
    cout << "GATE\n";
  }
  for (int a = 0; a < numXors; ++a){
    Polynomial gate;
    gate.type = 7;
    gate.par1 = xors[a][1];
    gate.par2 = xors[a][2];
    functions[xors[a][0]] = gate;

    cout << gate.par1 << '\n';
    cout << gate.par2 << '\n';
    cout << "GATE\n";
  }
  for (int a = 0; a < numNxors; ++a){
    Polynomial gate;
    gate.type = 8;
    gate.par1 = nxors[a][1];
    gate.par2 = nxors[a][2];
    functions[nxors[a][0]] = gate;

    cout << gate.par1 << '\n';
    cout << gate.par2 << '\n';
    cout << "GATE\n";
  }

  cout << "Starting Evaluate 301\n";
  vector<int> polyhash = functions[301].evaluate();
  cout << "\nFinished\n";

  cout << "OUTPUT:   ";
  for (int alpha = 0; alpha < polyhash.size(); ++alpha){
    if (!(polyhash[alpha]==0)){
      cout << polyhash[alpha] << " ";
    }
  }


  cout << "\n";
  cout << "Starting Evaluate 502\n";
  polyhash = functions[502].evaluate();
  cout << "\nFinished\n";
  cout << "OUTPUT:   ";
  for (int alpha = 0; alpha < polyhash.size(); ++alpha){
    if (!(polyhash[alpha]==0)){
      cout << polyhash[alpha] << " ";
    }
  }
  cout << "\n";


  cout << "Starting Evaluate 503\n";
 polyhash = functions[503].evaluate();
  cout << "\nFinished\n";
  cout << "OUTPUT:   ";
  for (int alpha = 0; alpha < polyhash.size(); ++alpha){
    if (!(polyhash[alpha]==0)){
      cout << polyhash[alpha] << " ";
    }
  }
  cout << "\n";


  cout << "Starting Evaluate 504\n";
  polyhash = functions[504].evaluate();
  cout << "\nFinished\n";
  cout << "OUTPUT:   ";
  for (int alpha = 0; alpha < polyhash.size(); ++alpha){
    if (!(polyhash[alpha]==0)){
      cout << polyhash[alpha] << " ";
    }
  }
  cout << "\n";
}













//Array manipulation functions//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//Multiplies the set of arrays together
//Multiply each element together, forming a new list of all the products
vector<int> arr_multiply(vector<int> in1, vector<int> in2){
  vector<int> out;
  //put each element in A in the beginning of B (end of A touches beginning of B)
  for (int a = 0; a < in1.size(); ++a){
    for (int b = 0; b < in2.size(); ++b){
      out.push_back(in1[a]*in2[b]); //Adds each product
    }
  }
  return out;
}
//Doesn't add, that could interfere with algorithm.
//Just concatenate the arrs (order will be identical if faults are
vector<int> arr_add(vector<int> in1, vector<int> in2){
  for (int a = in1.size(); a >= 0; --a) {
    in2.insert(in2.begin(),in1[a]);
  }
  return in2;
}







//GATE DFINITIONS///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Return values for coeffiients on each polynomial in ascending order
