#ifndef VIEW
#define VIEW

#include "SDL.h"
#include "Model.h"
#include "glew.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

class View {
private:
	GLuint triangle_settings;
	GLuint triangle_buffer;
	GLuint color_buffer;
	GLuint shader_program;
	GLuint vertex_shader;
	GLuint fragment_shader;

	Model& model;
public:
	View(Model& model);
	~View();
	void render(SDL_Window* window);
};

//
//Utilities
//
GLuint LoadShader(std::string shader_file_name, GLenum shader_type);
void CheckLinkStatus(GLuint& shader_program);
#endif