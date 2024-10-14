#include "Utility.h"


void play_sound(const char* filename) {
	
    // local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	
	// Load the WAV
	// the specs, length and buffer of our wav are filled
    // check if the file is loaded
	if( SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL ){
        printf("Failed to load wav file: %s\n", SDL_GetError());
	    SDL_FreeWAV(wav_buffer);
	}
	
    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);
    if (success != 0) {
        fprintf(stderr, "Failed to queue audio: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);
    }
    SDL_PauseAudioDevice(deviceId, 0);
    // keep application running long enough to hear the sound
    
    // wait for sound to finish
    SDL_Delay(300);

    // clean up
    SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wav_buffer);

}


void createGaussianKernel(float* kernel, int radius) {
    
    float sigma = radius / 2.0f;
    float sigmaSq = 2.0f * sigma * sigma;
    float sum = 0.0f;

    for (int i = -radius; i <= radius; ++i) {
        kernel[i + radius] = exp(-(i * i) / sigmaSq);
        sum += kernel[i + radius];
    }

    // Normalize the kernel
    for (int i = 0; i < 2 * radius + 1; ++i) {
        kernel[i] /= sum;
    }

}


void applyHorizontalBlur(Uint32* pixels, Uint32* tempPixels, int width, int height, float* kernel, int radius) {
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0, g = 0, b = 0, a = 0;

            for (int k = -radius; k <= radius; ++k) {
                int nx = x + k;
                if (nx >= 0 && nx < width) {
                    Uint32 pixel = pixels[y * width + nx];
                    SDL_Color color;
                    SDL_GetRGBA(pixel, SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), &color.r, &color.g, &color.b, &color.a);

                    float weight = kernel[k + radius];

                    r += color.r * weight;
                    g += color.g * weight;
                    b += color.b * weight;
                    a += color.a * weight;
                }
            }

            tempPixels[y * width + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
        }
    }

}


void applyVerticalBlur(Uint32* tempPixels, Uint32* pixels, int width, int height, float* kernel, int radius) {
    
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float r = 0, g = 0, b = 0, a = 0;

            for (int k = -radius; k <= radius; ++k) {
                int ny = y + k;
                if (ny >= 0 && ny < height) {
                    Uint32 pixel = tempPixels[ny * width + x];
                    SDL_Color color;
                    SDL_GetRGBA(pixel, SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), &color.r, &color.g, &color.b, &color.a);

                    float weight = kernel[k + radius];

                    r += color.r * weight;
                    g += color.g * weight;
                    b += color.b * weight;
                    a += color.a * weight;
                }
            }

            pixels[y * width + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
        }
    }

}


void applyBlur(SDL_Renderer* renderer, int width, int height, int radius) {
    
    SDL_Texture* blurred_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
    if (blurred_texture == NULL) {
        printf("blurred_texture creation failed: %s\n", SDL_GetError());
        return;
    }
    SDL_SetRenderTarget(renderer, blurred_texture);
    SDL_RenderCopy(renderer, blurred_texture, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);

    // Create Gaussian kernel
    float* kernel = (float*)malloc((2 * radius + 1) * sizeof(float));
    createGaussianKernel(kernel, radius);

    // Allocate pixel arrays
    Uint32* pixels = (Uint32*)malloc(width * height * sizeof(Uint32));
    Uint32* tempPixels = (Uint32*)malloc(width * height * sizeof(Uint32));
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, pixels, width * sizeof(Uint32));

    // Apply horizontal and vertical blur
    applyHorizontalBlur(pixels, tempPixels, width, height, kernel, radius);
    applyVerticalBlur(tempPixels, pixels, width, height, kernel, radius);

    // Update the texture with blurred pixels
    SDL_UpdateTexture(blurred_texture, NULL, pixels, width * sizeof(Uint32));

    // Free allocated memory
    free(pixels);
    free(tempPixels);
    free(kernel);
    SDL_RenderCopy(renderer, blurred_texture, NULL, NULL);

}


