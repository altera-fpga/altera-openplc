# Add source files
aux_source_directory(algorithm SOURCE)
aux_source_directory(axis SOURCE)
aux_source_directory(fb SOURCE)
aux_source_directory(servo SOURCE)

# Create "RTmotion" library
add_library(${PROJECT_NAME} SHARED ${SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-unused-variable)
target_link_libraries(${PROJECT_NAME} PRIVATE ruckig::ruckig)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

