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
	static const Color4f DEFAULT_COLOR0;

private:

	Color4f m_Color0;

public:

	MaterialComponent(const Material& material, Color4f color = DEFAULT_COLOR0);

	virtual ~MaterialComponent();

	void Apply();

	inline void SetColor(const Color4f& color) { this->m_Color0 = color; }
	void SetColor(float r, float g, float b, float a = 1.0f);

	inline Color4f GetColor() const { return this->m_Color0; }

}; // class MaterialComponent

#endif // __MATERIAL_COMPONENT_H__
