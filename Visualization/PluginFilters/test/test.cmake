# --> TestPlugin : QtPlugin [BEGIN]
OPTION(BUILD_USE_GUI_TestPlugin "BUILD TestPlugin " ON)
if (BUILD_USE_GUI_TestPlugin)
  set(Test_Qt_Plugin_HEADER "${PROJECT_SOURCE_DIR}/Visualization/PluginFilters/test/TestPlugin.h" "${PROJECT_SOURCE_DIR}/Visualization/PluginFilters/test/Dialogs/DialogTest1.h")
  set(Test_Qt_Plugin_UI "${PROJECT_SOURCE_DIR}/Visualization/PluginFilters/test/Dialogs/DialogTest1.ui")
  if (BUILD_USE_QT5)
    QT5_WRAP_CPP(Test_Qt_Plugin_MOC_CPP ${Test_Qt_Plugin_HEADER})
    QT5_WRAP_UI(Test_Qt_Plugin_UI_CPP ${Test_Qt_Plugin_UI})
    set(Test_Qt_Plugin_SRC ${Test_Qt_Plugin_SRC} ${Test_Qt_Plugin_MOC_CPP} ${Test_Qt_Plugin_UI_CPP})
  else(BUILD_USE_QT5)
    QT4_WRAP_CPP(Test_Qt_Plugin_MOC_CPP ${Test_Qt_Plugin_HEADER})
    QT4_WRAP_UI(Test_Qt_Plugin_UI_CPP ${Test_Qt_Plugin_UI})
    set(Test_Qt_Plugin_SRC ${Test_Qt_Plugin_SRC} ${Test_Qt_Plugin_MOC_CPP} ${Test_Qt_Plugin_UI_CPP})
  endif(BUILD_USE_QT5)

  add_library(TestPlugin SHARED "${PROJECT_SOURCE_DIR}/Visualization/PluginFilters/test/testPlugin.cpp" "${PROJECT_SOURCE_DIR}/Visualization/PluginFilters/test/Dialogs/DialogTest1.cpp"
    ${Test_Qt_Plugin_SRC}
    ${osgQt_SRC} # from viewer
    )
  target_link_libraries (TestPlugin ${Test_Qt_Plugin_LIB}
    ${GUILIB_DEMO} # from viewer
    )
  add_dependencies(TestPlugin mepp-gui)
endif (BUILD_USE_GUI_TestPlugin)
# --> TestPlugin : QtPlugin [END]
