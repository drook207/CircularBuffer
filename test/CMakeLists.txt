# GoogleTest requires at least C++14

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT https://github.com/google/googletest.git
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include(GoogleTest)

add_executable(CircularBufferTest CircularBufferTest.cxx)
gtest_add_tests(TARGET      CircularBufferTest
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)


set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)

target_link_libraries(CircularBufferTest PRIVATE circularbuffer GTest::gtest_main)
