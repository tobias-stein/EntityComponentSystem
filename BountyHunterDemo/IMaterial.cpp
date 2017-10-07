///-------------------------------------------------------------------------------------------------
/// File:	IMaterial.cpp.
///
/// Summary:	Declares the Material interface.
///-------------------------------------------------------------------------------------------------

#include "IMaterial.h"

IMaterial::IMaterial()
{
	this->Initialize();
}

IMaterial::~IMaterial()
{
	this->Release();
}