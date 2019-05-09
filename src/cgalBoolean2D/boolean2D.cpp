#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_vertical_decomposition_2.h>
#include <cmath>
#include <list>


typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2                                   Point_2;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
typedef std::list<Polygon_2>                              P_list_2;
typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;
typedef CGAL::Polygon_vertical_decomposition_2<Kernel>    Decomposition;


#include "cgalBoolean2D/print_utils.h"

namespace epi {

struct vertex_2 {
public:
    vertex_2(double x, double y): x(x), y(y) {}

    double x;
    double y;
};

Polygon_2 regularPoly2(uint n, double r, double xcen, double ycen)
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

template <typename Polygon_, typename... Args>
P_list_2 diffRegular2(Polygon_&& field, Args... args) {
    P_list_2 polys = {args...};
    //TODO: fix the return value
    if (polys.empty()) return polys;

    Pwh_list_2 holedPolys;
    CGAL::symmetric_difference(field, polys.front(), std::back_inserter(holedPolys)); polys.pop_front();
    Polygon_with_holes_2* fieldPtr = &(holedPolys.back());
    for (auto&& poly: polys) {
        CGAL::symmetric_difference(*fieldPtr, poly, std::back_inserter(holedPolys));
        holedPolys.pop_front();
        fieldPtr = &(holedPolys.back());
    }

    P_list_2 decompPolys;
    Decomposition decomp;

    decomp(*fieldPtr, std::back_inserter(decompPolys));

    std::cout << "The decomposition of the symmetric difference of regular polygons:" << std::endl;
    print_decomp(decompPolys);
    std::cout << std::endl;

    return decompPolys;
};

}

using epi::regularPoly2;
using epi::diffRegular2;

int main () {
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


    Polygon_2 P(regularPoly2(6, 9, 0, 0)),
            Q(regularPoly2(6, 10, 0, 0));

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

        P_list_2 decompR;
        Decomposition decomp;

        for (auto it = diffR.begin(); it != diffR.end(); ++it) {
            decomp(*it, std::back_inserter(decompR));
        }

        std::cout << "The decomposition of the symmetric difference:" << std::endl;
        print_decomp(decompR);
        std::cout << std::endl;
    }

    {
        double smallrad = 1.2;
        double smallcount = 3;
        double gutter = .5;

        double smallheight = sqrt(3)*smallrad;
        double yshift = sqrt(3)*smallrad + gutter;
        double yshift2 = yshift/2;
        double xshift = (sqrt(3)/2)*(sqrt(3)*smallrad + gutter);
        double bigrad = smallrad*smallcount + ((smallcount + 1)/sqrt(3))*gutter;

        std::cout << "smallheight: " << smallheight << '\n';
        std::cout << "yshift: " << yshift << '\n';
        std::cout << "yshift2: " << yshift2 << '\n';
        std::cout << "xshift: " << xshift << '\n';
        std::cout << "bigrad: " << bigrad << '\n';

        diffRegular2(regularPoly2(6, bigrad, 0, 0),
                     regularPoly2(6, 1, -2*xshift, 0),
                     regularPoly2(6, 1, -1.5*xshift, -.75*yshift),

                     // left row
                     regularPoly2(6, 1, -xshift, -yshift2 - yshift),
                     // regularPoly2(6, 1, -xshift, -yshift2),
                     regularPoly2(6, 1, -xshift, yshift2),
                     regularPoly2(6, 1, -xshift, yshift2 + yshift),

                     // middle row
                     regularPoly2(6, 1, 0, yshift2 + yshift),
                     // regularPoly2(6, 1, 0, yshift),
                     regularPoly2(6, 1, 0, 0),
                     regularPoly2(6, 1, 0, -yshift),

                     // right row
                     regularPoly2(6, 1, xshift, -yshift2 - yshift),
                     // regularPoly2(6, 1, xshift, -yshift2),
                     regularPoly2(6, 1, xshift, yshift2),
                     regularPoly2(6, 1, xshift, yshift2 + yshift),

                     regularPoly2(6, 1, 2*xshift, 0),
                     regularPoly2(6, 1, 1.5*xshift, -.75*yshift));
    }

    return 0;
}