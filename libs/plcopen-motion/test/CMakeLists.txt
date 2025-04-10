if(TEST)
  # Create scurve test executable
  add_executable(offline_scurve_test offline_scurve_test.cpp)
  target_link_libraries(offline_scurve_test
    RTmotion
    ${GTEST_BOTH_LIBRARIES}
    ${PYTHON_LIBRARIES}
    -lpthread
  )

  # Create scurve test executable
  add_executable(online_scurve_test online_scurve_test.cpp)
  target_link_libraries(online_scurve_test
    RTmotion
    ${GTEST_BOTH_LIBRARIES}
    ${PYTHON_LIBRARIES}
    -lpthread
  )

  # Create planner test executable
  add_executable(planner_test planner_test.cpp)
  target_link_libraries(planner_test
    RTmotion
    ${GTEST_BOTH_LIBRARIES}
    ${PYTHON_LIBRARIES}
    -lpthread
  )

  # Create function block test executable
  add_executable(function_block_test function_block_test.cpp)
  target_link_libraries(function_block_test
    RTmotion
    ${GTEST_BOTH_LIBRARIES}
    ${PYTHON_LIBRARIES}
    -lpthread
  )

  # Install test executables
  install(TARGETS offline_scurve_test online_scurve_test planner_test function_block_test
          RUNTIME DESTINATION ${INSTALL_BINDIR}
  )
endif(TEST)

