#include "solver.hpp"

int main()
{
	std::vector<Recipe>	   t_allRecipes;
	std::set<Ingredient>   t_leftOvers;

	Solver::ReadRecipes(t_allRecipes, t_leftOvers);

	const Recipe& t_fuelRecipe      = Solver::GetRecipeForMaterial(t_allRecipes, { "FUEL" });
	const unsigned int t_costOfFuel = Solver::GetOreCostOfRecipe(t_allRecipes, t_fuelRecipe, t_leftOvers);

	std::cout << "The ore cost of a fuel is " << t_costOfFuel << "." << std::endl;

	return 0;
}