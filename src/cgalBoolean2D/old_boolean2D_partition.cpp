#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/Partition_is_valid_traits_2.h>
// #include <CGAL/polygon_function_objects.h>
#include <CGAL/partition_2.h>
#include <list>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;

typedef CGAL::Partition_traits_2<Kernel>                    Traits;
typedef CGAL::Is_convex_2<Traits>                           Is_convex_2;
typedef Traits::Polygon_2                                   Polygon_2;
typedef Traits::Point_2                                     Point_2;
typedef Polygon_2::Vertex_const_iterator                    Vertex_iterator;
typedef std::list<Polygon_2>                                Polygon_list;
typedef CGAL::Partition_is_valid_traits_2<Traits, Is_convex_2> Validity_traits;


// typedef Kernel::Point_2                                   Point_2;
// typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;


#include "cgalBoolean2D/print_utils.h"

namespace epi {

struct vertex_2 {
public:
    vertex_2(double x, double y): x(x), y(y) {}

    double x;
    double y;
};

Polygon_2 genRegularPoly2(uint n, double r, double xcen, double ycen)
{
    Polygon_2 ret;
    for (uint i = 0; i < n; i++)
    {
        double theta = 2.0 * M_PI * (double)i / (double)n;
        ret.push_back(Point_2 (xcen + (r * cos(theta)),
                               ycen + (r * sin(theta)) ));
    }

    return ret;
}

}

using epi::genRegularPoly2;

int main ()
{
    // // Construct the two input polygons.
    // Polygon_2 P;
    // P.push_back (Point_2 (0, 0));
    // P.push_back (Point_2 (5, 0));
    // P.push_back (Point_2 (3.5, 1.5));
    // P.push_back (Point_2 (2.5, 0.5));
    // P.push_back (Point_2 (1.5, 1.5));
    // std::cout << "P = "; print_polygon (P);
    // Polygon_2 Q;
    // Q.push_back (Point_2 (0, 2));
    // Q.push_back (Point_2 (1.5, 0.5));
    // Q.push_back (Point_2 (2.5, 1.5));
    // Q.push_back (Point_2 (3.5, 0.5));
    // Q.push_back (Point_2 (5, 2));
    // std::cout << "Q = "; print_polygon (Q);


    Polygon_2 P(genRegularPoly2(6, 9, 0, 0)),
              Q(genRegularPoly2(6, 10, 0, 0));

    std::cout << "P = ";
    print_polygon(P);
    std::cout << "Q = ";
    print_polygon(Q);

    {
        // Compute the union of P and Q.
        Polygon_with_holes_2 unionR;
        if (CGAL::join(P, Q, unionR)) {
            std::cout << "The union: ";
            print_polygon_with_holes(unionR);
        }
        else
            std::cout << "P and Q are disjoint and their union is trivial."
                      << std::endl;
        std::cout << std::endl;
    }

    {
        // Compute the intersection of P and Q.
        Pwh_list_2 intR;
        CGAL::intersection(P, Q, std::back_inserter(intR));
        std::cout << "The intersection:" << std::endl;
        for (auto it = intR.begin(); it != intR.end(); ++it) {
            std::cout << "--> ";
            print_polygon_with_holes(*it);
        }
        std::cout << std::endl;
    }

    {
        // Compute the symmetric difference of P and Q.
        Pwh_list_2 diffR;
        CGAL::symmetric_difference(P, Q, std::back_inserter(diffR));
        std::cout << "The symmetric difference:" << std::endl;
        for (auto it = diffR.begin(); it != diffR.end(); ++it) {
            std::cout << "--> ";
            print_polygon_with_holes(*it);
        }
        std::cout << std::endl;
    }

    return 0;
}
