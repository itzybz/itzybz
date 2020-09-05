file(GLOB tests "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

foreach(file ${tests})
  get_filename_component(name "${file}" NAME_WLE)

  # TODO Change to dynamic linkage; Static build for now 
  set(BUILD_SHARED_LIBS OFF)

  add_executable(${name})
  target_sources(${name} PRIVATE ${file})
  target_link_libraries(${name} PRIVATE ${PROJECT_NAME})
endforeach()
