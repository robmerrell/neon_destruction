require "rake"
require "fileutils"
 
$pdk_path = "/opt/PalmPDK"
 
task :arch_settings do
  if ENV["TARGET"] == "pre"
    $arch_settings = "-mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp"
    $cc = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-gcc"
    $gpp = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-g++"
    $ar = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ar"
    $ranlib = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ranlib"
  elsif ENV["TARGET"] == "pixi"
    $arch_settings = "-mcpu=arm1136jf-s -mfpu=vfp -mfloat-abi=softfp"
    $cc = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-gcc"
    $gpp = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-g++"
    $ar = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ar"
    $ranlib = "#{$pdk_path}/arm-gcc/bin/arm-none-linux-gnueabi-ranlib"
  else
    $arch_settings = "-arch i386"
    $cc = "gcc"
    $gpp = "g++"
    $ar = "ar"
    $ranlib = "ranlib"
  end
end
 
 
desc "Create a static library for the Chipmunk physics engine TARGET=pre, pixi or host(mac); host is assumed if TARGET is not set"
file :build_chipmunk => :arch_settings do
  flags = [
    "-Wno-write-strings",
    "-Isrc/chipmunk/headers",
    "-std=gnu99",
    "-O3",
    "-DNDEBUG",
    "-ffast-math"
  ]
  
  # compile all of the files
  files = Dir.glob("src/chipmunk/**/*.c")
  files.each do |file|
    # make sure the dir exists for the object file
    dir_name = file.gsub(File.basename(file), '')
    FileUtils.mkdir_p "build/#{dir_name}"
    
    cmd = "#{$cc} #{$arch_settings} #{flags.join(' ')} -c #{file} -o build/#{file}.o"
    puts cmd
    system cmd
  end
  
  # create libchipmunk.a out of the compiled files
  files = Dir.glob("build/src/chipmunk/**/*.o")
  cmd = "#{$ar} cr build/libchipmunk.a #{files.join(' ')}"
  puts cmd
  system cmd
  
  # do ranlib on the library
  cmd = "#{$ranlib} build/libchipmunk.a"
  puts cmd
  system cmd
end


desc "Create a static library for SOIL TARGET=pre, pixi or host(mac); host is assumed if TARGET is not set"
file :build_soil => :arch_settings do
  flags = [
    "-Wno-write-strings",
    "-O3"
  ]
  
  if ENV["TARGET"] == "pre" || ENV["TARGET"] == "pixi"
    flags << "-L#{$pdk_path}/device/lib -Wl,--allow-shlib-undefined"
    flags << "-I#{$pdk_path}/include"
    flags << "--sysroot=#{$pdk_path}/arm-gcc/sysroot"
  end
  
  # compile all of the files
  files = Dir.glob("src/soil/*.c")
  files.each do |file|
    # make sure the dir exists for the object file
    dir_name = file.gsub(File.basename(file), '')
    FileUtils.mkdir_p "build/#{dir_name}"
    
    cmd = "#{$cc} #{$arch_settings} #{flags.join(' ')} -c #{file} -o build/#{file}.o"
    puts cmd
    system cmd
  end
  
  # create libchipmunk.a out of the compiled files
  files = Dir.glob("build/src/soil/**/*.o")
  cmd = "#{$ar} cr build/libSOIL.a #{files.join(' ')}"
  puts cmd
  system cmd
  
  # do ranlib on the library
  cmd = "#{$ranlib} build/libSOIL.a"
  puts cmd
  system cmd
end


desc "Build the main project and chipmunk if needed TARGET=pre, pixi or host(mac); host is assumed if TARGET is not set"
task :build => :arch_settings do
  # build the chipmunk lib if we can't find build/libchipmunk.a
  if !FileTest.exists? "build/libchipmunk.a"
    Rake::Task[:build_chipmunk].invoke
  end
  
  # build the soil lib if we can't find build/libSOIL.a
  if !FileTest.exists? "build/libSOIL.a"
    Rake::Task[:build_soil].invoke
  end
  
  cflags = [
    "-Wno-write-strings",
    "-I#{$pdk_path}/include",
    "-I#{$pdk_path}/include/SDL"
  ]
  
  libs = [
    "-Lbuild",
    "-lchipmunk",
    "-lSOIL",
    "-lSDL",
    "-lGLES_CM",
    "-lpdl"
  ]
  
  if ENV["TARGET"] == "pre" || ENV["TARGET"] == "pixi"
    libs << "-L#{$pdk_path}/device/lib -Wl,--allow-shlib-undefined"
    cflags << "--sysroot=#{$pdk_path}/arm-gcc/sysroot"
    cflags << "-DDEVICE"
  else
    libs << "-L#{$pdk_path}/host/lib"
    libs << "-framework cocoa"
    libs << "-lSDLmain"
  end
  
  # compile all of the files
  if ENV["FILE"]
    files = []
    files << ENV["FILE"]
  else
    files = Dir.glob("src/**/*.cpp")
  end
  files.each do |file|
    # make sure the dir exists for the object file
    dir_name = file.gsub(File.basename(file), '')
    FileUtils.mkdir_p "build/#{dir_name}"
    
    cmd = "#{$gpp} #{$arch_settings} #{cflags.join(' ')} -c #{file} -o build/#{file}.o"
    puts cmd
    system cmd
    exit if $?.to_i > 0
  end
  
  # link all of the files
  files = Dir.glob("build/**/*.o").reject {|file| file.include?("chipmunk")}
  cmd = "#{$gpp} #{files.join(' ')} #{$arch_settings} #{cflags.join(' ')} #{libs.join(' ')} -o main"
  puts cmd
  system cmd
