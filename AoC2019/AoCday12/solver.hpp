#pragma once

#include <regex>
#include <iostream>

namespace Solver
{
	template <size_t N>
	void ReadMoons(std::array<Moon, N>& moons)
	{
		const std::regex t_inputPattern{ "<x=(.*), y=(.*), z=(.*)>" };
		std::string      t_line;

		for (size_t i = 0U; i < moons.size(); ++i)
		{
			std::getline(std::cin, t_line);
			std::smatch t_regexMatches;
			std::regex_match(t_line, t_regexMatches, t_inputPattern);
			const int t_x = std::stoi(t_regexMatches[1]);
			const int t_y = std::stoi(t_regexMatches[2]);
			const int t_z = std::stoi(t_regexMatches[3]);

			moons[i].SetPosition({ t_x, t_y, t_z });
		}
	}

	template <size_t N>
	void ApplyGravityX(std::array<Moon, N>& moons)
	{
		for (size_t i = 0U; i < N - 1U; ++i)
		{
			for (size_t j = i + 1; j < N; ++j)
			{
				Moon& t_moonOne = moons[i];
				Moon& t_moonTwo = moons[j];
				Vector3D t_moonOnePosition = t_moonOne.GetPosition();
				Vector3D t_moonTwoPosition = t_moonTwo.GetPosition();
				Vector3D t_moonOneVelocity = t_moonOne.GetVelocity();
				Vector3D t_moonTwoVelocity = t_moonTwo.GetVelocity();

				int t_MoonOneXVelocity = t_moonOneVelocity.GetX();
				int t_MoonTwoXVelocity = t_moonTwoVelocity.GetX();
				if (t_moonOnePosition.GetX() != t_moonTwoPosition.GetX())
				{
					const bool t_isMoonOneXGreater = t_moonOnePosition.GetX() > t_moonTwoPosition.GetX();
					t_MoonOneXVelocity = t_isMoonOneXGreater ? t_MoonOneXVelocity - 1 : t_MoonOneXVelocity + 1;
					t_MoonTwoXVelocity = t_isMoonOneXGreater ? t_MoonTwoXVelocity + 1 : t_MoonTwoXVelocity - 1;
					t_moonOneVelocity.SetX(t_MoonOneXVelocity);
					t_moonTwoVelocity.SetX(t_MoonTwoXVelocity);
				}
				t_moonOne.SetVelocity(t_moonOneVelocity);
				t_moonTwo.SetVelocity(t_moonTwoVelocity);
			}
		}
	}

	template <size_t N>
	void ApplyGravityY(std::array<Moon, N>& moons)
	{
		for (size_t i = 0U; i < N - 1U; ++i)
		{
			for (size_t j = i + 1; j < N; ++j)
			{
				Moon& t_moonOne = moons[i];
				Moon& t_moonTwo = moons[j];
				Vector3D t_moonOnePosition = t_moonOne.GetPosition();
				Vector3D t_moonTwoPosition = t_moonTwo.GetPosition();
				Vector3D t_moonOneVelocity = t_moonOne.GetVelocity();
				Vector3D t_moonTwoVelocity = t_moonTwo.GetVelocity();

				int t_MoonOneYVelocity = t_moonOneVelocity.GetY();
				int t_MoonTwoYVelocity = t_moonTwoVelocity.GetY();
				if (t_moonOnePosition.GetY() != t_moonTwoPosition.GetY())
				{
					const bool t_isMoonOneYGreater = t_moonOnePosition.GetY() > t_moonTwoPosition.GetY();
					t_MoonOneYVelocity = t_isMoonOneYGreater ? t_MoonOneYVelocity - 1 : t_MoonOneYVelocity + 1;
					t_MoonTwoYVelocity = t_isMoonOneYGreater ? t_MoonTwoYVelocity + 1 : t_MoonTwoYVelocity - 1;
					t_moonOneVelocity.SetY(t_MoonOneYVelocity);
					t_moonTwoVelocity.SetY(t_MoonTwoYVelocity);
				}
				t_moonOne.SetVelocity(t_moonOneVelocity);
				t_moonTwo.SetVelocity(t_moonTwoVelocity);
			}
		}
	}

	template <size_t N>
	void ApplyGravityZ(std::array<Moon, N>& moons)
	{
		for (size_t i = 0U; i < N - 1U; ++i)
		{
			for (size_t j = i + 1; j < N; ++j)
			{
				Moon& t_moonOne = moons[i];
				Moon& t_moonTwo = moons[j];
				Vector3D t_moonOnePosition = t_moonOne.GetPosition();
				Vector3D t_moonTwoPosition = t_moonTwo.GetPosition();
				Vector3D t_moonOneVelocity = t_moonOne.GetVelocity();
				Vector3D t_moonTwoVelocity = t_moonTwo.GetVelocity();

				int t_MoonOneZVelocity = t_moonOneVelocity.GetZ();
				int t_MoonTwoZVelocity = t_moonTwoVelocity.GetZ();
				if (t_moonOnePosition.GetZ() != t_moonTwoPosition.GetZ())
				{
					const bool t_isMoonOneZGreater = t_moonOnePosition.GetZ() > t_moonTwoPosition.GetZ();
					t_MoonOneZVelocity = t_isMoonOneZGreater ? t_MoonOneZVelocity - 1 : t_MoonOneZVelocity + 1;
					t_MoonTwoZVelocity = t_isMoonOneZGreater ? t_MoonTwoZVelocity + 1 : t_MoonTwoZVelocity - 1;
					t_moonOneVelocity.SetZ(t_MoonOneZVelocity);
					t_moonTwoVelocity.SetZ(t_MoonTwoZVelocity);
				}
				t_moonOne.SetVelocity(t_moonOneVelocity);
				t_moonTwo.SetVelocity(t_moonTwoVelocity);
			}
		}
	}

