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
public:

	MaterialComponent(const Material& material);

	virtual ~MaterialComponent();

	void Apply() const;

}; // class MaterialComponent

#endif // __MATERIAL_COMPONENT_H__
