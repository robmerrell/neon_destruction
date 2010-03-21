require "rake"

desc "A quick and dirty compile, not suitable for large projects."
task :compile do
  # generate the compiler and linker flags
  flags = [
    "-Wno-write-strings",
    "-g",
    `sdl-config --cflags`.strip,
    `sdl-config --libs`.strip,
    "-I/System/Library/Frameworks/OpenGL.framework/Headers",
    "-framework OpenGL",
    "-Lsrc/projection_engine/chipmunk/lib",
    "-lchipmunk"
  ]
  
  # get a list of cpp files to compile
  files = Dir.glob("src/**/*.cpp")
  files << "utils/SDLMain.m"
  
  output_name = "main"
  
  # compile the files
  compile_cmd = "g++ #{files.join(' ')} #{flags.join(' ')} -o #{output_name}"
  puts compile_cmd
  system(compile_cmd)
end