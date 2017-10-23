///-------------------------------------------------------------------------------------------------
/// File:	Stash.h.
///
/// Summary:	Implements the stash class.
///-------------------------------------------------------------------------------------------------

#ifndef __STASH_ENTITY_H__
#define __STASH_ENTITY_H__

#include "GameObject.h"
#include "GameTypes.h"

#include "RigidbodyComponent.h"
#include "MaterialComponent.h"

class Stash : public GameObject<Stash>
{
private:

	RigidbodyComponent*		m_ThisRigidbody;
	MaterialComponent*		m_ThisMaterial;

	PlayerId				m_OwningPlayer;

	float					m_StashedBounty;

	void UpdateColor();

public:

	Stash(PlayerId playerId);
	virtual ~Stash();

	virtual void OnEnable() override;
	virtual void OnDisable() override;

	inline void SetOwner(PlayerId playerId) { this->m_OwningPlayer = playerId; }
	inline PlayerId GetOwner() const { return this->m_OwningPlayer; }

	inline void ClearStash() { this->m_StashedBounty = 0.0f; }
	inline float GetStashValue() const { return this->m_StashedBounty; }

	void StashBounty(float bounty);

}; // class Stash

#endif // __STASH_ENTITY_H__
