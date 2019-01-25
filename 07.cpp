#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Initializes the window
bool init();

//Loades the media
bool loadMedia();

//Closes the window
void close();

//Loads individual surfaces
SDL_Surface* loadSurface(std::string path);

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//We will render to this window
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//The surface will go in the window
SDL_Surface* gScreenSurface = NULL;

//The image will be contained here
SDL_Surface* gImageSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL)
		{
			printf("Window could not be created: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL)
			{
				printf("Could not create renderer, SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Init renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Init PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				//Note: a different method of rendering is used between the previous tutorial and this one
			}
		}
	}

	return success;
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("Could not load image %s, SDL Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL)
		{
			printf("Could not create texture from %s, SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of the old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

bool load_media()
{
	//Loading flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture("images/texture.png");
	if(gTexture == NULL)
	{
		printf("Unable to load texture image: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

void close()
{
	//Deallocate texture
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("Unable to load image %s, SDL ERROR: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if(optimizedSurface == NULL)
		{
			printf("Unable to optimize surface, SDL Error: %s\n", SDL_GetError());
		}
		//Get rid of the old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


int main(int argc, char* args[])
{
	//Start SDL and create window
	if(!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if(!load_media())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			//Main loop flag
			bool quit = false;

			//SDL Event Handler
			SDL_Event e;

			//While application is running
			while(!quit)
			{
				//Handle events on a queue
				while(SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				
				//Clear screen
				SDL_RenderClear(gRenderer);

				//Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close the window
	close();

	return 0;
}

