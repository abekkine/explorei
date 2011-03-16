#ifndef STARS_H
#define STARS_H

class Stars
{
    public:
        Stars();
        ~Stars();
        bool Init();
        void Render();

    private:
        // Methods.
		void RenderTest();
		void RenderStars();

	public:
		// Control Members.
		static bool _ready;
		static bool _enable;

    private:
        // Members.
};

#endif

