//g++ simTest.cpp -I"libLCS/" -L"libLCS/lib" -l LCS

#include <lcs/bus.h>
#include <lcs/not.h>
#include <lcs/and.h>
#include <lcs/or.h>
#include <lcs/xor.h>
#include <lcs/tester.h>
#include <lcs/simul.h>
#include <lcs/changeMonitor.h>

int main()
{
  /*
  First Models 2 XORs, 1 XORs, 1 AND
  Then 1 NXOR + 1 XOR, 1XOR, 1 AND
  Then 1XOR + 1 NXOR, 1 AND
  Then 2 XORs, 1 NXOR, 1 AND
  */

    lcs::Bus<1> a, b, out;

    //lcs::Not<> ng1(a_, a), ng2(b_, b);

    out.cass<0>(a & b);

    lcs::ChangeMonitor<2> inputMonitor((a,b), "Input", lcs::DUMP_ON);
    lcs::ChangeMonitor<1> outputMonitor(out, "Output", lcs::DUMP_ON);

    lcs::Tester<2> tester((a,b));

    lcs::Simulation::setStopTime(5000);
    lcs::Simulation::start();

    return 0;

}
