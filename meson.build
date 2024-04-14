project('Chip8_Emulator', 'cpp', default_options: ['cpp_std=c++17'])

sdl2_dep = dependency('sdl2', required: true, static: true)
# sdl2_main_dep = dependency('sdl2main', required: true, static: true)
sdl2_ttf_dep = dependency('sdl2_ttf', required: true, static: true)

incdir = include_directories('include')
src = ['src/main.cpp', 'src/chip8.cpp', 'src/instructions.cpp', 'src/window.cpp']

# if meson.get_compiler('cpp').get_id() == 'msvc'
#     extra_args = ['-std:c++17']
# else
#     extra_args = []
# endif

executable(
    'chip8',
    src,
    include_directories: incdir,
    # win_subsystem: 'windows',
    # cpp_args: extra_args,
    dependencies: [sdl2_dep, sdl2_ttf_dep]#, sdl2_main_dep]
)