	template <size_t N>
	void ApplyAllGravity(std::array<Moon, N>& moons)
	{
		ApplyGravityX(moons);
		ApplyGravityY(moons);
		ApplyGravityZ(moons);
	}

	template <size_t N>
	void ApplyAllVelocity(std::array<Moon, N>& moons)
	{
		for(auto& moon : moons)
		{
			moon.ApplyVelocityChange();
		}
	}

	template <size_t N>
	void CycleOnce(std::array<Moon, N>& moons)
	{
		ApplyAllGravity(moons);
		ApplyAllVelocity(moons);
	}

	template <size_t N>
	unsigned int GetTotalEnergy(std::array<Moon, N>& moons)
	{
		unsigned int t_totalEnergy = 0U;
		for (auto& moon : moons)
		{
			t_totalEnergy += moon.GetTotalEnergy();
		}
		return t_totalEnergy;
	}

	template <size_t N>
	unsigned int GetNumberOfStepsToRepetitionX(std::array<Moon, N>& moons)
	{
		std::array<int, N> m_startingPositionsX;
		std::array<int, N> m_startingVelocitiesX;
		for (size_t i = 0U; i < N; ++i)
		{
			m_startingPositionsX[i]  = moons[i].GetPosition().GetX();
			m_startingVelocitiesX[i] = moons[i].GetVelocity().GetX();
		}

		std::array<int, N> m_updatedPositionsX = m_startingPositionsX;
		std::array<int, N> m_updatedVelocitiesX = m_startingVelocitiesX;
		unsigned int t_steps = 0U;
		do
		{
			++t_steps;
			ApplyGravityX(moons);
			for (size_t i = 0U; i < N; ++i)
			{
				moons[i].ApplyVelocityX();
				m_updatedPositionsX[i] = moons[i].GetPosition().GetX();
				m_updatedVelocitiesX[i] = moons[i].GetVelocity().GetX();
			}			
		} while (m_startingPositionsX != m_updatedPositionsX || m_startingVelocitiesX != m_updatedVelocitiesX);
		return t_steps;
	}

	template <size_t N>
	unsigned int GetNumberOfStepsToRepetitionY(std::array<Moon, N>& moons)
	{
		std::array<int, N> m_startingPositionsY;
		std::array<int, N> m_startingVelocitiesY;
		for (size_t i = 0U; i < N; ++i)
		{
			m_startingPositionsY[i] = moons[i].GetPosition().GetY();
			m_startingVelocitiesY[i] = moons[i].GetVelocity().GetY();
		}

		std::array<int, N> m_updatedPositionsY = m_startingPositionsY;
		std::array<int, N> m_updatedVelocitiesY = m_startingVelocitiesY;
		unsigned int t_steps = 0U;
		do
		{
			++t_steps;
			ApplyGravityY(moons);
			for (size_t i = 0U; i < N; ++i)
			{
				moons[i].ApplyVelocityY();
				m_updatedPositionsY[i] = moons[i].GetPosition().GetY();
				m_updatedVelocitiesY[i] = moons[i].GetVelocity().GetY();
			}
		} while (m_startingPositionsY != m_updatedPositionsY || m_startingVelocitiesY != m_updatedVelocitiesY);
		return t_steps;
	}

	template <size_t N>
	unsigned int GetNumberOfStepsToRepetitionZ(std::array<Moon, N>& moons)
	{
		std::array<int, N> m_startingPositionsZ;
		std::array<int, N> m_startingVelocitiesZ;
		for (size_t i = 0U; i < N; ++i)
		{
			m_startingPositionsZ[i] = moons[i].GetPosition().GetZ();
			m_startingVelocitiesZ[i] = moons[i].GetVelocity().GetZ();
		}

		std::array<int, N> m_updatedPositionsZ = m_startingPositionsZ;
		std::array<int, N> m_updatedVelocitiesZ = m_startingVelocitiesZ;
		unsigned int t_steps = 0U;
		do
		{
			++t_steps;
			ApplyGravityZ(moons);
			for (size_t i = 0U; i < N; ++i)
			{
				moons[i].ApplyVelocityZ();
				m_updatedPositionsZ[i] = moons[i].GetPosition().GetZ();
				m_updatedVelocitiesZ[i] = moons[i].GetVelocity().GetZ();
			}
		} while (m_startingPositionsZ != m_updatedPositionsZ || m_startingVelocitiesZ != m_updatedVelocitiesZ);
		return t_steps;
	}

	long long int GreatestCommonDivisor(long long int a, long long int b)
	{
		if (a == 0)
			return b;
		return GreatestCommonDivisor(b % a, a);
	}

	long long int LowestCommonMultiple(long long int a, long long int b)
	{
		if (0 == a && 0 == b)
			return 0;
		return std::abs(a * b) / GreatestCommonDivisor(a, b);
	}

	template <size_t N>
	unsigned long long int GetNumberOfStepsToRepetition(const std::array<Moon, N>& moons)
	{
		std::array<Moon, N> t_moonsCopy = moons;		

		unsigned long long int t_stepsUntilXRepetition = GetNumberOfStepsToRepetitionX(t_moonsCopy);
		unsigned long long int t_stepsUntilYRepetition = GetNumberOfStepsToRepetitionY(t_moonsCopy);
		unsigned long long int t_stepsUntilZRepetition = GetNumberOfStepsToRepetitionZ(t_moonsCopy);

		return LowestCommonMultiple(LowestCommonMultiple(t_stepsUntilXRepetition, t_stepsUntilYRepetition), t_stepsUntilZRepetition);
	}
}	// namespace Solver
