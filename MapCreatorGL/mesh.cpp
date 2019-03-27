#include "mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(Vertex * verticies, unsigned int * indicies, unsigned int vertexSize, unsigned int indexSize, unsigned int indexCount)
{
	m_triCount = indexCount;

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, verticies, GL_STREAM_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indicies, GL_STREAM_DRAW);
}

void Mesh::Draw(GLuint * uniforms, Camera & camera, Transform & transform)
{
	Mat4 finalMatrix = camera.GetProjectionMatrix() * transform.GetModel();

	glUniformMatrix4fv(uniforms[0], 1, GL_TRUE, &finalMatrix.matrix[0][0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)m_triCount);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, m_triCount , GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Mesh::DrawDot(GLuint * uniforms, Transform & transform)
{
	Mat4 finalMatrix = transform.GetModel();

	glUniformMatrix4fv(uniforms[0], 1, GL_TRUE, &finalMatrix.matrix[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, m_triCount, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
}

Mesh::~Mesh()
{
}
