#include <application.h>

Application::Application()
{
//DEBUG
    puts("Application::Application()");
//END
    Defaults();
}

Application::~Application()
{
//DEBUG
    puts("Application::~Application()");
//END
    delete _display;
    delete _timer;
}

void Application::Defaults()
{
//DEBUG
    puts("Application::Defaults()");
//END
    _config = 0;
    _timer = 0;
    _display = 0;

    _ticks_period = -1.0;
    _time_step = -1.0;
    _quit_condition = false;
}

bool Application::Initialize()
{
//DEBUG
    puts("Application::Initialize()");
//END
    bool result = false;

    _config = Config::GetInstance();
    _timer = new Timer(); 
    _display = new Display();

    result = _display->Init();
    if( result )
    {
        if( _config->application_frequency > 0.0 )
        {
            _ticks_period = 1.0 / _config->application_frequency;
        }
        else
        {
            _ticks_period = 0.0;
        }

        _timer->Reset();

        _time_step = _config->application_timestep;
    }

    return result;
}

void Application::Run()
{
//DEBUG
    puts("Application::Run()");
//END
    while( _quit_condition == false )
    {
        _num_ticks = _timer->GetElapsed();
        if( _num_ticks > _ticks_period )
        {
            _timer->Reset();
        }

        _display->Update();
        
        _quit_condition = _display->CheckQuitCondition();
    }
}
