#pragma once

#include <SDL2\SDL.h>
#include "camera.h"

class FPSController 
{
public:
	FPSController();

	void Update(Camera &camera, float &deltaTime, const Uint8 *keyState);

private:
	Vec3 m_dir;

	Vec3 m_forward;
	Vec3 m_right;

	float m_pitch;
	float m_yaw;
	
	float m_walkSpeed;
	float m_rotSpeed;
};