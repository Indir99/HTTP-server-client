#include <iostream>
#include "ApplicationLogic/CustomServer.h"
#include "ApplicationLogic/SoapMessageCreator.h"


int main()
{
    ApplicationLogic::InitializeLibrary();
    ApplicationLogic::CustomServer server(60000);
    server.Start();

    while (1)
    {
        server.Update(-1, true);
    }
    ApplicationLogic::DeinitializeLibrary();


    return 0;
}
