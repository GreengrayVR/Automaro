#include "pch.hpp"
#include "Map.hpp"

Map::Map(size_t width, size_t height)
	: m_Terrain(Terrain(height))
	, m_sWidth(std::make_unique<size_t>(width))
	, m_sHeight(std::make_unique<size_t>(height))
{
	for (size_t y = 0; y < m_Terrain.size(); y++)
	{
		m_Terrain[y].resize(width);
	}
}

Object* Map::AddObject(std::unique_ptr<Object> object, const Vector& pos)
{
	Transform& transform = const_cast<Transform&>(object->GetTransform());
	transform.SetPosition(pos);

	return m_Terrain[pos.y][pos.x].emplace_back(std::move(object)).get();
}

IPlaceable* Map::AddPlaceable(std::unique_ptr<IPlaceable> object, const Vector& pos)
{
	Transform& transform = const_cast<Transform&>(object->GetTransform());
	transform.SetPosition(pos);

	m_vPlaceable.emplace_back(object.get())->OnPlace();

	return static_cast<IPlaceable*>(m_Terrain[pos.y][pos.x].emplace_back(std::move(object)).get());
}

std::vector<std::unique_ptr<Object>>& Map::GetObjectsInCell(const Vector& pos)
{
	return m_Terrain[pos.y][pos.x];
}

void Map::Move(Object* object, const Vector& pos)
{
	Vector oldPos = object->GetTransform().GetPosition();

	auto& cells = m_Terrain[oldPos.y][oldPos.x];
	auto& newCells = m_Terrain[pos.y][pos.x];

	//for (auto& cell : newCells)
	//	if (cell.get()->IsSolid())
	//		return;

	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].get() == object)
		{
			AddObject(Release(oldPos, i), pos);
			return;
		}
	}

	assert(false && "Object has to be on map");
}

[[nodiscard]]
std::unique_ptr<Object> Map::Release(const Vector& pos, int slot)
{
	auto object = std::move(m_Terrain[pos.y][pos.x][slot]);
	m_Terrain[pos.y][pos.x].erase(m_Terrain[pos.y][pos.x].begin() + slot);

	RemovePlaceable(object.get());

	Transform& transform = const_cast<Transform&>(object->GetTransform());
	transform.SetPosition({-1, -1});

	return object;
}

void Map::RemovePlaceable(Object* placeable, bool schedule)
{
	auto it = std::ranges::find(m_vPlaceable, placeable);
	if (it == m_vPlaceable.end()) return;

	if (schedule)
		m_vPlaceableRemoveScheduler.push_back(it);
	else
		m_vPlaceable.erase(it);
}

void Map::RemovePlaceables()
{
	if (m_vPlaceableRemoveScheduler.empty()) return;

	for (auto& placeable : m_vPlaceableRemoveScheduler)
		m_vPlaceable.erase(placeable);

	m_vPlaceableRemoveScheduler.clear();
}

void Map::Update(float deltaTime)
{
	for (auto placeable : m_vPlaceable)
		if (IWorkable* workable = dynamic_cast<IWorkable*>(placeable))
			workable->Update(deltaTime);

	RemovePlaceables();
}

size_t Map::GetWdith() const
{
	return *m_sWidth;
}

size_t Map::GetHeight() const
{
	return *m_sHeight;
}

std::vector<IPlaceable*>& Map::GetPlaceables()
{
	return m_vPlaceable;
}

IPlaceable* Map::GetPlaceable(const Vector& pos)
{
	auto it = std::find_if(
		m_vPlaceable.begin(),
		m_vPlaceable.end(),
		[&pos](IPlaceable* p) {
			return p->GetTransform().GetPosition() == pos;
		}
	);

	return it == m_vPlaceable.end() ? nullptr : *it;
}
