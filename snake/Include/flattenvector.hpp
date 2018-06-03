#pragma once
#include <vector>

namespace Model
{

template<typename T>
class FlattenVector
{
public:
    FlattenVector(unsigned rows, unsigned cols, const T& initialValue):
        m_rows(rows), m_cols(cols),
        m_values(m_rows*m_cols, initialValue)
    {}

    T& get(size_t x, size_t y)
    {
        if(x >= m_rows or y >= m_cols)
        {
            throw std::out_of_range("FlattenVector::get");
        }
        return m_values[x + y*m_cols];
    }

    const T& get(size_t x, size_t y) const
    {
        if(x >= m_rows or y >= m_cols)
        {
            throw std::out_of_range("FlattenVector::get");
        }
        return m_values[x + y*m_cols];
    }

private:
    const size_t m_rows;
    const size_t m_cols;
    std::vector<T> m_values;
};

}
