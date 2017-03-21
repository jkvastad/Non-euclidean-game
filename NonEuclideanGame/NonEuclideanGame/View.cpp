#include "View.h"

View::View(Model& model) :model(model) {
	glEnable(GL_DEPTH_TEST);

	vertex_shader = LoadShader(std::string("GLSL/vertex_shader.txt"), GL_VERTEX_SHADER);
	fragment_shader = LoadShader(std::string("GLSL/fragment_shader.txt"), GL_FRAGMENT_SHADER);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);

	glBindFragDataLocation(shader_program, 0, "color_out");
	glAttachShader(shader_program, fragment_shader);

	glLinkProgram(shader_program);
	CheckLinkStatus(shader_program);

	glDetachShader(shader_program, vertex_shader);
	glDetachShader(shader_program, fragment_shader);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glUseProgram(shader_program);


	glGenVertexArrays(1, &triangle_settings);
	glBindVertexArray(triangle_settings);

	float triangle_data[] = {
		-0.5, -0.5, 0, 1.0, 0, 0,
		0.5, -0.5, 0, 0, 1.0, 0,
		0.5,  0.5, 0, 0, 0, 1.0
	};

	//create vertex buffer object, get a handle to the buffer, load triangle vertices into the buffer
	glGenBuffers(1, &triangle_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);

	//get a handle to the "vertex_position" input attribute, tell it to read 3 floats at a time
	GLint vertex_position_attribute = glGetAttribLocation(shader_program, "vertex_position");
	glVertexAttribPointer(vertex_position_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(vertex_position_attribute);

	//get a handle to the "color_input" input attribute, tell it to read 3 floats at a time
	GLint color_in_attribute = glGetAttribLocation(shader_program, "color_input");
	glVertexAttribPointer(color_in_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(color_in_attribute);
}

View::~View() {
}

void View::render(SDL_Window* window) {
	glClearColor(model.background_color[0],
		model.background_color[1], model.background_color[2], model.background_color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();

	SDL_GL_SwapWindow(window);
}


GLuint LoadShader(std::string shader_file_name, GLenum shader_type) {
	std::ifstream my_stream(shader_file_name);
	std::string contents = std::string((std::istreambuf_iterator<char>(my_stream)), std::istreambuf_iterator<char>());
	const GLchar* shader_code = contents.c_str();

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_code, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		std::cout << "shader compile error in: " << shader_file_name << std::endl;
		char buffer[512];
		glGetShaderInfoLog(shader, 512, nullptr, buffer);
		std::cout << buffer << std::endl;
	}
	return shader;
}

void CheckLinkStatus(GLuint& shader_program) {
	GLint link_status;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE) {
		std::cout << "shader linker error in View constructor" << std::endl;
		char buffer[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, buffer);
	}
}