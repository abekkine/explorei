#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL/SDL.h>
#include <GL/gl.h>

#include <definitions.h>
#include <config.h>
#include <writer.h>
#include <panel.h>
#include <event.h>
#include <background.h>
#include <star.h>

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
        void UpdatePanAndZoomOffsets();
        void UpdateViewport();
        void PreRender();
        void Render();
        void PostRender();
        void BackgroundBegin();
        void BackgroundEnd();
        void OrthoBegin();
        void OrthoEnd();
        void CheckError();
        void Reshape();
        void Reshape( int width, int height );
        
        void ResetCommandParam();
        void ProcessCommands();
        void ProcessEvents();
        void ToggleWireframe();
        void ToggleBackground();
        void TogglePanel();

    private:
        // Components.

        // Text writer object.
        Writer* _writer;

        // Display panel.
        Panel* _panel;

        // User events.
        Event* _event;

        // Background layer.
        Background* _background;

        // Star layer.
        Star* _star;

    private:
        // Members

        // Configuration instance.
        Config* _config;

        // Display surface.
        SDL_Surface* _screen;

        // Viewport
        Volume _viewport;
        Volume _viewportBG;
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
        //DEBUG
        float _scaleBG_x;
        float _scaleBG_y;

        // Zoom & Pan
        double _zoom_level;
        //DEBUG
        double _zoom_levelBG;
        int _zoom_delta;
        int _pan_x_delta;
        int _pan_y_delta;

        // Screen center.
        double _center_x;
        double _center_y;
        //DEBUG
        double _centerBG_x;
        double _centerBG_y;
        
        // Quit condition check.
        bool _quit_condition_check;
};

#endif

