project('click', 'cpp',
    default_options: 'cpp_std=c++17'
)

libevdev = dependency('libevdev')
libx11 = dependency('x11')
libxinput = dependency('xi')
libxtest = dependency('xtst')
libjsoncpp = dependency('jsoncpp', fallback: ['jsoncpp', 'jsoncpp_dep'])
libglfw = dependency('glfw3', fallback: ['glfw3', 'glfw_dep'])

src = files(
    'src/input/input.cpp',
    'src/input/input.hpp',
    'src/config/config.cpp',
    'src/config/config.hpp',
    'src/main.cpp'
)

executable('click', src, dependencies: [libevdev, libx11, libxinput, libxtest, libjsoncpp, libglfw])