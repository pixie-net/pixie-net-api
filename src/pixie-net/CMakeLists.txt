set(API_FILE_LIST PixieNetConfig.cpp PixieNetCommon.cpp ProgramFippi.cpp)

add_library(PixieNetApi_STATIC STATIC ${API_FILE_LIST})
add_library(PixieNetApi SHARED ${API_FILE_LIST})
install(TARGETS PixieNetApi DESTINATION lib)
