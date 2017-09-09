#ifndef __POSITION_COMPONENT_H__
#define __POSITION_COMPONENT_H__

#include "Vec3.h"
#include "Component.h"

using Position3d = Vec3_t;

class PositionComponent : public ECS::Component<PositionComponent>
{
	Position3d m_Pos;

public:

	PositionComponent() :
		m_Pos(Position3d())
	{}

	PositionComponent(float x, float y, float z) :
		m_Pos(Position3d(x, y, z))
	{}

	PositionComponent(Position3d position) :
		m_Pos(position)
	{}

	virtual ~PositionComponent()
	{}

	// ACCESSOR

	inline const Position3d& GetPosition() const
	{
		return this->m_Pos;
	}

	inline void SetPosition(Position3d& position)
	{
		this->m_Pos = position;
	}

	inline float GetX() const
	{
		return this->m_Pos.x;
	}

	inline float GetY() const
	{
		return this->m_Pos.y;
	}

	inline float GetZ() const
	{
		return this->m_Pos.z;
	}
};

#endif // __POSITION_COMPONENT_H__