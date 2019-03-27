#pragma once

#include <iostream>
#include <string>
#include <SDL2\SDL.h>
#include "camera.h"
#include "mouse.h"
#undef main

class Display 
{
public:
	Display(int width, int height, const std::string& title);

	void Update(Mouse &mouse);
	void Clear(float r, float g, float b, float a);
	void Resize();
	bool IsClosed();

	inline SDL_Event GetEvent() { return m_e; }
	inline int &GetWidth() { return m_width; }
	inline int &GetHeight() { return m_height; }

	virtual ~Display();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	SDL_Event m_e;

	int m_width;
	int m_height;
	bool m_isClosed;
};
