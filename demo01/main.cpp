#include <iostream>

#include "ECS.h"

#include "PositionSystem.h"
#include "GravitySystem.h"
#include "RigidbodyObject.h"

using namespace ECS;

// global gravitation (Earth = 1G)
const Vec3_t G(0.0f, -9.81f, 0.0f);

const int MAX_ENTITIES = 100;


int main(const int argc, const char* argv[])
{
	// get systems
	PositionSystem* posSys = ECS_Engine->GetSystemManager()->AddSystem<PositionSystem>();
	GravitySystem* gravSys = ECS_Engine->GetSystemManager()->AddSystem<GravitySystem>(G);

	// create entities
	RigidBodyObject* rbo[MAX_ENTITIES];

	for (int i = 0; i < MAX_ENTITIES; ++i)
		rbo[i] = ECS_Engine->GetEntityManager()->CreateEntity<RigidBodyObject>(Vec3_t(0.0f, i, 0.0f), 1.0f);


	// Update system 200 frames
	const int MAX_FRAMES = 200;
	float FPS = 1.0f / 60.0f;

	for (int i = 0; i < MAX_FRAMES; ++i)
	{
		ECS_Engine->Update();
	}

	ECS::Terminate();

	return 0;
}