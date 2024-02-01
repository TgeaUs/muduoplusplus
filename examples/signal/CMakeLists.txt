add_executable(signal signal.cc)
target_link_libraries(signal muduo_base muduo_net)

add_executable(signal2 signal2.cc)
target_link_libraries(signal2 muduo_base muduo_net)
