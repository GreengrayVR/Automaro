#include "pch.hpp"
#include "IKeyboardHandler.hpp"

IKeyboardHandler::~IKeyboardHandler()
{
}

int IKeyboardHandler::GetPriority() const
{
    return m_iPriority;
}

void IKeyboardHandler::SetPriority(int priority)
{
    m_iPriority = priority;
}
