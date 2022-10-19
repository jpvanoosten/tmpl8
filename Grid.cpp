#include "Grid.h"

#include <cassert>
#include <cstring>
#include <map>

Grid::Grid(uint32_t width, uint32_t height)
    : m_width{ width }
    , m_height{ height }
{
    m_data = new Cell[static_cast<uint64_t>(m_width) * m_height];
}

Grid::Grid(const Grid& grid)
{
    copy(grid.m_data, grid.m_width, grid.m_height);
}

Grid::Grid(Grid&& grid) noexcept
    : m_width{grid.m_width}
    , m_height{grid.m_height}
    , m_data{grid.m_data}
{
    grid.m_data = nullptr;
    grid.m_width = 0;
    grid.m_height = 0;
}

Grid::~Grid()
{
    delete[] m_data;
}

Grid& Grid::operator=(const Grid& grid)
{
    if (this == &grid) return *this;

    copy(grid.m_data, grid.m_width, grid.m_height);

    return *this;
}

Grid& Grid::operator=(Grid&& grid) noexcept
{
    if(this == &grid) return *this;

    delete[] m_data;
    m_data = nullptr;
    std::swap(m_data, grid.m_data);

    m_width = grid.m_width;
    m_height = grid.m_height;

    grid.m_width = 0;
    grid.m_height = 0;

    return *this;
}

void Grid::resize(uint32_t width, uint32_t height)
{
    if (width != m_width || height != m_height)
    {
        delete[] m_data;
    }

    m_width = width;
    m_height = height;

    m_data = new Cell[static_cast<uint64_t>(width) * height];
}

Cell& Grid::getCell(size_t x, size_t y)
{
    assert(x < m_width);
    assert(y < m_height);

    const size_t i = y * m_width + x;
    return m_data[i];
}

const Cell& Grid::getCell(size_t x, size_t y) const
{
    assert(x < m_width);
    assert(y < m_height);

    const size_t i = y * m_width + x;
    return m_data[i];
}

void Grid::copy(const Cell* data, uint32_t width, uint32_t height)
{
    delete[] m_data;
    m_width = width;
    m_height = height;

    m_data = new Cell[static_cast<size_t>(m_width) * m_height];
    const size_t sizeInBytes = static_cast<size_t>(m_width) * m_height * sizeof(Cell);

    memcpy_s(m_data, sizeInBytes, data, sizeInBytes);
}
