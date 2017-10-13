///-------------------------------------------------------------------------------------------------
/// File:	MaterialComponent.h.
///
/// Summary:	Declares the material component class.
///-------------------------------------------------------------------------------------------------

#ifndef __MATERIAL_COMPONENT_H__
#define __MATERIAL_COMPONENT_H__

#include <ECS/ECS.h>

#include "Material.h"

class MaterialComponent : public Material, public ECS::Component<MaterialComponent>
{
	static const Color4f DEFAULT_COLOR0;

private:

	Color4f m_Color0;

public:

	MaterialComponent(const Material& material, Color4f color = DEFAULT_COLOR0);

	virtual ~MaterialComponent();

	void Apply();

}; // class MaterialComponent

#endif // __MATERIAL_COMPONENT_H__
