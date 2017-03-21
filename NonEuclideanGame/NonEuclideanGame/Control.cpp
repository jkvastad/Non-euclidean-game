#include "Control.h"

Control::Control(Model& model, View& view) :model(model), view(view) {
	key_state = SDL_GetKeyboardState(nullptr);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Control::handleInput() {
	SDL_Event Event;
	while (SDL_PollEvent(&Event)) {
	}

	if (key_state[SDL_SCANCODE_R]) { model.background_color = std::vector<double>{ 1,0,0,1 }; }
	if (key_state[SDL_SCANCODE_G]) { model.background_color = std::vector<double>{ 0,1,0,1 }; }
	if (key_state[SDL_SCANCODE_B]) { model.background_color = std::vector<double>{ 0,0,1,1 }; }
}