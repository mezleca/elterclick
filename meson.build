# TODO:
# this shit is a mess, gonna learn meson a little more so i can remake this

project(
    'click', 
    'c', 
    'cpp',
    default_options: 'cpp_std=c++17'
)

inc_glad = include_directories('dependencies/glad/include')
inc_imgui = include_directories('dependencies/imgui/')

libevdev = dependency('libevdev')
libx11 = dependency('x11')
libxinput = dependency('xi')
libxtest = dependency('xtst')
libjsoncpp = dependency('jsoncpp', fallback: ['jsoncpp', 'jsoncpp_dep'])
libglfw = dependency('glfw3', fallback: ['glfw3', 'glfw_dep'])
libglad = static_library(
    'glad',
    'dependencies/glad/src/glad.c',
    include_directories: inc_glad
)
libimgui = static_library(
    'imgui',
    [
        'dependencies/imgui/imgui.cpp',
        'dependencies/imgui/imgui_draw.cpp',
        'dependencies/imgui/imgui_tables.cpp',
        'dependencies/imgui/imgui_widgets.cpp',
        'dependencies/imgui/imgui_impl_opengl3.cpp',
        'dependencies/imgui/imgui_impl_glfw.cpp'
    ],
    include_directories: inc_imgui
)

src = files(
    'src/input/input.cpp',
    'src/input/input.hpp',
    'src/config/config.cpp',
    'src/config/config.hpp',
    'src/gui/gui.cpp',
    'src/gui/gui.hpp',
    'src/main.cpp'
)

executable(
    'click', 
    src, 
    dependencies: [libevdev, libx11, libxinput, libxtest, libjsoncpp, libglfw],
    link_with: [libglad, libimgui],
    include_directories: [inc_glad, inc_imgui]
)