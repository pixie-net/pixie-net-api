# - Try to find ZeroMQ headers and libraries.
#
# Usage of this module as follows:
#
#     find_package(ZeroMQ)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  ZeroMQ_ROOT_DIR  Set this variable to the root installation of
#                    ZeroMQ if the module has problems finding
#                    the proper installation path.
#
# Variables defined by this module:
#
#  ZeroMQ_FOUND              System has ZeroMQ libs/headers
#  ZeroMQ_LIBRARIES          The ZeroMQ libraries
#  ZeroMQ_INCLUDE_DIR        The location of ZeroMQ headers
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp zmq.h
        HINTS /usr/include
        )
find_library(ZeroMQ
        NAMES  libzmq.so
        HINTS /usr/lib
        HINTS /usr/lib/arm-linux-gnueabihf/
        )

set(ZeroMQ_LIBRARIES ${ZeroMQ})
set(ZeroMQ_C_LIBRARIES ${ZeroMQ_C})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZeroMQ DEFAULT_MSG
        ZeroMQ_LIBRARIES
        ZeroMQ_INCLUDE_DIR)

mark_as_advanced(
        ZeroMQ_LIBRARIES
        ZeroMQ_INCLUDE_DIR)