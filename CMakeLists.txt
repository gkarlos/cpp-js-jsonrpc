project(cpp-js-jsonrpc)

add_executable(server server.cpp)
target_link_libraries(server cxxtools cxxtools-json cxxtools-http)