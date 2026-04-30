find_package(GTest CONFIG REQUIRED)

add_executable(unit_tests 
    test_smart_resource.cpp
    ../../repositorio-extra/atividade-extra59/SmartResource.cpp
)

target_link_libraries(unit_tests PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(unit_tests PRIVATE ../../repositorio-extra/atividade-extra59)

# Registrar o teste no CTest
enable_testing()
add_test(NAME SmartResourceTests COMMAND unit_tests)
