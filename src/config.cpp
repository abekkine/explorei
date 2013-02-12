#include <stdlib.h>
#include <string.h>

#include <config.h>

Config* Config::_instance = NULL;

Config* Config::GetInstance()
{
    if( _instance == NULL )
    {
        _instance = new Config();
    }

    return _instance;
}

Config::Config()
{
//DEBUG
    puts("Config::Config()");
//END
    Init();
    Defaults();
}

Config::~Config()
{
    // TODO :
//DEBUG
    puts("Config::~Config()");
//END
//    delete [] background_fill_method;
}

bool Config::Read( std::string configFile )
{
    bool result = false;

    _configFile = configFile;

    if( config_read_file( &_config, _configFile.c_str() ) )
    {
        ReadApplication();
        ReadBackground();
        ReadGenerator();
        ReadDisplay();

        config_destroy( &_config );
    }
    else
    {
        config_error_t error_type;
        error_type = config_error_type( &_config );

        if( error_type == CONFIG_ERR_FILE_IO )
        {
            fprintf( stderr, "\nConfig File Error.\n\n" );
        }
        else
        {
            fprintf( stderr, "%s:%d - %s\n",
                config_error_file( &_config ),
                config_error_line( &_config ),
                config_error_text( &_config ) );
        }

        config_destroy( &_config );

        exit( 1 );
    }

    return result;
}

void Config::Init()
{
    config_init( &_config );
}

void Config::Defaults()
{
	// Application
	application_frequency = 20;
	application_timestep = 1.0;

	// Background
	background_tile_size = 0.1;
	background_tile_delta = 0.01;
//	background_fill_method_ptr = NULL;
	background_fill_method = NULL;
	
	// Background Offsets
	background_offset_delta = 0.01;
	background_red_offset = 0.0;
	background_green_offset = 0.0;
	background_blue_offset = 0.0;

	// Generator
	generator_octaves = 1;

	// Display Screen
	display_screen_width = 512;
	display_screen_height = 512;

	// Display World
	display_world_width = 1.0;
	display_world_height = 1.0;

	// Display Color
	display_background_red = 0.0;
	display_background_green = 0.0;
	display_background_blue = 0.0;
}

void Config::ReadApplication()
{
    _setting = config_lookup( &_config, "config.application" );
    if( _setting != NULL )
    {
        config_setting_lookup_float( _setting, "frequency", &application_frequency );
        config_setting_lookup_float( _setting, "timestep", &application_timestep );
    }
}

void Config::ReadBackground()
{
    _setting = config_lookup( &_config, "config.background" );
    if( _setting != NULL )
    {
        config_setting_lookup_float( _setting, "size", &background_tile_size );
        config_setting_lookup_float( _setting, "size_delta", &background_tile_delta );
//        config_setting_lookup_string( _setting, "fill_method", &background_fill_method_ptr );

//        background_fill_method = new char[ 1 + strlen( background_fill_method_ptr ) ];
//        strcpy( background_fill_method, background_fill_method_ptr );

        ReadBackgroundOffsets();
    }
	else
	{
//		background_fill_method = new char[ strlen( "corner" ) ];
//		strcpy( background_fill_method, "corner" );
	}
}

void Config::ReadBackgroundOffsets()
{
    _setting = config_lookup( &_config, "config.background.offset" );
    if( _setting != NULL )
    {
        config_setting_lookup_float( _setting, "delta", &background_offset_delta );
        config_setting_lookup_float( _setting, "red", &background_red_offset );
        config_setting_lookup_float( _setting, "green", &background_green_offset );
        config_setting_lookup_float( _setting, "blue", &background_blue_offset );
    }
}

void Config::ReadGenerator()
{
    _setting = config_lookup( &_config, "config.generator" );
    if( _setting != NULL )
    {
        config_setting_lookup_int( _setting, "octaves", &generator_octaves );
    }

}

void Config::ReadDisplay()
{
    _setting = config_lookup( &_config, "config.display" );
    if( _setting != NULL )
    {
        ReadDisplayScreen();
        ReadDisplayWorld();
        ReadDisplayColor();
    }
}

void Config::ReadDisplayScreen()
{
    _setting = config_lookup( &_config, "config.display.screen" );
    if( _setting != NULL )
    {
        config_setting_lookup_int( _setting, "width", &display_screen_width );
        config_setting_lookup_int( _setting, "height", &display_screen_height );
    }
}

void Config::ReadDisplayWorld()
{
    _setting = config_lookup( &_config, "config.display.world" );
    if( _setting != NULL )
    {
        config_setting_lookup_float( _setting, "width", &display_world_width );
        config_setting_lookup_float( _setting, "height", &display_world_height );
    }
}

void Config::ReadDisplayColor()
{
    _setting = config_lookup( &_config, "config.display.bg" );
    if( _setting != NULL )
    {
        config_setting_lookup_float( _setting, "red", &display_background_red );
        config_setting_lookup_float( _setting, "green", &display_background_green );
        config_setting_lookup_float( _setting, "blue", &display_background_blue );
    }
}

void Config::Dump()
{
    // Configuration items.
    puts( "Configuration Dump:" );
    // Application settings.
    puts( "  Application:" );
    printf( "    application_frequency = %f\n", application_frequency );
    printf( "    application_timestep = %f\n", application_timestep );
    // Background settings.
    puts( "  Background:" );
    printf( "    background_tile_size = %f\n", background_tile_size );
    printf( "    background_tile_delta = %f\n", background_tile_delta );
    printf( "    background_red_offset = %f\n", background_red_offset );
    printf( "    background_green_offset = %f\n", background_green_offset );
    printf( "    background_blue_offset = %f\n", background_blue_offset );
    printf( "    background_offset_delta = %f\n", background_offset_delta );
//    printf( "    background_fill_method = \"%s\"\n", background_fill_method );
    // Generator settings.
    puts( "  Generator:" );
    printf( "    generator_octaves = %d\n", generator_octaves );
    // Display settings.
    puts( "  Display:" );
    printf( "    display_screen_width = %d\n", display_screen_width );
    printf( "    display_screen_height = %d\n", display_screen_height );
    printf( "    display_world_width = %f\n", display_world_width );
    printf( "    display_world_height = %f\n", display_world_height );
    printf( "    display_background_red = %f\n", display_background_red );
    printf( "    display_background_green = %f\n", display_background_green );
    printf( "    display_background_blue = %f\n", display_background_blue );
}
