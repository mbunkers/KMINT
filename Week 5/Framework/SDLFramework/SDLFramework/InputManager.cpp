#include "InputManager.h"
#include <string>
#include <iostream>

using namespace std;

InputManager::InputManager(){
	mKeyState = SDL_GetKeyboardState(nullptr);
	//initialiseJoysticks();
}
InputManager::~InputManager(){

}

void InputManager::update(){
	// Keyboard update
	//

	// Joystick update
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0){
		int controllerIdentifier = event.jaxis.which;
		int buttinIndex = event.jbutton.button;
		//SDL_Scancode code = event.key.keysym.scancode;

		switch (event.type)
		{
			// Map the key state as true
		case SDL_JOYBUTTONDOWN:
			mButtonStates[controllerIdentifier][buttinIndex] = true;
			break;
			// Map the key state as false
		case SDL_JOYBUTTONUP:
			mButtonStates[controllerIdentifier][buttinIndex] = false;
			break;
		case SDL_JOYDEVICEREMOVED:
                removeController(controllerIdentifier);
			break;
		case SDL_JOYDEVICEADDED:
                addController(controllerIdentifier);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			SDL_PumpEvents();
			break;
		default:
			break;
		}
	}
}

void InputManager::clean(){
	if (mJoysticksAreInitialised){
		for (int i = 0; i < SDL_NumJoysticks(); i++){
			SDL_JoystickClose(mJoysticks[i]);
		}
	}
}

bool InputManager::isKeyDown(SDL_Keycode code){
	SDL_Scancode key = SDL_GetScancodeFromKey(code);
	//mKeyState = SDL_GetKeyboardState(nullptr);
	if (mKeyState != 0){
		if (mKeyState[key] == 1){
			return true;
		}
	}
	return false;
}

bool InputManager::isKeyUp(SDL_Keycode code){
	SDL_Scancode key = SDL_GetScancodeFromKey(code);
	//mKeyState = SDL_GetKeyboardState(nullptr);
	if (mKeyState != 0){
		if (mKeyState[key] == 0){
			return true;
		}
	}
	return false;
}

bool InputManager::isJoyStickKeyDown(size_t joystick, int buttonNumber){
	// Check if not joystick(s) are available
	if (mJoysticksAreInitialised == true){
        SDL_Joystick *currentJoystick = mJoysticks[joystick];
        while (!SDL_JoystickGetAttached(currentJoystick)){
            joystick++;
            if (joystick < mJoysticks.size() - 1){
                currentJoystick = mJoysticks[joystick];
            }
            else {
                break;
            }
        }

		if (mButtonStates[joystick][buttonNumber] == true){
			// Set on false if true. It prevents a repeated event
			//mButtonStates[joystick][buttonNumber] = false;
			return true;
		}
	}
	return false;
}

bool InputManager::isJoyStickKeyUp(size_t joystick, int buttonNumber){
	// Check if not joystick(s) are available
	if (mJoysticksAreInitialised == true){
		SDL_Joystick *currentJoystick = mJoysticks[joystick];
		while (!SDL_JoystickGetAttached(currentJoystick)){
			joystick++;
			if (joystick < mJoysticks.size() - 1){
				currentJoystick = mJoysticks[joystick];
			}
			else {
				break;
			}
		}

		if (mButtonStates[joystick][buttonNumber] == false){
			// Set on false if true. It prevents a repeated event
			//mButtonStates[joystick][buttonNumber] = false;
			return true;
		}
	}
	return false;
}

void InputManager::initialiseKeyboard(){
	//if (SDL_GetKeyboardState(nullptr) != 0){
	//	const Uint8 *keys = SDL_GetKeyboardState(nullptr);
	//	for (Uint8 i = 0; i < keys.; i++){

	//	}
	//}
}

void InputManager::addController(int identifier){
    SDL_Joystick *joystick = SDL_JoystickOpen(identifier);
    if (joystick != 0){
        mJoysticks.push_back(joystick);
        std::vector<bool> tempButtons;

        // Store all buttons on theiri index and set their state on false
        for (int j = 0; j < SDL_JoystickNumButtons(joystick); j++){
            tempButtons.push_back(false);
        }
        mButtonStates.push_back(tempButtons);
    }
    SDL_JoystickEventState(SDL_ENABLE);
    mJoysticksAreInitialised = true;
}

void InputManager::removeController(int identifier){
    SDL_Joystick *joystick = mJoysticks[identifier];
    SDL_JoystickClose(joystick);

    size_t controllersConnected = mJoysticks.size();

    for (size_t i = 0; i < mJoysticks.size(); i++){
        SDL_Joystick *joystick = mJoysticks[identifier];
        if (!SDL_JoystickGetAttached(joystick)){
            controllersConnected--;
        }
    }

    if (controllersConnected == 0){
        mJoysticksAreInitialised = false;
    }

    //mJoysticks.erase(mJoysticks.begin() + identifier);
    //mButtonStates.erase(mButtonStates.begin() + identifier);
    //if (mJoysticks.size() == 0){
    //    mJoysticksAreInitialised = false;
    //}
}

void InputManager::initialiseJoysticks(){
	if (SDL_NumJoysticks() > 0){
		// Enable all currently connected joysticks
		for (int i = 0; i < SDL_NumJoysticks(); i++){
			SDL_Joystick *joystick = SDL_JoystickOpen(i);
			if (joystick != 0){
				mJoysticks.push_back(joystick);
				std::vector<bool> tempButtons;

				// Store all buttons on theiri index and set their state on false
				for (int j = 0; j < SDL_JoystickNumButtons(joystick); j++){
					tempButtons.push_back(false);
				}
				mButtonStates.push_back(tempButtons);
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		mJoysticksAreInitialised = true;
	}
	else {
		mJoysticksAreInitialised = false;
	}
}

int InputManager::joystickUp(){
#ifdef _WIN32
    return 0;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_DPAD_UP;
#endif
}

int InputManager::joystickDown(){
#ifdef _WIN32
    return 1;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
#endif
}

int InputManager::joystickLeft(){
#ifdef _WIN32
    return 2;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
#endif
}

int InputManager::joystickRight(){
#ifdef _WIN32
    return 3;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
#endif
}

int InputManager::joystickA(){
#ifdef _WIN32
    return 10;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_A;
#endif
}

int InputManager::joystickB(){
#ifdef _WIN32
    // Needs to be confirmed
    return 11;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_B;
#endif
}

int InputManager::joystickX(){
#ifdef _WIN32
    // Needs to be confirmed
    return 12;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_X;
#endif
}

int InputManager::joystickY(){
#ifdef _WIN32
    // Needs to be confirmed
    return 13;
#endif
#ifdef __APPLE__
    return SDL_CONTROLLER_BUTTON_Y;
#endif
}

int InputManager::joystickLeftTrigger(){
    // Needs to be defined
#ifdef _WIN32
    return 1;
#endif
#ifdef __APPLE__
    return 2;
#endif
}

int InputManager::joystickRightTrigger(){
    // Needs to be defined
#ifdef _WIN32
    return 1;
#endif
#ifdef __APPLE__
    return 2;
#endif
}

int InputManager::joystickStart(){
#ifdef _WIN32
    // Needs to be confirmed
    return 4;
#endif
#ifdef __APPLE__
    return 8;
#endif
}

int InputManager::joystickBack(){
#ifdef _WIN32
    return 4;
#endif
#ifdef __APPLE__
    return 9;
#endif
}

int InputManager::joystickHome(){
    // Needs to be defined
#ifdef _WIN32
    return 1;
#endif
#ifdef __APPLE__
    return 2;
#endif
}

