#pragma once

template <typename T>
class ObjectIterator
{
    static_assert(std::is_base_of_v<Object, T>, "Type T does not inherit from Object");

public:

    ObjectIterator(std::vector<std::unique_ptr<Object>>& objects)
        : m_objects(objects)
        , m_it(objects.begin())
    {
    }

    [[nodiscard]]
    bool IsValid() const
    {
        if (!m_firstPassed)
            return false;

        if (m_it == m_objects.end())
            return false;

        return true;
    }

    [[nodiscard]]
    bool Next()
    {
        if (m_firstPassed)
            ++m_it;
        else
            m_firstPassed = true;

        while (true)
        {
            if (m_it == m_objects.end())
                return false;

            if (dynamic_cast<T*>(m_it->get()) == nullptr)
                ++m_it;
            else
                break;
        }

        return true;
    }

    [[nodiscard]]
    T* Get() const
    {
        assert(IsValid());

        return static_cast<T*>(m_it->get());
    }

    [[nodiscard]]
    std::unique_ptr<T> Release()
    {
        assert(IsValid());

        std::unique_ptr<T> tmp(static_cast<T*>(m_it->release()));
        m_it = m_objects.erase(m_it);

        return tmp;
    }

private:

    std::vector<std::unique_ptr<Object>>& m_objects;
    std::vector<std::unique_ptr<Object>>::iterator m_it;
    bool m_firstPassed = false;
};
