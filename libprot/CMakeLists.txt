add_definitions(-std=c++14)

# main library cpp files
file(GLOB SRC_FILES
	"*.cpp"
)

file(GLOB INCLUDE_FILES
	"*.h"
)

add_library(
	${PROT_LIBRARY_NAME}
	SHARED
	${SRC_FILES}
	${INCLUDE_FILES}
)

target_link_libraries(
	${PROT_LIBRARY_NAME}
	${CMAKE_THREAD_LIBS_INIT}
	${CMAKE_DL_LIBS}
	${UNIX_LIBRARY_NAME}
)
