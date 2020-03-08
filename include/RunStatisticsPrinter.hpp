/// @file RunStatisticsPrinter.hpp
/// @brief 
/// @author S. V. Paulauskas
/// @date March 07, 2020
#ifndef PIXIE_NET_RUNSTATISTICSPRINTER_HPP
#define PIXIE_NET_RUNSTATISTICSPRINTER_HPP

#include <string>

#include "RunStatistics.hpp"

class RunStatisticsPrinter {
public:
    std::string format_stats_as_json(const RunStatistics &stats);

private:
    std::string format_channel_for_json(const unsigned int &channel, const RunStatistics &stats) const;
};

#endif //PIXIE_NET_RUNSTATISTICSPRINTER_HPP
