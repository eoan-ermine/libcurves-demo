install(
    TARGETS libcurves-demo_exe
    RUNTIME COMPONENT libcurves-demo_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
