#include "TextureManager.h"
#include <SDL_image.h>

TextureManager *TextureManager::instance = nullptr;

TextureManager *TextureManager::getInstance() {

    if (TextureManager::instance == nullptr)
        TextureManager::instance = new TextureManager();

    return TextureManager::instance;
}

SDL_Texture *TextureManager::LoadImage(SDL_Renderer *renderer, const std::string &file) {

    //Todo make loading for any image type with SDL_image

    SDL_Surface *image = SDL_LoadBMP(file.c_str());

    return SDL_CreateTextureFromSurface(renderer, image);
}

void TextureManager::ApplySurface(int x, int y, SDL_Texture *texture, SDL_Renderer *renderer) {

    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    // You can change texture height and wight here
    SDL_QueryTexture(texture, nullptr, nullptr, &pos.w, &pos.h);

    // You can cut part of texture with third param
    SDL_RenderCopy(renderer, texture, nullptr, &pos);

    SDL_RenderPresent(renderer);
}