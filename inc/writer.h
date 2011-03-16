#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <vector>

#include <font.h>

class Writer
{
    public:
        // Types and members.
        typedef struct {
            int x;
            int y;
            std::string text;
			bool* control;
            bool internal;
        } MessageDisplayType;

	private:
		static Writer* _instance;
		Writer();

    public:
        static Writer* GetInstance();
        ~Writer();
        bool Init();
        void Render();
        void AddStatic( int x, int y, std::string text );
        void AddDynamic( MessageDisplayType* message );
        
    private:
        // Methods.
        void Defaults();

	public:
		// Control Members.
		static bool _ready;
		static bool _enable;
        
    private:
        // Members.
        Font* _font;
        MessageDisplayType* _a_message;
        std::vector< MessageDisplayType* > _message_list;
        std::vector< MessageDisplayType* >::iterator _iMessage;
};

#endif
