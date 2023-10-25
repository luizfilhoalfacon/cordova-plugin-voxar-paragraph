#ifndef __GUARD_LLAH_H__
#define __GUARD_LLAH_H__

#include <iostream>
#include <list>
#include <set>
#include <string>

#include "opencv2/core/core.hpp"

#include "geometry/point2.h"
#include "grid/grid_2d.h"
#include "hash_table/hash_table.h"

class PARagraph2 {
public:
    static const int RESOLUTION_MIN_VAL;
    
    enum Invariant { SRIF = 2, TRIANGLE_AREAS_RATIO = 4, CROSS_RATIO = 5 };
    
    virtual ~PARagraph2();
    
    PARagraph2(unsigned long hash_size, unsigned long n_pages, const std::string& page_common_filename,
              int n = 7, int m = 6, Invariant invariant = TRIANGLE_AREAS_RATIO, int q = 25,
              const std::vector<double>* discretization_thresholds = nullptr);
    
    PARagraph2(unsigned long hash_size, unsigned long n_pages, int n = 7, int m = 6,
              Invariant invariant = TRIANGLE_AREAS_RATIO, int q = 25,
              const std::vector<double>* discretization_thresholds = nullptr);
    
    bool store_document(const cv::Mat& in_image, document_id_type doc_id, bool prints = false);
    
    bool retrieve_document(const cv::Mat& in_image, document_id_type& retrieved_id,
                           cv::Mat& homography, float min_matches = 0.6f, bool prints = false);
    
    bool compute_thresholds(const std::vector<std::string>& filenames, int n_bins,
                            std::vector<double>& result) const;
    
    int n() const { return m_n; }
    int m() const { return m_m; }
    int f() const { return m_f; }
    int q() const { return m_q; }
    
    const Hash_Table& hash_table() const { return m_hash_table; }
    
    bool serialize(std::ostream& os);
    bool serialize(const std::string& filename);
    
    bool deserialize(std::istream& is, bool adjust_pages = true);
    bool deserialize(const std::string& filename, bool adjust_pages = true);
    
    const std::vector<double>& discretization_thresholds() const { return m_discretization_thresholds; }
    
    void set_discretization_thresholds(const std::vector<double>& thresholds);
    
private:
    static const int MIN_REQUIRED_VOTES;
    
    int m_n, m_m, m_f, m_q;
    Hash_Table m_hash_table;
    std::vector<double> m_discretization_thresholds;
    
    void init(const std::vector<double>* discretization_thresholds);
    
    void threshold_image(const cv::Mat& img, cv::Mat& result, bool inverted = false) const;
    
    double estimate_character_size(const cv::Mat& in_img) const;
    
    void compute_feature_points(const cv::Mat& in_image, std::list<Point2>& feature_points,
                                Grid_2D& grid) const;
    
    void find_nearest_points(const Point2& p, const Grid_2D& grid, std::vector<Point2>& dest) const;
    
    void combinations(const std::vector<Point2>& elements, std::vector<std::vector<Point2>>& dest) const;
    
    void lexicographical_combinations(const std::vector<Point2>& origin,
                                      std::vector<std::vector<Point2>>& dest) const;
    
    int discretize_feature(double val) const;
    
    unsigned long hash_function2(const std::vector<int>& feature_vector) const;
    
    double triangle_areas_ratio_invariant(const Point2& p0, const Point2& p1, const Point2& p2,
                                          const Point2& p3) const;
    
    double cross_ratio_invariant(const Point2& p0, const Point2& p1, const Point2& p2,
                                 const Point2& p3, const Point2& p4) const;
    
    double srif_invariant(const Point2& feature_point, const Point2& p0, const Point2& p1) const;
    
    double compute_feature(const Point2& feature_point, const std::vector<Point2>& points) const;
    
    void adjust_initial_point(const Point2& feature_point, std::vector<Point2>& points) const;
    
    void compute_hash_values(std::list<Point2>::const_iterator feature_points_begin,
                             std::list<Point2>::const_iterator feature_points_end, const Grid_2D* grid,
                             std::list<std::list<unsigned long>>::iterator hash_values_begin,
                             std::list<std::list<unsigned long>>::iterator hash_values_end, 
                             std::vector<double>* invariant_values = nullptr) const;
    
    void delaunay_triangulate(const std::vector<cv::Point2f>& points,
                              std::vector<std::set<int>>& graph);
};


#endif
