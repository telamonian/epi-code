#ifndef EPI_ITER_H
#define EPI_ITER_H

// #include <boost/iterator/zip_iterator.hpp>
// #include <boost/range/iterator_range.hpp>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

namespace epi {

// template<class... Conts>
// auto zip_range(Conts&... conts)
// -> decltype(boost::make_iterator_range(
//         boost::make_zip_iterator(boost::make_tuple(conts.begin()...)),
//         boost::make_zip_iterator(boost::make_tuple(conts.end()...))))
// {
//     return {boost::make_zip_iterator(boost::make_tuple(conts.begin()...)),
//             boost::make_zip_iterator(boost::make_tuple(conts.end()...))};
// }

template<typename T>
std::string tostr(const std::vector<T>& vec) {
    std::stringstream ss;
    ss << "[";
    for (auto&& i : vec) {
        ss << i << ", ";
    }
    ss << "]";

    return ss.str();
}

template<typename T>
const char* tocstr(const std::vector<T>& vec) {
    return tostr(vec).c_str();
    // return tostr(std::forward<std::vector<T> >(vec)).c_str();
}

}

#endif //EPI_ITER_H
