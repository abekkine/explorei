#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <vector>

#include <font.h>

class Writer
{
    private:
        // Types and members.
        typedef struct {
            int x;
            int y;
            char type;
            std::string format;
            void * value;
            bool* control;
        } MessageDisplayType;

    private:
        static Writer* _instance;
        Writer();

    public:
        static Writer* GetInstance();
        ~Writer();
        bool Init();
        void UpdateOrigin( int x, int y );
        void Render();
        void Add( std::string text, int x, int y, bool* control );
        void Add( std::string format, int* value, int x, int y, bool* control );
        void Add( std::string format, double* value, int x, int y, bool* control );
        
    private:
        // Methods.
        void Defaults();

    public:
        // Control Members.
        static bool _ready;
        static bool _enable;
        
    private:
        // Members.
        int _origin_x;
        int _origin_y;
        char _text_buffer[256];
        Font* _font;
        MessageDisplayType* _a_message;
        std::vector< MessageDisplayType* > _message_list;
        std::vector< MessageDisplayType* >::iterator _iMessage;
};

#endif
