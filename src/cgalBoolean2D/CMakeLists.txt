set(boolean2D_src boolean2D.cpp)

add_executable(boolean2D ${boolean2D_src})

target_link_libraries(boolean2D CGAL::CGAL CGAL::CGAL_Core)
