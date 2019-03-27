#include "map.h"

Map::Map(float boundaries, float ceiling, float floor, GLuint *uniforms)
{
	SetUpGrid();

	m_boundaries = boundaries;
	m_ceiling = ceiling;
	m_floor = floor;

	m_settingUp = false;
	m_generate = false;
	m_onPoint = false;

	m_gridShader.Init("./res/gridShader", uniforms);
	m_mapShader.Init("./res/mapShader", uniforms);

	m_clickedPoint = m_points.end();
}

void Map::Update(Mouse & mouse, const Uint8 * keyState)
{
	/*
	IF ENTER is pressed by user
		Generate map
	*/
	if (keyState[SDL_SCANCODE_RETURN]) 
	{
		m_generate = true;
	}
	else
	{
		if (keyState[SDL_SCANCODE_BACKSPACE]) 
		{
			ClearLists();
		} 
		else
		{
			// IF LEFT MOUSE BUTTON is clicked and within the boundaries of the map
			if (mouse.left_button && (mouse.x >= -0.5f && mouse.x <= 0.5f && mouse.y >= -0.5f && mouse.y <= 0.5f)) {
				/*
				IF LEFT SHIFT is held down by user
					SET map point to the point on grid nearest to the mouse
				ELSE
					SET map point to mouse position
				*/
				if (keyState[SDL_SCANCODE_LSHIFT])
				{
					m_mapX = roundf(mouse.x * 20.0f) / 20.0f;
					m_mapY = roundf(mouse.y * 20.0f) / 20.0f;
				}
				else
				{
					m_mapX = mouse.x;
					m_mapY = mouse.y;
				}

				//SET up world postion of map point
				m_x = m_mapX * (m_boundaries / 2.0f);
				m_y = m_mapY * (m_boundaries / 2.0f);


				if (!m_onPoint)
				{
					CheckPoints();
				}
				else
				{
					RecalculatePoint();
				}
			}
			else
			{
				ReleasePoint();
			}
		}
	}
}

void Map::Draw(GLuint * uniforms)
{
	m_mapShader.Bind();

	m_cameraPoint.Draw(uniforms);

	m_cameraLine.Draw(uniforms, LINE_WIDTH);

	for (std::list<Point*>::iterator it = m_points.begin(); it != m_points.end(); it++)
	{
		(*it)->Draw(uniforms);
	}

	for (std::list<Line*>::iterator it = m_lines.begin(); it != m_lines.end(); it++)
	{
		(*it)->Draw(uniforms, LINE_WIDTH);
	}

	m_gridShader.Bind();

	for (std::list<Line*>::iterator it = m_gridLines.begin(); it != m_gridLines.end(); it++)
	{
		(*it)->Draw(uniforms, GRID_LINE_WIDTH);;
	}

	for (std::list<Line*>::iterator it = m_borderLines.begin(); it != m_borderLines.end(); it++)
	{
		(*it)->Draw(uniforms, LINE_WIDTH);;
	}
}

void Map::Generate(std::list<Wall*> &walls)
{
	if (m_points.size() > 1) 
	{
		for (std::list<Point*>::iterator it = m_points.begin(); it != m_points.end(); it++)
		{
			if (it != m_it_end)
			{
				m_it_next = it;
				m_it_next++;
			}

			walls.push_back(new Wall((*it)->GetWorldPoint(), (*m_it_next)->GetWorldPoint(), m_ceiling, m_floor));
		}

		if (walls.size() > 2)
		{
			m_it_next = m_points.end();
			m_it_next--;

			walls.push_back(new Wall((*m_it_next)->GetWorldPoint(), (*m_points.begin())->GetWorldPoint(), m_ceiling, m_floor));
		}
	}

	m_generate = false;
	m_settingUp = false;
}

