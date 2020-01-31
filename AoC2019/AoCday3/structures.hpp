#pragma once

#include <cmath>

class Point
{
	int          m_x;
	int          m_y;
	unsigned int m_combinedDistance;
public:
	Point(int x, int y, unsigned int combinedDistance = 0U) :
		m_x{ x },
		m_y{ y },
		m_combinedDistance{ combinedDistance } {}

	inline int GetX() const { return m_x; }
	inline int GetY() const { return m_y; }
	inline unsigned int GetManhattanDistance() const { return std::abs(m_x) + std::abs(m_y); }
	inline unsigned int GetCombinedDistance() const { return m_combinedDistance; }
	inline bool operator!=(const Point& other) const { return m_x == other.m_x && m_y == other.m_y; }
};

class Segment
{
	const Point			m_start;
	const Point			m_end;
	const bool			m_isVertical;
	const unsigned int	m_distanceFromStart;
public:
	Segment(const Point& start, const Point& end, bool isVertical, unsigned int distanceFromStart = 0) :
		m_start{ start },
		m_end{ end },
		m_isVertical{ isVertical },
		m_distanceFromStart{ distanceFromStart } {}

	inline const Point& GetStart()	const { return m_start; }
	inline const Point& GetEnd() const { return m_end; }
	inline bool IsVertical() const { return m_isVertical; }
	inline unsigned int GetDistanceFromStart() const { return m_distanceFromStart; }
};