end


desc "Clean build files by removing the build directory"
task :clean do
  puts "removing build files..."
  FileUtils.rmtree "build"
  FileUtils.rm "main" if File.exists?("main")
  FileUtils.rm "com.trackera.neonblaster_1.0.0_all.ipk" if File.exists?("com.trackera.neonblaster_1.0.0_all.ipk")
end


desc "Copy the app to /media/internal on the device without creating a package and run the jerk"
task :run do
  Rake::Task[:cp].invoke

  run_cmd = "novacom run file:///media/internal/neon_blaster/main"
  system(run_cmd)
end


desc "Copy the app to /media/internal/neon_blaster"
task :cp do
  copy_bin = "scp -r -P 10022 main root@localhost:/media/internal/neon_blaster"
  puts copy_bin
  system(copy_bin)
  
  copy_assets = "scp -r -P 10022 assets root@localhost:/media/internal/neon_blaster"
  puts copy_assets
  system(copy_assets)
end


desc "Create and install a package to the device"
task :pkg do
  pdk_bin = "/opt/PalmSDK/Current/bin/"
  
  # copy the executable and asset file to the package dir
  system("cp main neon_blaster")
  system("cp -r assets/* neon_blaster/assets")
  system("cp -r levels/* neon_blaster/levels")

  puts "packaging..."
  cmd = "#{pdk_bin}/palm-package neon_blaster"
  puts cmd
  system(cmd)
  
  puts "installing..."
  cmd = "#{pdk_bin}/palm-install com.trackera.neonblaster_1.0.0_all.ipk"
  puts cmd
  system(cmd)
end


desc "Generate platform images for both dynamic and static"
task :gen_images do
  require "rmagick"
  
  sizes = [48, 64, 96, 128, 192, 256, 384, 512]
  draw_width = [64, 64, 128, 128, 256, 256, 512, 512]
  
  sizes.each do |size|
    ind = sizes.index(size)
    left_image = Magick::Image.read("utils/img/blue/left.png").first
    middle_image = Magick::Image.read("utils/img/blue/body.png").first.scale(size-22, 25)
    right_image = Magick::Image.read("utils/img/blue/right.png").first

    img = Magick::Image.new(draw_width[ind], 32) { self.background_color = "transparent" }

    # add the glows
    img.composite!(left_image, 0, 5, Magick::OverCompositeOp)
    img.composite!(middle_image, 11, 5, Magick::OverCompositeOp)
    img.composite!(right_image, size-11, 5, Magick::OverCompositeOp)


    # white line
    line = Magick::Image.new(size-24, 6) { self.background_color = "white" }
    gc = Magick::Draw.new
    gc.stroke("white")

    gc.draw(line)
    img.composite!(line, 12, 14, Magick::OverCompositeOp)

    img.write("utils/img/gen/#{size}.png")
  end
end


desc "generate test sheets for the platform images"
task :gen_img_testsheet do
  require "rmagick"
  
  sizes = [48, 64, 96, 128, 192, 256, 384, 512]
  draw_width = [64, 64, 128, 128, 256, 256, 512, 512]
  
  sizes.each do |size|
    ind = sizes.index(size)
    img = Magick::Image.read("utils/img/gen/#{size}.png").first

    if ind > 0
      height = sizes[ind] - sizes[ind-1]+1
      sheet = Magick::Image.new(600, height * 32) { self.background_color = "black" }

      cn = 0
      for i in sizes[ind-1]+1..sizes[ind]
        comp = img.resize(i, 32)
        sheet.composite!(comp, 10, cn * 32, Magick::OverCompositeOp)
        cn += 1
      end

      sheet.write("utils/img/test/#{size}.png")
    end
  end
  
end

