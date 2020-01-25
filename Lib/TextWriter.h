#ifndef SAPER_TEXTWRITER_H
#define SAPER_TEXTWRITER_H


#include <string>
#include <SDL_render.h>

class TextWriter {

public:
    static TextWriter *getInstance();
    void renderText(const std::string& text, int x, int y, SDL_Color color, SDL_Renderer* renderer);

private:
    static TextWriter *instance;

};


#endif //SAPER_TEXTWRITER_H
