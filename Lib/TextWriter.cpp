#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "TextWriter.h"
#include "TextureManager.h"

TextWriter *TextWriter::instance = nullptr;

TextWriter *TextWriter::getInstance() {

    if (TextWriter::instance == nullptr)
        TextWriter::instance = new TextWriter();

    return TextWriter::instance;
}

void TextWriter::renderText(const std::string& text, int x, int y, SDL_Color color, SDL_Renderer* renderer) {

    if (TTF_Init() < 0)
        throw std::runtime_error("Can not init TTF!");

    TTF_Font* font = TTF_OpenFont("../Fronts/JetBrainsMono-Bold.ttf", 24);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    TextureManager::getInstance()->ApplySurface(x, y, message, renderer);

}