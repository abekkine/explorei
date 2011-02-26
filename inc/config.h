#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <libconfig.h>

//! @brief Configuration class to handle config files.
class Config
{
    private:
        static Config* _instance;
        Config();

    public:
        //! @brief Returns instance of configuration class.
        static Config* GetInstance();
        //! @brief Desctructor.
        ~Config();
        //! @brief Read and parse contents of the given config file.
        //! TBD :
        //! @param[in] configFile String configuration file name.
        bool Read( std::string configFile );
        //! @brief Simple debug function to list configuration items.
        void Dump();

    private:
        // Methods
        void Defaults();
        void Init();
        void ReadApplication();
        void ReadBackground();
        void ReadBackgroundOffsets();
        void ReadGenerator();
        void ReadDisplay();
        void ReadDisplayScreen();
        void ReadDisplayWorld();
        void ReadDisplayColor();

    private:
        // Members
        std::string _configFile;
        config_t _config;
        config_setting_t* _setting;

    public:
        // Configuration items.
        // Application settings.
        //! Application running frequency.
        double application_frequency;
        //! Execution step length of application.
        double application_timestep;
        // Background settings.
        //! Unit size for background triangular mesh.
        double background_tile_size;
        //! Background tile increment/decrement step size.
        double background_tile_delta;
        //! Background color red offset value for perlin noise generation.
        double background_red_offset;
        //! Background color green offset value for perlin noise generation.
        double background_green_offset;
        //! Background color blue offset value for perlin noise generation.
        double background_blue_offset;
        //! Increment/Decrement delta value for color offsets.
        double background_offset_delta;
        //! Fill method string pointer.
        const char* background_fill_method_ptr;
        //! Fill method string value.
        char* background_fill_method;
        // Generator settings.
        //! Perlin noise octave value for noise generation.
        int generator_octaves;
        // Display settings.
        //! Display screen width.
        int display_screen_width;
        //! Display screen height.
        int display_screen_height;
        //! Width of the world projected to screen.
        double display_world_width;
        //! Height of the world projected to screen.
        double display_world_height;
        //! Background color red component.
        double display_background_red;
        //! Background color green component.
        double display_background_green;
        //! Background color blue component.
        double display_background_blue;

};

#endif

