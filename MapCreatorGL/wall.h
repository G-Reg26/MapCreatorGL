#pragma once

#include<GL\glew.h>

#include "math.h"
#include "mesh.h"
#include "transform.h"
#include "texture.h"
#include "camera.h"

class Wall 
{
public:
	Wall(Vec2 &corner1, Vec2 &corner2, float &ceiling, float &floor);

	void Draw(Camera &camera, GLuint * uniforms);

	inline Transform &GetTransform() { return m_transform; }

private:
	Vertex m_verts[4];

	unsigned int m_indicies[6] =
	{
		1, 2, 3,
		3, 0, 1,
	};

	Mesh m_mesh;
	Texture m_texture;
	Transform m_transform;
};