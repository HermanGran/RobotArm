
function(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE threepp::threepp Catch2::Catch2WithMain Kinematics)
    target_include_directories(${name} PRIVATE "${PROJECT_SOURCE_DIR}/include")
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_test_executable(RobotArm_test)