#pragma once

#include <list>
#include <GL\glew.h>

#include "math.h"
#include "shader.h"
#include "camera.h"
#include "mouse.h"
#include "wall.h"

struct Point 
{
	Point() 
	{
	}

	Point(Vec2 point)
	{
		m_transform.GetPos().x = point.x;
		m_transform.GetPos().y = point.y;

		glGenBuffers(1, &m_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Point(Vec2 point, Vec2 corner) 
	{
		m_worldPoint.x = corner.x;
		m_worldPoint.y = corner.y;

		m_transform.GetPos().x = point.x;
		m_transform.GetPos().y = point.y;

		glGenBuffers(1, &m_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Draw(GLuint * uniforms) 
	{
		Mat4 finalMatrix = m_transform.GetModel();

		glUniformMatrix4fv(uniforms[0], 1, GL_TRUE, &finalMatrix.matrix[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glPointSize(10.0f);

		glDrawArrays(GL_POINTS, 0, 1);

		glDisableVertexAttribArray(0);
	}

	// checks if point has been clicked
	bool CheckClick(float x, float y) 
	{
		m_topPoint.x = m_transform.GetPos().x - (COLLISION_BOX_SCALE / 2.0f);
		m_topPoint.y = m_transform.GetPos().y + (COLLISION_BOX_SCALE / 2.0f);

		m_bottomPoint.x = m_transform.GetPos().x + (COLLISION_BOX_SCALE / 2.0f);
		m_bottomPoint.y = m_transform.GetPos().y - (COLLISION_BOX_SCALE / 2.0f);

		if (x < m_bottomPoint.x && x > m_topPoint.x &&
			y > m_bottomPoint.y && y < m_topPoint.y)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	Transform &GetTransform() { return m_transform; }
	Vec2 &GetWorldPoint() { return m_worldPoint; }

	float COLLISION_BOX_SCALE = 0.015f;

	float m_verts[2]
	{
		0.0f, 0.0f,
	};

	GLuint m_VBO;

	Transform m_transform;

	// boundaries for mouse collision
	Vec2 m_topPoint;
	Vec2 m_bottomPoint;

	// 
	Vec2 m_worldPoint;
};

struct Line
{
	Line() 
	{
	}

	Line(Vec2 point1, Vec2 point2)
	{
		m_verts[0] = point1.x;
		m_verts[1] = point1.y;

		m_verts[2] = point2.x;
		m_verts[3] = point2.y;

		glGenBuffers(1, &m_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Draw(GLuint * uniforms, const float & lineWidth)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_verts), &m_verts[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		Mat4 finalMatrix = m_transform.GetModel();

		glUniformMatrix4fv(uniforms[0], 1, GL_TRUE, &finalMatrix.matrix[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glLineWidth(lineWidth);

		glDrawArrays(GL_LINES, 0, 2);

		glDisableVertexAttribArray(0);
	}

	float * GetVerts() { return m_verts; }

	float m_verts[4];

	GLuint m_VBO;

	Transform m_transform;
};

class Map
{
public:
	Map(float xMax, float ceiling, float floor, GLuint *uniforms);

	void Update(Mouse &mouse, const Uint8 *keyState);
	void Draw(GLuint *uniforms);
	void Generate(std::list<Wall*> &walls);

	void SetUpGrid();
	void CheckPoints();
	void RecalculatePoint();
	void CreatePoint();
	void ReleasePoint();
	void ClearLists();

	inline bool &SettingUpMap() { return m_settingUp; }
	inline bool &IsGenerating() { return m_generate; }
	inline Point &CameraPoint() { return m_cameraPoint; }
	inline Line &CameraLine() { return m_cameraLine; }
	inline std::list<Point*> &PointsList() { return m_points; }
	inline std::list<Line*> &LinesList() { return m_lines; }

private:
	const float GRID_LINE_WIDTH = 1.0f;
	const float LINE_WIDTH = 3.0f;

	std::list<Point*> m_points;
	std::list<Line*> m_lines;

	// grid objects for map
	std::list<Line*> m_gridLines;
	std::list<Line*> m_borderLines;

	// pointers
	std::list<Point*>::iterator m_it_next;
	std::list<Point*>::iterator m_it_end;
	std::list<Point*>::iterator m_clickedPoint;

	Shader m_gridShader;
	Shader m_mapShader;

	Point m_cameraPoint;
	Line m_cameraLine;
	
	float m_boundaries;
	float m_ceiling;
	float m_floor;

	Vec2 m_currentWallCorner;
	Vec2 m_prevWallCorner;
	Vec2 m_referencePoint;

	bool m_settingUp;
	bool m_generate;
	bool m_onPoint;

	float m_x;
	float m_y;

	float m_mapX;
	float m_mapY;
};