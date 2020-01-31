#pragma once

class Vector3D
{
	int m_x;
	int m_y;
	int m_z;
public:
	Vector3D() : m_x{ 0 }, m_y{ 0 }, m_z{ 0 } {}
	Vector3D(int x, int y, int z) : m_x{x}, m_y{y}, m_z{z} {}

	inline int GetX() const { return m_x; }
	inline int GetY() const { return m_y; }
	inline int GetZ() const { return m_z; }
	inline void SetX(int x) { m_x = x; }
	inline void SetY(int y) { m_y = y; }
	inline void SetZ(int z) { m_z = z; }
	inline unsigned int GetAbsoluteSum() const { return std::abs(m_x) + std::abs(m_y) + std::abs(m_z);; }
	inline bool operator==(const Vector3D& other) const { return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;; }

	Vector3D& operator+=(const Vector3D& other) {
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		return *this;		
	}
};

class Moon
{
	Vector3D m_position;
	Vector3D m_velocity;
public:
	inline Vector3D GetPosition() const { return m_position; }
	inline Vector3D GetVelocity() const { return m_velocity; }
	inline void SetPosition(const Vector3D position) { m_position = position; }
	inline void SetVelocity(const Vector3D velocity) { m_velocity = velocity; }
	inline void ApplyVelocityX() { m_position.SetX(m_position.GetX() + m_velocity.GetX()); }
	inline void ApplyVelocityY() { m_position.SetY(m_position.GetY() + m_velocity.GetY()); }
	inline void ApplyVelocityZ() { m_position.SetZ(m_position.GetZ() + m_velocity.GetZ()); }
	inline void ApplyVelocityChange() { ApplyVelocityX(); ApplyVelocityY(); ApplyVelocityZ(); }
	inline unsigned int GetTotalEnergy() const { return m_position.GetAbsoluteSum() * m_velocity.GetAbsoluteSum(); }
	inline bool operator==(const Moon& other) const { return m_position == other.m_position && m_velocity == other.m_velocity; }
};