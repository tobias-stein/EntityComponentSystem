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
	//for (int i = 0; i < 2; ++i)
	//{
		ECS::Initialize();

		// get systems
		PositionSystem* posSys = ECS_Engine->GetSystemManager()->AddSystem<PositionSystem>();
		GravitySystem* gravSys = ECS_Engine->GetSystemManager()->AddSystem<GravitySystem>(G);

		posSys->AddDependencies(gravSys);
		posSys->AddDependencies(gravSys);
		posSys->AddDependencies(gravSys);

		//ECS_Engine->GetSystemManager()->AddSystemDependency<PositionSystem>(gravSys);

		for (int i = 0; i < MAX_ENTITIES; ++i)
			ECS_Engine->GetEntityManager()->CreateEntity<RigidBodyObject>(Vec3_t(0.0f, (float)i, 0.0f), 1.0f);

		const float DT = 1.0f / 60.0f;

		// Update system 200 frames
		const int MAX_FRAMES = 200;

		for (int i = 0; i < MAX_FRAMES; ++i)
		{
			ECS_Engine->Update(DT);
		}


		ECS::EntityId id = ECS_Engine->GetEntityManager()->GetEntityId(0);

		ECS_Engine->GetEntityManager()->DestroyEntity(id);

		ECS::Terminate();
	//}

	return 0;
}