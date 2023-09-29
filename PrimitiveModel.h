#pragma once
#include "Model.h"

class PrimitiveModel abstract : public Model
{
public:
	virtual void MakePrimitive(const std::string& texFilename = "") {}
};

class PrimitiveCube : public PrimitiveModel
{
public:
	virtual void MakePrimitive(const std::string& texFilename = "") override;
};

class PrimitiveShpher : public PrimitiveModel
{
private:
	enum { SectorCount = 20, StackCount = 20 };
public:
	virtual void MakePrimitive(const std::string& texFilename = "") override;
};
