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

    app->Initialize();

    app->Run();

    return 0;
}
