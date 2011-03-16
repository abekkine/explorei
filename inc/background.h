#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background
{
    public:
        Background();
        ~Background();
        bool Init();
        void Render();

    private:
        // Methods.
		void RenderTest();
		void RenderBackground();

	public:
		static bool _ready;
		static bool _enable;

    private:
        // Members.
};

#endif

