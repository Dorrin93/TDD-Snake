#pragma once
#include <vector>

namespace Model
{

template<typename T>
class FlattenVector
{
public:
    FlattenVector(unsigned cols, unsigned rows, const T& initialValue):
        m_cols(cols), m_rows(rows),
        m_values(m_rows*m_cols, initialValue)
    {}

    T& get(size_t x, size_t y)
    {
        if(x >= m_cols or y >= m_rows)
        {
            throw std::out_of_range("FlattenVector::get");
        }
        return m_values[x + y*m_cols];
    }

    const T& get(size_t x, size_t y) const
    {
        if(x >= m_cols or y >= m_rows)
        {
            throw std::out_of_range("FlattenVector::get");
        }
        return m_values[x + y*m_cols];
    }

    void fill(const T& value)
    {
        std::fill(std::begin(m_values), std::end(m_values), value);
    }

private:
    const size_t m_cols;
    const size_t m_rows;
    std::vector<T> m_values;
};

}
