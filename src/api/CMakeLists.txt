set(API_SOURCE_LIST
        ConfigurationFileParser.cpp
        PixieNetConfig.cpp
        PixieNetCommon.cpp
        ProgramFippi.cpp
        )

add_library(PixieNetApi_STATIC STATIC ${API_SOURCE_LIST})
add_library(PixieNetApi SHARED ${API_SOURCE_LIST})
install(TARGETS PixieNetApi DESTINATION lib)
