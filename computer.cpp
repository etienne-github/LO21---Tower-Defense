#include "computer.h"

Computer::Computer()
{

    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            this->objectMap[i][j]=0;
            this->constructible[i][j]=true;
            vie =30;
            credit=0;
            emit vieChanged();
            emit creditChanged();

        }
    }
}
