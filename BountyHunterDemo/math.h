///-------------------------------------------------------------------------------------------------
/// File:	math.h.
///
/// Summary:	Declares the mathematics class.
///-------------------------------------------------------------------------------------------------

#ifndef __MATH_H__
#define __MATH_H__

// include standard math
#include <math.h>

// include glm math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtc/random.hpp>

using Color3f = glm::vec3;
using Color4f = glm::vec4;
using Color3ui = glm::uvec3;
using Color4ui = glm::uvec4;

using Point = glm::vec3;
using Position = glm::vec3;

using Point2D = glm::vec2;
using Position2D = glm::vec2;

/// Summary:	Defines an inavlid position.
static const Position INVALID_POSITION = glm::vec3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

#endif // __MATH_H__

