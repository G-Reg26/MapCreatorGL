#include "display.h"
#include<GL\glew.h>

Display::Display(int width, int height, const std::string & title)
{
	m_width = width;
	m_height = height;
	
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != glewInit()) 
	{
		std::cerr << "glew failed to initialize" << std::endl;
	}

	m_isClosed = false;

	glEnable(GL_DEPTH_TEST);
}

void Display::Update(Mouse & mouse)
{
	SDL_GL_SwapWindow(m_window);

	while (SDL_PollEvent(&m_e)) 
	{
		if (m_e.type == SDL_QUIT) 
		{
			m_isClosed = true;
		}
		else 
		{
			switch (m_e.type)
			{
				case SDL_WINDOWEVENT:
					switch (m_e.window.event)
					{
						case SDL_WINDOWEVENT_RESIZED:
							Resize();
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					mouse.x =  (m_e.motion.x - (m_width / 2)) * (1.0f / (m_width / 2));
					mouse.y = -(m_e.motion.y - (m_height / 2)) * (1.0f / (m_height / 2));
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch (m_e.button.button) 
					{
						case SDL_BUTTON_LEFT:
							mouse.left_button = true;
							break;
						case SDL_BUTTON_RIGHT:
							mouse.right_button = true;
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch (m_e.button.button)
					{
					case SDL_BUTTON_LEFT:
						mouse.left_button = false;
						break;
					case SDL_BUTTON_RIGHT:
						mouse.right_button = false;
						break;
					default:
						break;
					}
					break;
				default:
					break;
			}
		}
	}
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Resize()
{
	m_width = m_e.window.data1;
	m_height = m_e.window.data2;

	glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
}

bool Display::IsClosed()
{
	return m_isClosed;
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