void add_image_to_render(const char* filename, SDL_Renderer* renderer, SDL_Rect destRect) {
    
    // Load the BMP image
    SDL_Surface* image = IMG_Load(filename);
    if (!image) {
        printf("Image loading failed: %s\n", IMG_GetError());
        goto Quit; // If the image failed to load, exit the function
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    // Check if the texture was created successfully
    if (!texture) {
        printf("Texture creation failed: %s\n", SDL_GetError());
        SDL_DestroyTexture(texture);
        goto Quit;
    }

    // Copy the texture to the renderer with destination rectangle
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    // Free surface and texture
    SDL_DestroyTexture(texture);
Quit:
    SDL_FreeSurface(image);

}


void Draw_the_red_boundary_move_Rect(SDL_Renderer* renderer, SDL_Rect draw_red_boundary_move){
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    SDL_RenderDrawRect(renderer, &draw_red_boundary_move); 
    // we draw the line around the piece 
    // we wanted to make it thicker so here is a way to do it, don't know if it's the best way
    // Draw top line
    for (int i = 0; i < 5; ++i) {
        SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + i);
    }
    // Draw right line
    for (int i = 0; i < 5; ++i) {
        SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y, draw_red_boundary_move.x + draw_red_boundary_move.w - i, draw_red_boundary_move.y + draw_red_boundary_move.h);
    }
    // Draw bottom line
    for (int i = 0; i < 5; ++i) {
        SDL_RenderDrawLine(renderer, draw_red_boundary_move.x, draw_red_boundary_move.y + draw_red_boundary_move.h - i, draw_red_boundary_move.x + draw_red_boundary_move.w, draw_red_boundary_move.y + draw_red_boundary_move.h - i);
    }
    // Draw left line
    for (int i = 0; i < 5; ++i) {
        SDL_RenderDrawLine(renderer, draw_red_boundary_move.x + i, draw_red_boundary_move.y, draw_red_boundary_move.x + i, draw_red_boundary_move.y + draw_red_boundary_move.h);
    }

}


void Draw_Filled_Circle(SDL_Renderer *renderer, int center_col, int center_row, int radius) {
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to red
    int x, y, dl;
    for (y = -radius; y <= radius; y++) {
        dl = (int)sqrt(radius * radius - y * y);
        for (x = -dl; x <= dl; x++) {
            SDL_RenderDrawPoint(renderer, center_col + x, center_row + y);
        }
    }

}


void add_font_to_render(SDL_Renderer* renderer, const char* text, int font_size, SDL_Color textColor, int width_of_middle_of_text, int heigth_of_middle_of_text){
    
    // Load font
    TTF_Font* font = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", font_size);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create text surface and texture
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }
    SDL_FreeSurface(textSurface);

    // Add the text to the render at the given position
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {width_of_middle_of_text-divide_by_two(textWidth), heigth_of_middle_of_text-divide_by_two(textHeight), textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

}


bool is_point_in_rect(int x, int y, SDL_Rect rect){
    
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);

}


int min (int a, int b){
    
    if (a < b){
        return a;
    }
    return b;

}


int max (int a, int b){

    if (a > b){
        return a;
    }
    return b;

}


static unsigned int seed;  // Initialize without a specific seed
static const unsigned int a = 1664525;
static const unsigned int long c = 1013904223;
static const unsigned int long m = 4294967296;  // 2^32


void set_seed() {

    // Use current time to initialize seed
    seed = (unsigned int)(time(NULL) ^ getpid());

}


unsigned int custom_rand() {
    
    seed = (a * seed + c) % m;  // Update seed using LCG formula
    return seed;

}


int random_int(int min, int max) {
    
    return min + custom_rand() % (max - min + 1);
    
}


int int_clamp(int value, int min, int max) {
    
    if (value < min) return min;
    if (value > max) return max;
    return value;

}


float float_clamp(float value, float min, float max) {
    
    if (value < min) return min;
    if (value > max) return max;
    return value;

}


int get_rank(int square){
    
    return square >> 3; // could be written as square / 8, using the bit shift operator is faster

}


int get_file(int square){
    
    return square & 0x07; // could be written as square % 8, using the bitwise AND operator is faster

}


int get_index(int rank, int file){
    
    return (rank << 3) | file; // could be written as rank * 8 + file, using the bit shift operator is faster

}


int divide_by_two(int number) {
    
    return number >> 1;  // could be written as number / 2, using the bit shift operator is faster

}
