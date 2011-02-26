#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL/SDL.h>
#include <GL/gl.h>

#include <definitions.h>
#include <config.h>
#include <texture.h>
#include <writer.h>
#include <panel.h>
#include <event.h>
#include <background.h>
#include <dust.h>
#include <stars.h>
#include <parameter.h>

//! @brief Class responsible for rendering objects.
class Display
{
    public:
        //! @brief Constructor.
        Display();
        //! @brief Destructor.
        ~Display();
        //! @brief Initialization method.
        bool Init();
        //! @brief Update method.
        void Update();
        //! @brief Checks quit condition.
        bool CheckQuitCondition();

    private:
        // Methods
        void Defaults();
        void InitGL();
        void InitComponents();
        void UpdateViewport();
        void UpdateScale();
        void PreRender();
        void Render();
        void PostRender();
        void OrthoBegin();
        void OrthoEnd();
        void CheckError();
        void Reshape();
        void Reshape( int width, int height );
        
        void ResetCommandParam();
        void ProcessCommands();
        void ProcessEvents();
        void NextParameter();
        void PrevParameter();
        void NextValue();
        void PrevValue();
        void ToggleBackground();
        void ToggleStars();
        void ToggleDust();
        void TogglePanel();
        void ToggleFontTest();
        void ToggleFPS();
        void ToggleParamDisplay();
        void ToggleWireframe();

        void VersionMessage();

    private:
        // Components.

        // Texture object.
        Texture* _texture;
        bool _texture_ready;
        bool _texture_enable;

		// Text writer object.
		Writer* _writer;
		bool _writer_ready;
		bool _writer_enable;

        // Display panel.
        Panel* _panel;
        bool _panel_ready;
        bool _panel_enable;

        // User events.
        Event* _event;
        bool _event_ready;
        bool _event_enable;

        // Background layer.
        Background* _background;
        bool _background_ready;
        bool _background_enable;

        // Space dust layer.
        Dust* _dust;
        bool _dust_ready;
        bool _dust_enable;

        // Stars layer.
        Stars* _stars;
        bool _stars_ready;
        bool _stars_enable;

        // User accessible parameters.
        Parameter* _param;
        bool _param_ready;
        bool _param_enable;

    private:
        // Members

        // Configuration instance.
        Config* _config;

        // Display surface.
        SDL_Surface* _screen;

        // Viewport
        Volume _viewport;
        // Viewport screen dimensions.
        int _screen_width;
        int _screen_height;
        // Viewport world dimensions.
        double _world_width;
        double _world_height;

        // Background color settings.
        float _background_red;
        float _background_green;
        float _background_blue;
        float _background_alpha;

        // Real world / Screen Scaling.
        float _scale_x;
        float _scale_y;

        // Zoom & Pan
        double _zoom_level;
        int _zoom_delta;
        int _pan_x_delta;
        int _pan_y_delta;

        // Screen center.
        double _center_x;
        double _center_y;
        
        // Quit condition check.
        bool _quit_condition_check;
};

#endif

