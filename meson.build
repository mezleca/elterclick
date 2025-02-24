project('click', 'cpp',
    default_options: 'cpp_std=c++17'
)

libevdev = dependency('libevdev')
libudev = dependency('libudev')
libinput = dependency('libinput')
libx11 = dependency('x11')
libxinput = dependency('xi')

# TODO: better way to include extra dependencies
src = files(
    'src/input/input.cpp',
    'src/input/input.hpp',
    'src/main.cpp',
    'dependencies/json/json.cpp',
    'dependencies/json/json.hpp'
)

executable('click', src, dependencies: [libevdev, libudev, libinput, libx11, libxinput])