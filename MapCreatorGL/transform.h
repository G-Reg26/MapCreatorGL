#pragma once

#include "math.h"

class Transform {
public:
	Transform(const Vec3& pos = Vec3(), const Vec3& rot = Vec3(), const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) 
	{
	}

	Mat4 GetModel() 
	{
		Translate();
		Rotate();
		Scale();

		return  translateMat * rotMat * scaleMat;
	}

	void Translate() 
	{
		translateMat.matrix[0][3] = m_pos.x;
		translateMat.matrix[1][3] = m_pos.y;
		translateMat.matrix[2][3] = m_pos.z;
	}

	void Scale() 
	{
		scaleMat.matrix[0][0] = m_scale.x;
		scaleMat.matrix[1][1] = m_scale.y;
		scaleMat.matrix[2][2] = m_scale.z;
	}

	void Rotate() 
	{
		rotXMat.matrix[1][1] = cosf(m_rot.x);
		rotXMat.matrix[1][2] = -sinf(m_rot.x);
		rotXMat.matrix[2][1] = sinf(m_rot.x);
		rotXMat.matrix[2][2] = cosf(m_rot.x);


		rotYMat.matrix[0][0] = cosf(m_rot.y);
		rotYMat.matrix[0][2] = sinf(m_rot.y);
		rotYMat.matrix[2][0] = -sinf(m_rot.y);
		rotYMat.matrix[2][2] = cosf(m_rot.y);

		rotZMat.matrix[0][0] = cosf(m_rot.z);
		rotZMat.matrix[0][1] = -sinf(m_rot.z);
		rotZMat.matrix[1][0] = sinf(m_rot.z);
		rotZMat.matrix[1][1] = cosf(m_rot.z);

		rotMat = rotXMat * rotYMat * rotZMat;
	}

	inline Vec3& GetPos() { return m_pos; }
	inline Vec3& GetRot() { return m_rot; }
	inline Vec3& GetScale() { return m_scale; }
	inline Mat4& GetRotMat() { return rotMat; }
	inline Mat4& GetPosMat() { return translateMat; }

	inline void SetPos(const Vec3& pos) { m_pos = pos; }
	inline void SetRot(const Vec3& rot) { m_rot = Functions::ToRadians(rot); }
	inline void SetScale(const Vec3& scale) { m_scale = scale; }

private:
	Vec3 m_pos;
	Vec3 m_rot;
	Vec3 m_scale;

	Mat4 translateMat;
	Mat4 scaleMat;

	Mat4 rotXMat;
	Mat4 rotYMat;
	Mat4 rotZMat;
	Mat4 rotMat;
};