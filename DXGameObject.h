#pragma once
#include <typeinfo>
#include <unordered_map>
#include <set>
#include <memory>
#include "Components/DXTransform.h"
#include "Components/ComponentException.h"

using TypeInfoRef = std::reference_wrapper<const std::type_info>;
using LPCOMP = std::unique_ptr<BaseComponent>;

struct HashCode
{
	std::size_t operator()(TypeInfoRef code) const
	{
		return code.get().hash_code();
	}
};

struct EqualTo
{
	bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
	{
		return lhs.get() == rhs.get();
	}
};

class DXGameObject
{
private:
	std::unordered_map<TypeInfoRef, LPCOMP, HashCode, EqualTo> components;
	std::set<ActionComponent*> actionables;
	std::set<RenderComponent*> renderables;
	std::unique_ptr<DXTransform> transform;

public:
	DXGameObject();

	DXTransform* GetTransform() const;

	template<typename T, typename = std::enable_if<std::is_base_of<BaseComponent, T>::value>>
	T* AddComponent()
	{
		if (nullptr != components[typeid(T)])
		{
			std::string msg = "Already Component : ";
			msg += typeid(T).name();
			ThrowComponentException(msg);
		}

		components[typeid(T)] = std::make_unique<T>(this);
		switch (components[typeid(T)]->GetType())
		{
		case ComponentType::ACTION: actionables.insert(reinterpret_cast<ActionComponent*>(components[typeid(T)].get())); break;
		case ComponentType::RENDER: renderables.insert(reinterpret_cast<RenderComponent*>(components[typeid(T)].get())); break;
		}

		return dynamic_cast<T*>(components[typeid(T)].get());
	}
	template<typename T, typename = std::enable_if<std::is_base_of<BaseComponent, T>::value>>
	T* GetComponent()
	{
		if (components.end() == components.find(typeid(T))) return nullptr;
		return dynamic_cast<T*>(components[typeid(T)].get());
	}
	template<>
	DXTransform* GetComponent<DXTransform>()
	{
		if (nullptr != transform) return transform.get();
		return nullptr;
	}

	void Update();
	void Draw(const XMMATRIX& viewProjectionMatrix);

private:
	template<>
	DXTransform* AddComponent<DXTransform>()
	{
		if (nullptr != transform) return transform.get();

		transform = std::make_unique<DXTransform>(this);
		return transform.get();
	}
};