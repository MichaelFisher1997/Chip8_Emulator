project('Chip8_Emulator', 'cpp', default_options: ['cpp_std=c++17'])

sdl2_dep = dependency('sdl2', required: true, static: true)
# sdl2_main_dep = dependency('sdl2main', required: true, static: true)
sdl2_ttf_dep = dependency('sdl2_ttf', required: true, static: true)
freetype2_dep = dependency('freetype2', required: true, static: true)

incdir = include_directories('include')
src = ['src/main.cpp', 'src/chip8.cpp', 'src/instructions.cpp', 'src/window.cpp']

executable(
    'chip8',
    src,
    include_directories: incdir,
    # win_subsystem: 'windows', # For windows?
    # cpp_args: extra_args,
    dependencies: [sdl2_dep, sdl2_ttf_dep]#, sdl2_main_dep]
)
    # dependencies: [sdl2_dep, sdl2_main_dep, sdl2_ttf_dep, freetype2_dep] # Windows?