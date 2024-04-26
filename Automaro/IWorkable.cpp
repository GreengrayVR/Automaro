#include "pch.hpp"
#include "IWorkable.hpp"

IWorkable::IWorkable(World* world, int completeTime, Direction outputDir)
	: m_pWorld(world)
	, m_fTimeToComplete(completeTime)
	, m_fTime(completeTime)
	, m_bIsRunning(false)
{
}

IWorkable::~IWorkable()
{
}

void IWorkable::Update(float deltaTime)
{
	EarlyUpdate();

	if (!IsRunning()) return;

	m_fTime -= deltaTime;
	if (m_fTime < 0)
	{
		OnComplete();
		m_fTime = m_fTimeToComplete;
	}

	LateUpdate();
}

float IWorkable::GetTime() const
{
	return m_fTime;
}

float IWorkable::GetTimeToComplete() const
{
	return m_fTimeToComplete;
}

void IWorkable::SetRunning(bool running)
{
	m_bIsRunning = running;

	if (!m_bIsRunning)
	{
		m_fTime = m_fTimeToComplete;
	}
}

bool IWorkable::IsRunning() const
{
	return m_bIsRunning;
}

void IWorkable::Reset()
{
	SetRunning(false);
	m_fTime = m_fTimeToComplete;
}

std::unique_ptr<Item> IWorkable::TransferOutput()
{
	return std::move(m_ItemOutput);
}

bool IWorkable::TransferOutput(int count)
{
	if (!m_Output || !m_ItemOutput) return false;

	auto& input = m_ItemOutput;
	auto* output = m_Output->GetItemInput();

	if (!output)
	{
		m_Output->SetInput(input->CloneT<Item>());
		output = m_Output->GetItemInput();
		output->SetCount(0);
	}

	output->Transfer(input.get(), count);

	if (input->GetCount() <= 0)
	{
		std::unique_ptr<Item> tmp = std::move(input);
	}

	return true;
}

Item* IWorkable::GetItemOutput()
{
	return m_ItemOutput.get();
}

Item* IWorkable::GetItemInput()
{
	return m_ItemInput.get();
}

void IWorkable::SetOutput(IWorkable* output)
{
	m_Output = output;
}

void IWorkable::SetInput(std::unique_ptr<Item> input)
{
	m_ItemInput = std::move(input);
}

IWorkable* IWorkable::GetOutput()
{
	return m_Output;
}

ItemIOContainer::ItemIOContainer(const ItemIOContainer& other)
{
	if (other.m_ItemInput)
		m_ItemInput = other.m_ItemInput->CloneT<Item>();
	if (other.m_ItemOutput)
		m_ItemOutput = other.m_ItemOutput->CloneT<Item>();
}
