/// @file TraceInterface.hpp
/// @brief 
/// @author S. V. Paulauskas
/// @date February 29, 2020
//

#ifndef PIXIE_NET_TRACEINTERFACE_HPP
#define PIXIE_NET_TRACEINTERFACE_HPP

#include <map>
#include <vector>

class TraceInterface {
public:
 std::map<unsigned int, std::vector<int> > get_traces(volatile unsigned int *mapped);
};


#endif //PIXIE_NET_TRACEINTERFACE_HPP
