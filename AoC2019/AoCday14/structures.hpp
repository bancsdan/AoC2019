#pragma once

#include <string>
#include <vector>

class Material
{
	const std::string m_name;
public:
	Material(const std::string& name) : m_name{ name } {}

	inline const std::string& GetName() const { return m_name; }
	inline bool operator==(const Material& other) const { return m_name == other.m_name; }
};

class Ingredient
{
	const Material m_material;
	unsigned int   m_quantity;
public:
	Ingredient(const Material& material, unsigned int m_quantity) : m_material{ material }, m_quantity{ m_quantity } {}

	inline unsigned int GetQuantity() const { return m_quantity; }
	inline void SetQuantity(unsigned int quantity) { m_quantity = quantity; }
	inline const Material& GetMaterial() const { return m_material; }
	inline bool operator<(const Ingredient& other) const { return m_material.GetName() < other.m_material.GetName(); }
};

class Recipe
{
	std::vector<Ingredient>	m_ingredients;
	Ingredient				m_result;
public:
	Recipe(const std::vector<Ingredient>& ingredients, const Ingredient& result) : m_ingredients{ ingredients }, m_result{ result } {}

	inline const std::vector<Ingredient>& GetIngredients() const { return m_ingredients; }
	inline const Ingredient& GetResult() const { return m_result; }
	inline bool	ResultsIn(const Material& material) const { return material == m_result.GetMaterial(); }
};
