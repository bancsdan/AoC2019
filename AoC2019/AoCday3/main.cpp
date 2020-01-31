#include <iostream>
#include <string>
#include <vector>

#include "structures.hpp"
#include "solver.hpp"

int main()
{
	std::string t_line;
	
	std::getline(std::cin, t_line);
	const auto t_firstWireSegments = Solver::GetSegments(t_line);
	std::getline(std::cin, t_line);
	const auto t_secondWireSegments = Solver::GetSegments(t_line);

	std::vector<Point> t_intersectingPoints = Solver::GetIntersectingPoints(t_firstWireSegments, t_secondWireSegments);
	const auto t_minDistanceManhattan		= Solver::FindClosestPointsManhattan(t_intersectingPoints);
	const auto t_minDistanceCombined	    = Solver::FindClosestPointsCombined(t_intersectingPoints);

	return 0;
}