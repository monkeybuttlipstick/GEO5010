#include <iostream>
#include <boost/filesystem.hpp>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h>
#include <chrono>
#include <CGAL/boost/graph/Face_filtered_graph.h>
#include <CGAL/boost/graph/IO/polygon_mesh_io.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <cmath>   // for HUGE_VAL
#include <CGAL/Polygon_mesh_processing/measure.h>



typedef CGAL::Simple_cartesian<double>                           K;
typedef K::Point_3                                               Point_3;
typedef CGAL::Surface_mesh<Point_3>                              SM;
typedef SM::Property_map<SM::Vertex_index, std::size_t>          Vertex_id_map;
typedef SM::Property_map<SM::Face_index, std::size_t>            Face_id_map;
typedef CGAL::Face_filtered_graph<SM>                            Filtered_graph;


namespace SMS = CGAL::Surface_mesh_simplification;
namespace PMP = CGAL::Polygon_mesh_processing;

int main()
{
    std::string file = "4_0.off";
    const std::string filename = CGAL::data_file_path("../original_data/"+ file);
    SM sm;
    if(!CGAL::Polygon_mesh_processing::IO::read_polygon_mesh(filename, sm))
    {
        std::cerr << "Invalid input." << std::endl;
        return 1;
    }

    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    // The simplification stops when the number of undirected edges
    // drops below 50% of the initial count
    double stop_ratio = 0.41;
    SMS::Count_ratio_stop_predicate<SM> stop(stop_ratio);
    int r = SMS::edge_collapse(sm, stop);
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();


    std::cout << "\nFinished!\n" << sm.number_of_vertices() << " final vertices.\n";
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms" << std::endl;
    CGAL::IO::write_polygon_mesh("../edge_collapse_data/" + file, sm, CGAL::parameters::stream_precision(17));

    return EXIT_SUCCESS;
}


