require "rake"

desc "A quick and dirty compile, not suitable for large projects."
task :compile do
  # generate the compiler and linker flags
  flags = [
    "-Wno-write-strings",
    "-g",
    "-I/opt/PalmPDK/include",
    "-I/opt/PalmPDK/include/SDL",
    "-L/opt/PalmPDK/host/lib",
    "-framework cocoa",
    "-arch i386",
    "-Lsrc/projection_engine/chipmunk/lib",
    "-lchipmunk",
    "-lSDL",
    "-lSDLmain",
    "-lGLESv2"
  ]
  
  # get a list of cpp files to compile
  files = Dir.glob("src/**/*.cpp")
  
  output_name = "main"
  
  # compile the files
  compile_cmd = "g++ #{files.join(' ')} #{flags.join(' ')} -o #{output_name}"
  puts compile_cmd
  system(compile_cmd)
end

desc "Compile and run"
task :run do
  Rake::Task["compile"].invoke
  system("./main")
end