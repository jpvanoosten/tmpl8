#pragma once
#include <cstdint>

class Cell
{
public:
    int data = 0; // What is this? Anything we want!
};

class Grid
{
public:
    Grid(uint32_t width = 1u, uint32_t height = 1u);
    Grid(const Grid& grid);
    Grid(Grid&& grid) noexcept;
    ~Grid();

    Grid& operator=(const Grid& grid);
    Grid& operator=(Grid&& grid) noexcept;

    void resize(uint32_t width, uint32_t height);

    // Move semantics!

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    Cell* getData();
    const Cell* getData() const;

    Cell& getCell(size_t x, size_t y);
    const Cell& getCell(size_t x, size_t y) const;

private:
    void copy(const Cell* data, uint32_t width, uint32_t height);

    uint32_t m_width = 0u;
    uint32_t m_height = 0u;

    Cell* m_data = nullptr;
};

// Inline implementation.
inline uint32_t Grid::getWidth() const
{
    return m_width;
}

inline uint32_t Grid::getHeight() const
{
    return m_height;
}

inline Cell* Grid::getData()
{
    return m_data;
}

inline const Cell* Grid::getData() const
{
    return m_data;
}
