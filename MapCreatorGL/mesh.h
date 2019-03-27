#pragma once

#include <gl\glew.h>
#include "math.h"
#include "transform.h"
#include "camera.h"

struct Vertex 
{
	Vertex() 
	{
	}

	Vertex(Vec3 pos)
	{
		m_pos = pos;
		m_tex = Vec2(0.0f, 0.0f);
	}

	Vertex(Vec3 pos, Vec2 tex) 
	{
		m_pos = pos;
		m_tex = tex;
	}

	Vec3 m_pos;
	Vec2 m_tex;
};

class Mesh
{
public:
	Mesh();
	Mesh(Vertex * verticies, unsigned int * indicies, unsigned int vertexSize, unsigned int indexSize, unsigned int triCount);

	void Draw(GLuint * uniforms, Camera &camera, Transform &transform);
	void DrawDot(GLuint * uniforms, Transform & transform);

	~Mesh();

private:
	GLuint m_VBO;
	GLuint m_IBO;

	unsigned int m_triCount;
};

