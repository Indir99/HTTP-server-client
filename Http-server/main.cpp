#include <iostream>
#include "ApplicationLogic/CustomServer.h"

int main()
{
    ApplicationLogic::CustomServer server(60000);
    server.Start();

    while (1)
    {
        server.Update(-1, true);
    }



    return 0;
}
