#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include "InputManager.h"

#ifdef __APPLE__
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#else
#include <SDL_events.h>
#include <SDL_timer.h>
#endif


#include <time.h>

int main(int argc, char *args[]){
	srand((int)time(0));
	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}

	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));
	

	//while (true){}
	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				application->handleEvent(event.key.keysym.sym);
			}
		}

		application->UpdateGameObjects();
		application->RenderGameObjects();
		
		application->SetColor(Color(0, 0, 0, 255));
		//application->DrawText("Welcome to KMint", 800 / 2, 600 / 2);
	
		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->EndTick();
	}
		
	return EXIT_SUCCESS;
}