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

//Protypes for olynomial/gate classes
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
          coef1 = {3};
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
          coef2 = {3};
          coef3 = {-1};
          out = arr_add(coef1,arr_add(arr_multiply(coef2,arr_multiply(in1,in2)),arr_add(arr_multiply(coef3,in1),arr_multiply(coef3,in2))));
          break;
        //XOR
        case 7:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          coef1 = {-2};
          out = arr_add(arr_multiply(coef1,arr_multiply(in1,in2)),arr_add(in1,in2));
          break;
        //Nxor
        case 8:
          in1 = functions[par1].evaluate();
          in2 = functions[par2].evaluate();
          coef1 = {1};
          coef2 = {2};
          coef3 = {-1};
          out =arr_add(coef1,arr_add(arr_multiply(coef2,arr_multiply(in1,in2)),arr_add(arr_multiply(coef3,in1),arr_multiply(coef3,in2))));
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


int main() {
  int Lsize = 2;
  int Ssize = 2;

  int Largs[Lsize] = {1,2};
  int Sargs[Ssize] = {3,4};



  Polynomial gate;
  //gate.define(Lsize+Ssize,Largs,Sargs);
  //gate.define_product(Lsize,Ssize,Largs,Sargs);

}













//Array manipulation functions//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//Multiplies the set of arrays together
//Multiply each element together, forming a new list of all the products
vector<int> arr_multiply(vector<int> in1, vector<int> in2){
  vector<int> out;
  //put each element in A in the beginning of B (end of A touches beginning of B)
  for (int a = in1.size(); a >= 0; --a) {
    in2.insert(in2.begin(),in1[a]);
  }
  return in2;
}
//Doesn't add, that could interfere with algorithm.
//Just concatenate the arrs (order will be identical if faults are
vector<int> arr_add(vector<int> in1, vector<int> in2){
  vector<int> out;
  for (int a = 0; a < in1.size(); ++a){
    for (int b = 0; b < in2.size(); ++b){
      out.push_back(in1[a]*in2[b]); //Adds each product
    }
  }
  return out;
}







//GATE DFINITIONS///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Return values for coeffiients on each polynomial in ascending order
