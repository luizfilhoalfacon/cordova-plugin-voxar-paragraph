#ifndef __GUARD_GRID_H__
#define __GUARD_GRID_H__

#include <algorithm>
#include <vector>
#include <unordered_map>

#include "../geometry/point2.h"
#include "../geometry/vector2.h"

class Grid_2D {
public:
    Grid_2D() : m_cell_size_x(0.f), m_cell_size_y(0.f), m_num_cells(Index2(0, 0)), m_origin(Point2(0, 0)) {}
    Grid_2D(const Point2& bottom_left, float cell_size_x, float cell_size_y, int num_cells_x, int num_cells_y);
    Grid_2D(const Point2& bottom_left, const Point2& top_right, int num_cells_x, int num_cells_y);

    bool insert(const Point2* p);

    void find_neighbors(const Point2& p, int n, std::vector<const Point2*>& dest) const;

private:
    struct Index2 {
        int x, y;
        Index2(int x, int y) : x(x), y(y) {}
    };

    typedef std::vector<const Point2*> Cell;

    float m_cell_size_x, m_cell_size_y;
    Index2 m_num_cells;
    Point2 m_origin;
    std::unordered_map<int, Cell> m_cell_hash_table;

    int hash_key(const Index2& i) const { return i.x + (m_num_cells.x * i.y); }

    Index2 cell_index(const Point2& p) const;

    bool in_bounds(const Index2& i) const;

    void report_points(const Index2& i, std::vector<const Point2*>& dest) const;
};

#endif
