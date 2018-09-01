//my
#include "include/Constants.hh"
#include "src/Tree.h"
//c++
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        cout<<"--> Incorrect number of the input parameters:"<<endl;
        cout<<"--> [1] - A name of the input .root file."<<endl;
        cout<<"--> [2] - A number of the event."<<endl;
        cout<<"--> [3] - A number of the channel."<<endl;
        cout<<endl;
        return -1;
    }

    Tree pointer(argv[1]);

    pointer.VisualisationAllChannels(atoi(argv[2]));
    pointer.VisualisationOnlyOneChannel(atoi(argv[2]),atoi(argv[3]));

    return 0;
}
