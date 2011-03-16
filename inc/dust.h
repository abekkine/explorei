#ifndef DUST_H
#define DUST_H

class Dust
{
    public:
        Dust();
        ~Dust();
        bool Init();
        void Render();

    private:
        // Methods
		void RenderTest();
		void RenderDust();

	public:
		// Control Members.
		static bool _ready;
		static bool _enable;

    private:
        // Members
};

#endif

