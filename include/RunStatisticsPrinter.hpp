/// @file RunStatisticsPrinter.hpp
/// @brief 
/// @author S. V. Paulauskas
/// @date March 07, 2020
#ifndef PIXIE_NET_RUNSTATISTICSPRINTER_HPP
#define PIXIE_NET_RUNSTATISTICSPRINTER_HPP

#include "RunStatistics.hpp"

#include <string>

class RunStatisticsPrinter {
public:
    void print_statistics(const RunStatistics &stats);
private:
    std::string format_channel_for_json(const unsigned int &channel, const RunStatistics &stats) const;
};

#endif //PIXIE_NET_RUNSTATISTICSPRINTER_HPP
