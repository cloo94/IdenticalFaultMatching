/*
Compile with these steps
1.`gcc -Wall -g -c demo.c -o demo.o`
2. gcc -g -o demo demo.o libabc.a -lm -ldl -rdynamic -lreadline -ltermcap -lpthread`
*/




/**CFile****************************************************************

  FileName    [demo.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [ABC as a static library.]

  Synopsis    [A demo program illustrating the use of ABC as a static library.]

  Author      [Alan Mishchenko]

  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: demo.c,v 1.00 2005/11/14 00:00:00 alanmi Exp $]

***********************************************************************/

#include <stdio.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

// procedures to start and stop the ABC framework
// (should be called before and after the ABC procedures are called)
extern void   Abc_Start();
extern void   Abc_Stop();

// procedures to get the ABC framework and execute commands in it
extern void * Abc_FrameGetGlobalFrame();
extern int    Cmd_CommandExecute( void * pAbc, char * sCommand );

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [The main() procedure.]

  Description [This procedure compiles into a stand-alone program for
  DAG-aware rewriting of the AIGs. A BLIF or PLA file to be considered
  for rewriting should be given as a command-line argument. Implementation
  of the rewriting is inspired by the paper: Per Bjesse, Arne Boralv,
  "DAG-aware circuit compression for formal verification", Proc. ICCAD 2004.]

  SideEffects []

  SeeAlso     []

***********************************************************************/
void compare(char file1[], char file2[])
{
  char Command[1000];
  //char file1[] = "faultdesign1.bench";
  //char file2[] = "faultdesign2.bench";
  printf("%s\n",file1 );
  printf("%s\n",file2 );

/*
  Abc_Start();
    //sprintf(Command,"read_bench %s \n",file1);
    //sprintf(Command,"read_bench %s \n",file2);

    sprintf(Command,"cec %s %s",file1,file2);
  Abc_Stop();
*/





// parameters
int fUseResyn2  = 0;
int fPrintStats = 1;
int fVerify     = 1;
// variables
void * pAbc;
char * pFileName;
clock_t clkRead, clkResyn, clkVer, clk;

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// start the ABC framework
Abc_Start();
pAbc = Abc_FrameGetGlobalFrame();


//////////////////////////////////////////////////////////////////////////
// perform verification
clk = clock();
if ( fVerify )
{
    sprintf( Command, "cec %s %s",file1,file2);
    if ( Cmd_CommandExecute( pAbc, Command ) )
    {
        fprintf( stdout, "Cannot execute command \"%s\".\n", Command );
    }
}
clkVer = clock() - clk;


//////////////////////////////////////////////////////////////////////////
// stop the ABC framework
Abc_Stop();


}

/*
NOTE for Testing individual component

int main( int argc, char * argv[] )
{
    printf("Test\n");
    compare(argv[1],argv[2]);

    return 0;
}

*/
