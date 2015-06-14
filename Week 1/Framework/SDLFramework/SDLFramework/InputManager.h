#ifndef __INPUTMANAGER__
#define __INPUTMANAGER__

#ifdef _WIN32
//define something for Windows
#include <SDL.h>
#else
#ifdef __APPLE__
//define it for a Unix machine
#include <SDL2/SDL.h>
#endif
#endif

#include <vector>
using namespace std;

class InputManager{
private:	
	const Uint8 *mKeyState;
	std::vector<bool> mKeyStates;

	std::vector<SDL_Joystick *> mJoysticks;
	std::vector<std::vector<bool> > mButtonStates;
	std::vector<std::vector<bool> > mHatStates;
	bool mJoysticksAreInitialised;

	InputManager();
	InputManager(InputManager const&);
	void operator=(InputManager const&);
public:
	~InputManager();
	static InputManager &Instance(){
		static InputManager mInstance;
		return mInstance;
	}

	void update();
	void clean();
	bool isKeyDown(SDL_Keycode code);
	bool isKeyUp(SDL_Keycode code);

	void initialiseKeyboard();
	void initialiseJoysticks();
	bool isJoyStickKeyUp(size_t joystick, int buttonNumber);
	bool isJoyStickKeyDown(size_t joystick, int buttonNumber);
	bool isJoyStickHatDown(int joystick, int hatNumber);
	bool joysticksIsInitialized(){
		return mJoysticksAreInitialised;
	}
    void addController(int identifier);
    void removeController(int identifier);

    // Controller members
    int joystickUp();
    int joystickDown();
    int joystickLeft();
    int joystickRight();
    int joystickA();
    int joystickB();
    int joystickX();
    int joystickY();
    int joystickLeftTrigger();
    int joystickRightTrigger();
    int joystickStart();
    int joystickBack();
    int joystickHome();
};

typedef InputManager InputHandler;

#endif