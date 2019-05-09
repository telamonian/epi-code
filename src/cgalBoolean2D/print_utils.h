#ifndef CGAL_PRINT_UTILS_H
#define CGAL_PRINT_UTILS_H

#include <CGAL/Polygon_with_holes_2.h>
#include <iostream>

//-----------------------------------------------------------------------------
// Pretty-print a CGAL polygon.
//
template<class Kernel, class Container>
void print_polygon (const CGAL::Polygon_2<Kernel, Container>& P, const std::string& name="", const std::string& end="")
{
    typename CGAL::Polygon_2<Kernel, Container>::Vertex_const_iterator  vit;

    if (not name.empty()) std::cout << name << ": ";
    std::cout << "[";
    for (vit = P.vertices_begin(); vit != P.vertices_end(); ++vit)
        std::cout << "[" << vit->x() << ", " << vit->y() << "], ";
    std::cout << "]" << end;

    return;
}

template<template <typename, typename> class PContainer, class Kernel, class Container, class A>
void print_decomp (const PContainer<CGAL::Polygon_2<Kernel, Container>, A>& P)
{
    std::cout << "[";
    for (auto&& p : P) {
        print_polygon(p, "", ",\n");
    }
    std::cout << "]";

    return;
}

//-----------------------------------------------------------------------------
// Pretty-print a polygon with holes.
//
template<class Kernel, class Container>
void print_polygon_with_holes
        (const CGAL::Polygon_with_holes_2<Kernel, Container>& pwh)
{
    if (! pwh.is_unbounded())
    {
        std::cout << "{ Outer boundary = ";
        print_polygon (pwh.outer_boundary());
    }
    else
        std::cout << "{ Unbounded polygon." << std::endl;

    typename CGAL::Polygon_with_holes_2<Kernel,Container>::
    Hole_const_iterator  hit;
    unsigned int                                                     k = 1;

    std::cout << "  " << pwh.number_of_holes() << " holes:" << std::endl;
    for (hit = pwh.holes_begin(); hit != pwh.holes_end(); ++hit, ++k)
    {
        std::cout << "    Hole #" << k << " = ";
        print_polygon (*hit);
    }
    std::cout << " }" << std::endl;

    return;
}

#endif
