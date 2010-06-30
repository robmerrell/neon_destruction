require "rubygems"
require "rmagick"


sizes = [48, 64, 96, 128, 192, 256, 384, 512]
draw_width = [64, 64, 128, 128, 256, 256, 512, 512]

# sizes.each do |size|
#   ind = sizes.index(size)
#   left_image = Magick::Image.read("left.png").first
#   middle_image = Magick::Image.read("body.png").first.scale(size-22, 25)
#   right_image = Magick::Image.read("right.png").first
#   
#   img = Magick::Image.new(draw_width[ind], 32) { self.background_color = "transparent" }
#   
#   # add the glows
#   img.composite!(left_image, 0, 5, Magick::OverCompositeOp)
#   img.composite!(middle_image, 11, 5, Magick::OverCompositeOp)
#   img.composite!(right_image, size-11, 5, Magick::OverCompositeOp)
#   
#   
#   # white line
#   line = Magick::Image.new(size-24, 6) { self.background_color = "white" }
#   gc = Magick::Draw.new
#   gc.stroke("white")
#   
#   gc.draw(line)
#   img.composite!(line, 12, 14, Magick::OverCompositeOp)
#   
#   img.write("gen/#{size}.png")
# end


sizes.each do |size|
  ind = sizes.index(size)
  img = Magick::Image.read("gen/#{size}.png").first
  
  if ind > 0
    height = sizes[ind] - sizes[ind-1]+1
    sheet = Magick::Image.new(600, height * 32) { self.background_color = "black" }
    
    cn = 0
    for i in sizes[ind-1]+1..sizes[ind]
      comp = img.resize(i, 32)
      sheet.composite!(comp, 10, cn * 32, Magick::OverCompositeOp)
      cn += 1
    end
    
    sheet.write("test/#{size}.png")
  end
end
