#include <array>
#include <limits>

#include "structures.hpp"
#include "solver.hpp"

int main()
{
	constexpr size_t                  t_numberOfMoons = 4U;
	constexpr size_t                  t_numberOfSteps = 1000U;
	std::array<Moon, t_numberOfMoons> t_moons;

	Solver::ReadMoons(t_moons);
	std::array<Moon, t_numberOfMoons> t_moonsCopy = t_moons;

	for (unsigned int i = 0U; i < t_numberOfSteps; ++i)
	{
		Solver::CycleOnce(t_moonsCopy);
	}

	std::cout << "The total energy of the system after " << t_numberOfSteps << " steps is " << Solver::GetTotalEnergy(t_moonsCopy) << "." << std::endl;
	std::cout << "The total numer of steps needed to reach the initial state again is " << Solver::GetNumberOfStepsToRepetition(t_moons) << "." << std::endl;

	return 0;
}