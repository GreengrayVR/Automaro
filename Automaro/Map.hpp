#pragma once
#include "MachineManager.hpp"

using Terrain = std::vector<std::vector<std::vector<std::unique_ptr<Object>>>>;

class IPlaceable;

class Map
{
public:
	Map(size_t width, size_t height);

	void Update(float deltaTime);
	size_t GetWdith() const;
	size_t GetHeight() const;
	Object* AddObject(std::unique_ptr<Object> object, const Vector& pos);
	IPlaceable* AddPlaceable(std::unique_ptr<IPlaceable> object, const Vector& pos);

	std::vector<std::unique_ptr<Object>>& GetObjectsInCell(const Vector& pos);
	
	template <typename T>
	ObjectIterator<T> GetObjectIteratorInCell(const Vector& pos)
	{
		return ObjectIterator<T>(GetObjectsInCell(pos));
	}
	
	void Move(Object* object, const Vector& pos);
	std::unique_ptr<Object> Release(const Vector& pos, int slot);

private:
	std::vector<IPlaceable*> m_vMachines;
	std::unique_ptr<size_t> m_sWidth;
	std::unique_ptr<size_t> m_sHeight;
	Terrain m_Terrain;
};
