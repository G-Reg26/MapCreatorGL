#pragma once

#include <SDL2\SDL.h>
#include "math.h"
#include "transform.h"

class Camera {
public:
	Camera(const float fov, const float aspect, const float zFar, const float zNear, Vec3 pos, Vec3 target, Vec3 &up) 
	{
		m_pos = pos;
		m_target = target;
		m_up = up;

		m_fov = fov * (PI / 180.0f);

		m_projectionMatrix.matrix[0][0] = 1.0f / (tanf(m_fov / 2) * aspect);
		m_projectionMatrix.matrix[1][1] = 1.0f / (tanf(m_fov / 2));
		m_projectionMatrix.matrix[2][2] = (-zNear - zFar) / (zNear - zFar);
		m_projectionMatrix.matrix[2][3] = (2.0f * zFar * zNear) / (zNear - zFar);
		m_projectionMatrix.matrix[3][2] = 1.0f;
		m_projectionMatrix.matrix[3][3] = 0.0f;
	}

	void Update() 
	{		
		m_cameraTransTransform.matrix[0][3] = -m_pos.x;
		m_cameraTransTransform.matrix[1][3] = -m_pos.y;
		m_cameraTransTransform.matrix[2][3] = -m_pos.z;

		Vec3 n = m_target;
		m_target.Normalize();
		Vec3 u = m_up;
		u = u.Cross(m_target);
		u.Normalize();
		Vec3 v = n.Cross(u);
		
		m_cameraRotTransform.matrix[0][0] = u.x;
		m_cameraRotTransform.matrix[0][1] = u.y;
		m_cameraRotTransform.matrix[0][2] = u.z;
		m_cameraRotTransform.matrix[1][0] = v.x;
		m_cameraRotTransform.matrix[1][1] = v.y;
		m_cameraRotTransform.matrix[1][2] = v.z;
		m_cameraRotTransform.matrix[2][0] = n.x;
		m_cameraRotTransform.matrix[2][1] = n.y;
		m_cameraRotTransform.matrix[2][2] = n.z;
	}

	void LookAt(const Vec3 &target) 
	{
		Vec3 newTarget;

		newTarget.x = target.x - m_pos.x;
		newTarget.y = target.y - m_pos.y;
		newTarget.z = target.z - m_pos.z;

		newTarget.Normalize();

		m_target = newTarget;
	}

	void Follow(const Vec3 &target, const float &maxDistance) 
	{
		Vec3 dir;

		dir.x = target.x - m_pos.x;
		dir.y = 0.0f;
		dir.z = target.z - m_pos.z;

		if (Functions::Distance(target, m_pos) > maxDistance) 
		{
			m_pos += dir.Normalize() * .01f;
		}
	}

	inline Vec3 &GetPos() { return m_pos; }
	inline Vec3 &GetTarget() { return m_target; }
	inline Vec3 &GetUp() { return m_up; }

	Mat4 &GetProjectionMatrix() { return m_projectionMatrix * m_cameraRotTransform *  m_cameraTransTransform; }

private:
	Mat4 m_projectionMatrix;
	Mat4 m_cameraTransTransform;
	Mat4 m_cameraRotTransform;

	Vec3 m_pos;
	Vec3 m_up;
	Vec3 m_target;

	float m_fov;
};