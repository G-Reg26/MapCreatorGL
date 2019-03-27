#include "fpsController.h"

FPSController::FPSController()
{
	m_walkSpeed = 6.0f;
	m_rotSpeed = 5.0f;

	m_pitch = 0.0f;
	m_yaw = Functions::ToRadians(90.0f);
}

void FPSController::Update(Camera & camera,  float & deltaTime, const Uint8 *keyState)
{
	m_dir = Vec3(0.0f, 0.0f, 0.0f);

	m_forward = camera.GetTarget() * Vec3(1.0f, 0.0f, 1.0f);
	m_forward.Normalize();

	m_right = m_forward;
	m_right = m_right.Cross(Vec3(0.0f, -1.0f, 0.0f));
	m_right.Normalize();

	if (keyState[SDL_SCANCODE_W])
	{
		m_dir += m_forward * m_walkSpeed * deltaTime;
	}
	else if (keyState[SDL_SCANCODE_S])
	{
		m_dir -= m_forward * m_walkSpeed * deltaTime;
	}

	if (keyState[SDL_SCANCODE_D])
	{
		m_dir += m_right * m_walkSpeed * deltaTime;
	}
	else if (keyState[SDL_SCANCODE_A])
	{
		m_dir -= m_right * m_walkSpeed * deltaTime;
	}

	if (keyState[SDL_SCANCODE_LEFT])
	{
		m_yaw += m_rotSpeed * deltaTime;
	}
	else if (keyState[SDL_SCANCODE_RIGHT])
	{
		m_yaw -= m_rotSpeed * deltaTime;
	}

	if (keyState[SDL_SCANCODE_UP])
	{
		m_pitch += m_rotSpeed * deltaTime;
	}
	else if (keyState[SDL_SCANCODE_DOWN])
	{
		m_pitch -= m_rotSpeed * deltaTime;
	}

	if (m_pitch >= Functions::ToRadians(90.0f))
	{
		m_pitch = Functions::ToRadians(90.0f);
	}
	else if (m_pitch <= Functions::ToRadians(-90.0f))
	{
		m_pitch = Functions::ToRadians(-90.0f);
	}

	camera.GetTarget().x = cos(m_pitch) * cos(m_yaw);
	camera.GetTarget().y = sin(m_pitch);
	camera.GetTarget().z = cos(m_pitch) * sin(m_yaw);

	camera.GetPos() += m_dir;
}
