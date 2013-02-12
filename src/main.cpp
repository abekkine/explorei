#include <version.h>
#include <application.h>
#include <config.h>

void show_version()
{
    printf( "Version: %s\n", VERSION_STRING );
}

int main()
{
    show_version();

    Config* config = Config::GetInstance();
    config->Read( "../conf/explore.conf" );
    config->Dump();
    
    Application* app = new Application();

    if( app->Initialize() ) {

        app->Run();
    }

    delete app;
    delete config;

    return 0;
}
