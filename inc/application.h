#ifndef APPLICATION_H
#define APPLICATION_H

#include <config.h>
#include <timer.h>
#include <display.h>

//! @brief Holds everything regarding the application.
class Application
{
    public:
        //! @brief Constructor.
        Application();
        //! @brief Destructor.
        ~Application();
        //! Startup initialization.
        bool Initialize();
        //! Main application loop.
        void Run();

    private:
        // Methods
        void Defaults();

    private:
        // Members
        Config* _config;
        Timer* _timer;
        Display* _display;

        float _ticks_period;
        float _time_step;
        float _num_ticks;
        bool _quit_condition;
};

#endif

