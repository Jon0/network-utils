add_definitions(-std=c++14)

# executable names
set(CLIENT_NAME "nclient")
set(SERVER_NAME "nserver")

# executable files
file(GLOB SERVER_FILES
	"server.cpp"
)

add_executable(
	${SERVER_NAME}
	${SERVER_FILES}
)

target_link_libraries(
	${SERVER_NAME}
	${NET_LIBRARY_NAME}
)