void Map::SetUpGrid()
{
	float gridCounter = -0.5f;

	while (gridCounter < 0.5f)
	{
		m_gridLines.push_back(new Line(Vec2(gridCounter, 0.5f), Vec2(gridCounter, -0.5f)));
		m_gridLines.push_back(new Line(Vec2(0.5f, -gridCounter), Vec2(-0.5f, -gridCounter)));

		gridCounter = gridCounter + 0.05f;
	}

	m_borderLines.push_back(new Line(Vec2( 0.5f,-0.5), Vec2(-0.5f,-0.5)));
	m_borderLines.push_back(new Line(Vec2(-0.5f,-0.5), Vec2(-0.5f, 0.5)));
	m_borderLines.push_back(new Line(Vec2(-0.5f, 0.5), Vec2( 0.5f, 0.5)));
	m_borderLines.push_back(new Line(Vec2( 0.5f, 0.5), Vec2( 0.5f,-0.5)));
}

void Map::CheckPoints()
{
	// check through points list
	for (std::list<Point*>::iterator it = m_points.begin(); it != m_points.end(); it++)
	{
		/*
		IF map point has been clicked
			Set clickedPoint to map point
			onPoint is true
			Stop loop
		*/
		if ((*it)->CheckClick(m_mapX, m_mapY))
		{
			m_onPoint = true;
			m_clickedPoint = it;
			return;
		}
	}

	CreatePoint();
}

void Map::RecalculatePoint()
{
	// SET reference point to recent clicked point
	m_referencePoint = Vec2((*m_clickedPoint)->GetTransform().GetPos().x, (*m_clickedPoint)->GetTransform().GetPos().y);

	// SET clicked point coords to map coords
	(*m_clickedPoint)->GetTransform().GetPos().x = m_mapX;
	(*m_clickedPoint)->GetTransform().GetPos().y = m_mapY;

	(*m_clickedPoint)->GetWorldPoint().x = m_x;
	(*m_clickedPoint)->GetWorldPoint().y = m_y;

	// IF the recently clicked point is the point at the end of the points list
	if (m_clickedPoint == m_it_end)
	{
		// SET current wall corner to map x and y
		m_currentWallCorner = Vec2(m_mapX, m_mapY);
	}

	for (std::list<Line*>::iterator it = m_lines.begin(); it != m_lines.end(); it++)
	{
		/*
		IF the recently clicked point is a point connected by lines
			UPDATE the point's vertices
		*/
		if ((*it)->GetVerts()[0] == m_referencePoint.x && (*it)->GetVerts()[1] == m_referencePoint.y)
		{
			(*it)->GetVerts()[0] = m_mapX;
			(*it)->GetVerts()[1] = m_mapY;
		}

		if ((*it)->GetVerts()[2] == m_referencePoint.x && (*it)->GetVerts()[3] == m_referencePoint.y)
		{
			(*it)->GetVerts()[2] = m_mapX;
			(*it)->GetVerts()[3] = m_mapY;
		}
	}
}

void Map::CreatePoint()
{
	if (m_points.size() > 0)
	{
		m_prevWallCorner = m_currentWallCorner;
	}

	m_points.push_back(new Point(Vec2(m_mapX, m_mapY), Vec2(m_x, m_y)));

	m_currentWallCorner = Vec2(m_mapX, m_mapY);

	if (m_points.size() > 1)
	{
		m_lines.push_back(new Line(m_prevWallCorner, m_currentWallCorner));
	}

	m_it_end = m_points.end();
	m_it_end--;

	m_onPoint = true;
	m_clickedPoint = m_it_end;
}

// once user releases mouse button
void Map::ReleasePoint()
{
	if (m_onPoint) 
	{
		m_onPoint = false;
		m_clickedPoint = m_points.end();
	}
}

// clear list for points and lines
void Map::ClearLists()
{
	for (std::list<Point*>::iterator it = m_points.begin(); it != m_points.end(); it++)
	{
		delete (*it);
	}

	for (std::list<Line*>::iterator it = m_lines.begin(); it != m_lines.end(); it++)
	{
		delete (*it);
	}

	m_points.clear();
	m_lines.clear();
}
