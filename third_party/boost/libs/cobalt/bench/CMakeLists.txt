
add_executable(boost_cobalt_post_bench post.cpp)
target_link_libraries(boost_cobalt_post_bench PRIVATE Boost::cobalt Boost::system Threads::Threads)
if (TARGET Boost::context)
    target_link_libraries(boost_cobalt_post_bench PRIVATE Boost::context)
    target_compile_definitions(boost_cobalt_post_bench PRIVATE BOOST_COBALT_BENCH_WITH_CONTEXT=1)
    set_property(TARGET boost_cobalt_post_bench PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

add_executable(boost_cobalt_immediate_bench immediate.cpp)
target_link_libraries(boost_cobalt_immediate_bench PRIVATE Boost::cobalt Boost::system Threads::Threads)
if (TARGET Boost::context)
    target_link_libraries(boost_cobalt_immediate_bench PRIVATE Boost::context)
    target_compile_definitions(boost_cobalt_immediate_bench PRIVATE BOOST_COBALT_BENCH_WITH_CONTEXT=1)
    set_property(TARGET boost_cobalt_immediate_bench PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

add_executable(boost_cobalt_channel_bench channel.cpp)
target_link_libraries(boost_cobalt_channel_bench PRIVATE Boost::cobalt Boost::system Threads::Threads)
if (TARGET Boost::context)
    target_link_libraries(boost_cobalt_channel_bench PRIVATE Boost::context)
    target_compile_definitions(boost_cobalt_channel_bench PRIVATE BOOST_COBALT_BENCH_WITH_CONTEXT=1)
    set_property(TARGET boost_cobalt_channel_bench PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

add_executable(boost_cobalt_parallel_bench parallel.cpp)
target_link_libraries(boost_cobalt_parallel_bench PRIVATE Boost::cobalt Boost::system Threads::Threads)
if (TARGET Boost::context)
    target_link_libraries(boost_cobalt_parallel_bench PRIVATE Boost::context)
    target_compile_definitions(boost_cobalt_parallel_bench PRIVATE BOOST_COBALT_BENCH_WITH_CONTEXT=1)
    set_property(TARGET boost_cobalt_parallel_bench PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()



add_executable(boost_cobalt_monotonic_bench monotonic.cpp)
target_link_libraries(boost_cobalt_monotonic_bench PRIVATE Boost::cobalt Boost::system Threads::Threads)
if (TARGET Boost::context)
    target_link_libraries(boost_cobalt_monotonic_bench PRIVATE Boost::context)
    target_compile_definitions(boost_cobalt_monotonic_bench PRIVATE BOOST_COBALT_BENCH_WITH_CONTEXT=1)
    set_property(TARGET boost_cobalt_monotonic_bench PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()
