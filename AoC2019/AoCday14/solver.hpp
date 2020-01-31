#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <set>

#include "structures.hpp"

namespace Solver
{
	void ReadRecipes(std::vector<Recipe>& recipes, std::set<Ingredient>& leftOvers)
	{
		const std::regex t_inputPattern{ "(\\d+) ([A-Z]+)" };
		std::string		 t_line;

		std::ifstream t_fileStream("input.txt");
		while (std::getline(t_fileStream, t_line))
		{
			if (t_line.empty())
			{
				break;
			}

			std::vector<Ingredient> t_ingredients;
			std::smatch				t_regexMatches;

			while (std::regex_search(std::cbegin(t_line), std::cend(t_line), t_regexMatches, t_inputPattern))
			{
				unsigned int t_quantity = std::stoi(t_regexMatches[1]);
				std::string t_name		= t_regexMatches[2];

				t_ingredients.push_back({ {t_name}, t_quantity });
				leftOvers.insert({ {t_name}, 0U });
				t_line = { t_regexMatches.suffix().first, std::cend(t_line) };
			}
			Ingredient t_result = std::move(t_ingredients[t_ingredients.size() - 1U]);
			t_ingredients.pop_back();
			recipes.push_back({ t_ingredients, t_result });
		}
	}

	const Recipe& GetRecipeForMaterial(const std::vector<Recipe>& recipes, const Material& neededMaterial)
	{
		auto t_neededSubRecipeIterator = std::find_if(std::begin(recipes), std::end(recipes),
			[&neededMaterial](const Recipe& recipe) { return recipe.ResultsIn(neededMaterial); });
		if (t_neededSubRecipeIterator == std::end(recipes))
		{
			throw new std::runtime_error("Unknown recipe!");
		}
		return *t_neededSubRecipeIterator;
	}

	Ingredient GetLeftOverIngredientAndErase(std::set<Ingredient>& leftOvers, const Material& neededMaterial)
	{
		auto t_leftOverIngredientIterator = std::find_if(std::begin(leftOvers), std::end(leftOvers),
			[&neededMaterial](const Ingredient& ingredient) { return ingredient.GetMaterial() == neededMaterial; });
		if (t_leftOverIngredientIterator == std::end(leftOvers))
		{
			throw new std::runtime_error("Unknown ingredient!");
		}
		Ingredient t_leftOverIngredient = *t_leftOverIngredientIterator;
		leftOvers.erase(t_leftOverIngredientIterator);
		return t_leftOverIngredient;
	}

	unsigned int GetOreCostOfRecipe(const std::vector<Recipe>& allRecipes, const Recipe& theNeededRecipe, std::set<Ingredient>& leftOvers)
	{
		unsigned int t_totalCost = 0U;
		for (const auto& ingredient : theNeededRecipe.GetIngredients())
		{
			const Material& t_neededMaterial = ingredient.GetMaterial();
			unsigned int t_neededQuantity    = ingredient.GetQuantity();
			if (t_neededMaterial.GetName() == "ORE")
			{
				t_totalCost += t_neededQuantity;
				break;
			}

			const Recipe& t_neededSubRecipe = GetRecipeForMaterial(allRecipes, t_neededMaterial);
			Ingredient t_leftOverIngredient = GetLeftOverIngredientAndErase(leftOvers, t_neededMaterial);

			unsigned int t_quantityOfLeftOverMaterial         = t_leftOverIngredient.GetQuantity();
			const unsigned int t_createdQuantityWithSubRecipe = t_neededSubRecipe.GetResult().GetQuantity();
			const unsigned int t_numberOfCrafts = static_cast<unsigned int>(std::ceil((static_cast<int>(t_neededQuantity) - 
				static_cast<int>(t_quantityOfLeftOverMaterial)) / static_cast<float>(t_createdQuantityWithSubRecipe)));

			t_quantityOfLeftOverMaterial += t_numberOfCrafts * t_createdQuantityWithSubRecipe - t_neededQuantity;

			for(unsigned i = 0; i < t_numberOfCrafts; ++i)
				t_totalCost += GetOreCostOfRecipe(allRecipes, t_neededSubRecipe, leftOvers);

			t_leftOverIngredient.SetQuantity(t_quantityOfLeftOverMaterial);
			leftOvers.insert(t_leftOverIngredient);
		}
		return t_totalCost;
	}
}