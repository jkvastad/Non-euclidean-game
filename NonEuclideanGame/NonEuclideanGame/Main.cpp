#include "Main.h"

int main(int argc, char* argv[]) {
	SDL_Window* main_window;
	init(main_window);

	Model model;
	View view(model);
	Control control(model, view);

	const double dt = 10;
	double accumulatedTime = 0.0;
	double lastTime = SDL_GetTicks();
	double currentTime;

	while (true) {
		currentTime = SDL_GetTicks();
		accumulatedTime += currentTime - lastTime;
		lastTime = currentTime;
		float delta_time = currentTime - lastTime;

		control.handleInput();

		while (accumulatedTime>dt) {
			//timeStepModel(model, dt); // move the model dt time forward
			accumulatedTime -= dt;
		}

		view.render(main_window);
	}

	GLTearDown(main_window);

	return 0;
}