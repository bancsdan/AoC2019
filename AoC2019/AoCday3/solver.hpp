#pragma once

#include <sstream>
#include <algorithm>
#include <functional>

namespace Solver
{
	std::vector<Segment> GetSegments(const std::string& wire)
	{
		std::stringstream	 t_wireStream(wire);
		std::string			 t_pointString;
		std::vector<Segment> t_segments;
		Point				 t_previousPoint{ 0, 0, 0U };
		unsigned int         t_distanceFromStart = 0U;

		while (std::getline(t_wireStream, t_pointString, ','))
		{
			const unsigned int t_segmentLength = std::stoi(std::string{ t_pointString.begin() + 1, t_pointString.end() });
			const char& t_direction = t_pointString[0];
			t_distanceFromStart += t_segmentLength;

			int t_newX;
			int t_newY;
			bool t_isVertical = false;
			switch (t_direction)
			{
			case('L'):
			{
				t_newX = t_previousPoint.GetX() - t_segmentLength;
				t_newY = t_previousPoint.GetY();
				t_isVertical = false;
				break;
			}
			case('R'):
			{
				t_newX = t_previousPoint.GetX() + t_segmentLength;
				t_newY = t_previousPoint.GetY();
				t_isVertical = false;
				break;
			}
			case('D'):
			{
				t_newX = t_previousPoint.GetX();
				t_newY = t_previousPoint.GetY() - t_segmentLength;
				t_isVertical = true;
				break;
			}
			case('U'):
			{

				t_newX = t_previousPoint.GetX();
				t_newY = t_previousPoint.GetY() + t_segmentLength;
				t_isVertical = true;
				break;
			}
			default:
				break;
			}
			const Point   t_newPoint{ t_newX, t_newY };
			const Segment t_newSegment{ t_previousPoint, t_newPoint, t_isVertical, t_distanceFromStart };
			t_segments.push_back(t_newSegment);
			t_previousPoint = t_newPoint;
		}
		return t_segments;
	}

	bool AreSegmentsParallel(const Segment& firstSegment, const Segment& secondSegment)
	{
		return firstSegment.IsVertical() == secondSegment.IsVertical();
	}

	bool Intersects(const Segment& horizontal, const Segment& vertical)
	{
		const auto& t_horizontalStart = horizontal.GetStart();
		const auto& t_verticalStart = vertical.GetStart();
		const int t_xMin = std::min(t_horizontalStart.GetX(), horizontal.GetEnd().GetX());
		const int t_xMax = std::max(t_horizontalStart.GetX(), horizontal.GetEnd().GetX());
		const int t_yMin = std::min(t_verticalStart.GetY(), vertical.GetEnd().GetY());
		const int t_yMax = std::max(t_verticalStart.GetY(), vertical.GetEnd().GetY());

		return t_horizontalStart.GetY() >= t_yMin &&
			t_horizontalStart.GetY() <= t_yMax &&
			t_verticalStart.GetX() >= t_xMin &&
			t_verticalStart.GetX() <= t_xMax;
	}

	auto GetIntersectingPoints(const std::vector<Segment>& firstWireSegments, const std::vector<Segment>& secondWireSegments)
	{
		std::vector<Point> t_intersectingPointsWithDistances;
		for (const auto& segmentsOfFirst : firstWireSegments)
		{
			for (const auto& segmentOfSecond : secondWireSegments)
			{
				if (!AreSegmentsParallel(segmentsOfFirst, segmentOfSecond))
				{
					const bool t_isTheFirstSegmentVertical = segmentsOfFirst.IsVertical();
					const auto& t_horizontal = t_isTheFirstSegmentVertical ? segmentOfSecond : segmentsOfFirst;
					const auto& t_vertical   = t_isTheFirstSegmentVertical ? segmentsOfFirst : segmentOfSecond;
					if (Intersects(t_horizontal, t_vertical))
					{
						const unsigned int t_horizontalDistanceFromEndOfSegment = std::abs(t_horizontal.GetEnd().GetX() - t_vertical.GetEnd().GetX());
						const unsigned int t_verticalDistanceFromEndOfSegment	= std::abs(t_vertical.GetEnd().GetY() - t_horizontal.GetEnd().GetY());
						const unsigned int t_distanceOnHorizontal			    = t_horizontal.GetDistanceFromStart() - t_horizontalDistanceFromEndOfSegment;
						const unsigned int t_distanceOnVertical                 = t_vertical.GetDistanceFromStart() - t_verticalDistanceFromEndOfSegment;
						t_intersectingPointsWithDistances.push_back(Point{
							t_vertical.GetStart().GetX(),
							t_horizontal.GetStart().GetY(),
							t_distanceOnHorizontal + t_distanceOnVertical});
					}
				}
			}
		}
		auto t_startPoint = std::find_if(std::begin(t_intersectingPointsWithDistances), std::end(t_intersectingPointsWithDistances), [](const Point& point) { return 0U == point.GetCombinedDistance(); });
		if (t_startPoint != std::end(t_intersectingPointsWithDistances))
		{
			t_intersectingPointsWithDistances.erase(t_startPoint);
		}
		return t_intersectingPointsWithDistances;
	}

	unsigned int FindClosestPointsManhattan(const std::vector<Point>& points)
	{
		const auto t_minDistancePointIterator = std::min_element(std::begin(points), std::end(points),
			[](const Point& p1, const Point& p2) { return p1.GetManhattanDistance() < p2.GetManhattanDistance(); });

		return t_minDistancePointIterator->GetManhattanDistance();
	}

	unsigned int FindClosestPointsCombined(const std::vector<Point>& points)
	{
		const auto t_minDistancePointIterator = std::min_element(std::begin(points), std::end(points),
			[](const Point& p1, const Point& p2) { return p1.GetCombinedDistance() < p2.GetCombinedDistance(); });

		return t_minDistancePointIterator->GetCombinedDistance();
	}
}	// namespace Solver
