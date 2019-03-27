#include <iostream>
#include <GL\glew.h>
#include <list>

#include "display.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "texture.h"
#include "map.h"
#include "wall.h"
#include "fpsController.h"

const Uint8 *keyState = SDL_GetKeyboardState(NULL);

GLuint uniform[1];

Display display(1200, 600, "MapCreatorGL");

Shader shader("./res/basicShader", uniform);

Camera camera(60.0f, display.GetWidth()/display.GetHeight(), 100.0f, 1.0f, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f));

Mouse mouse;

Map map(50.0f, 2.0f, 0.0f, uniform);

FPSController controller;

std::list<Wall*> walls;

float oldTime =		SDL_GetTicks();
float newTime =		0.0f;
float deltaTime =	0.0f;

int main() 
{
	// set camera height
	camera.GetPos().y = 2.25f;

	// map is being set up on start up
	map.SettingUpMap() = true;

	// player's location on map
	map.CameraPoint() = Point(Vec2(camera.GetPos().x, camera.GetPos().z));
	// line that illustrates which direction the user is looking at
	map.CameraLine() = Line(Vec2(camera.GetPos().x, camera.GetPos().z), Vec2(camera.GetTarget().x, camera.GetTarget().z));

	while (!display.IsClosed()) 
	{
		newTime = SDL_GetTicks();
		deltaTime = (newTime - oldTime) / 1000.0f;
		oldTime = newTime;

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// IF map is being set up
		if (map.SettingUpMap()) 
		{
			display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

			if (!map.IsGenerating()) 
			{
				map.Update(mouse, keyState);

				// SET camera map point
				map.CameraPoint().GetTransform().SetPos(Vec3(camera.GetPos().x / 25.0f, camera.GetPos().z / 25.0f, 0.0f));

				// SET camera line map points
				map.CameraLine().GetVerts()[0] = camera.GetPos().x / 25.0f;
				map.CameraLine().GetVerts()[1] = camera.GetPos().z / 25.0f;
				
				map.CameraLine().GetVerts()[2] = (camera.GetPos().x + camera.GetTarget().x) / 25.0f;
				map.CameraLine().GetVerts()[3] = (camera.GetPos().z + camera.GetTarget().z) / 25.0f;

				map.Draw(uniform);
			}
			else
			{
				map.Generate(walls);
			}
		}
		else
		{
			display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

			shader.Bind();

			camera.Update();

			// IF ESCAPE key is pressed
			if (keyState[SDL_SCANCODE_ESCAPE])
			{
				// map is being set up
				map.SettingUpMap() = true;

				// DELETE all wall and floor objects
				for (std::list<Wall*>::iterator it = walls.begin(); it != walls.end(); it++)
				{
					delete (*it);
				}

				// CLEAR walls and floors list
				walls.clear();
			}
			else
			{
				for (std::list<Wall*>::iterator it = walls.begin(); it != walls.end(); it++)
				{
					(*it)->Draw(camera, uniform);
				}
			}
		}

		// update camera position
		controller.Update(camera, deltaTime, keyState);

		display.Update(mouse);
	}

	return 0;
}