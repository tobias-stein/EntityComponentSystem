///-------------------------------------------------------------------------------------------------
/// File:	Transform.h.
///
/// Summary:	Declares the transform class.
///-------------------------------------------------------------------------------------------------

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "math.h"

class Transform
{
private:

	glm::mat4	m_Transform;
	
public:

	Transform();
	Transform(const glm::mat4& transform);
	Transform(const glm::vec2& position_xy);
	Transform(const glm::vec3& position);
	Transform(const glm::vec3& position, const glm::quat rotation);
	Transform(const glm::vec3& position, const glm::vec3 axis, const float angle);
	Transform(const glm::vec3& position, const glm::quat rotation, const glm::vec3& scale);
	Transform(const glm::vec3& position, const glm::vec3 axis, const float angle, const glm::vec3& scale);

	inline void Zero()		{ this->m_Transform = glm::mat4(0.0f); }
	inline void One()		{ this->m_Transform = glm::mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f); }
	inline void Identity()	{ this->m_Transform = glm::mat4(1.0f); }


	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation_euler);
	void SetScale(const glm::vec3& scale);

	inline glm::vec3 GetRight() const { return glm::vec3(this->m_Transform[0]); }
	inline glm::vec3 GetUp() const { return glm::vec3(this->m_Transform[1]); }
	inline glm::vec3 GetForward() const { return glm::vec3(this->m_Transform[2]); }

	void SetRight(const glm::vec3& right);
	void SetUp(const glm::vec3& up);
	void SetForward(const glm::vec3& forward);

	inline glm::vec3 GetPosition() const { return glm::vec3(this->m_Transform[3]); }

	

	///-------------------------------------------------------------------------------------------------
	/// Fn:	glm::vec3 Transform::GetRotation();
	///
	/// Summary:	Returns euler angles.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	14/10/2017
	///
	/// Returns:	The rotation.
	///-------------------------------------------------------------------------------------------------

	glm::vec3 GetRotation() const;

	glm::vec3 GetScale() const;

	// conversion to float array
	inline operator const float*() const { return &(this->m_Transform[0][0]); }
	inline operator const glm::mat4&() const { return this->m_Transform; }

	inline static Transform IDENTITY() { return Transform(); }

}; // class Transform

#endif // __TRANSFORM_H__