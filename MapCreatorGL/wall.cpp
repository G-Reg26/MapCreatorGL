#include "wall.h"

Wall::Wall(Vec2 & corner1, Vec2 & corner2, float & ceiling, float & floor)
{
	// get wall width
	float wallWidth = Functions::C((corner1.x - corner2.x), (corner1.y - corner2.y));

	// initialize mesh vertices
	m_verts[0] = Vertex(Vec3( wallWidth / 2.0f, ceiling, 0.0f), Vec2(0.0f, 1.0f));
	m_verts[1] = Vertex(Vec3(-wallWidth / 2.0f, ceiling, 0.0f), Vec2(1.0f, 1.0f));
	m_verts[2] = Vertex(Vec3(-wallWidth / 2.0f, floor,	 0.0f), Vec2(1.0f, 0.0f));
	m_verts[3] = Vertex(Vec3( wallWidth / 2.0f, floor,	 0.0f), Vec2(0.0f, 0.0f));

	// set wall position
	m_transform.SetPos(Vec3((corner1.x + corner2.x) / 2.0f, (floor + ceiling) / 2.0f, (corner1.y + corner2.y) / 2.0f));

	// set wall y rotation
	m_transform.GetRot().y = atanf((corner1.x - corner2.x) / (corner1.y - corner2.y)) + Functions::ToRadians(90.0f);

	// initialize mesh
	m_mesh = Mesh(m_verts, m_indicies, sizeof(m_verts), sizeof(m_indicies), sizeof(m_indicies) / sizeof(m_indicies[0]));

	// initialize texture
	m_texture.Init("./res/bricks.jpg");
}

void Wall::Draw(Camera & camera, GLuint * uniforms)
{
	m_texture.Bind(0);
	m_mesh.Draw(uniforms, camera, m_transform);
}
