project(
  'click',
  ['c', 'cpp'],
  default_options: [
    'cpp_std=c++17',
    'default_library=static',
  ],
  version: '0.1.0'
)

cc = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')

libsdl2 = subproject('sdl2')
libjson = subproject('jsoncpp')

libglad = static_library(
    'glad',
    'extra/glad/src/glad.c',
    include_directories: include_directories('extra/glad/include')
)

libimgui = static_library(
    'imgui',
    [
        'extra/imgui/imgui.cpp',
        'extra/imgui/imgui_draw.cpp',
        'extra/imgui/imgui_tables.cpp',
        'extra/imgui/imgui_widgets.cpp',
        'extra/imgui/backends/imgui_impl_opengl3.cpp',
        'extra/imgui/backends/imgui_impl_sdl2.cpp'
    ],
    dependencies: libsdl2.get_variable('sdl2_dep'),
    include_directories: [include_directories('extra/imgui/')]
)

# wrap shit
deps = [
  libsdl2.get_variable('sdl2_dep'),
  libjson.get_variable('jsoncpp_dep')
]

host_system = host_machine.system()
if host_system == 'linux'
    deps += dependency('x11')
    deps += dependency('xi')
    deps += dependency('xtst')
else
endif

src_files = [
  'src/input/input.cpp',
  'src/config/config.cpp',
  'src/gui/gui.cpp',
  'src/main.cpp'
]

executable(
  'click',
  src_files,
  link_with: [libglad, libimgui],
  include_directories: [include_directories('extra/glad/include'), include_directories('extra/imgui/')],
  dependencies: [deps]
)