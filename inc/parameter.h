#ifndef PARAMETER_H
#define PARAMETER_H

class Parameter
{
    public:
        Parameter();
        ~Parameter();
        bool Init();
        void Render();

    private:
        // Methods
		void RenderTest();
		void RenderParam();

	public:
		// Control Members.
		static bool _ready;
		static bool _enable;

    private:
        // Members
};

#endif

