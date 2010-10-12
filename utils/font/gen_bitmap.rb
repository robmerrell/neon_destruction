require "rubygems"
require "hpricot"

file = File.open("large.xml", "rb")
contents = file.read

sizes = []

doc= Hpricot::XML(contents)
(doc/:rectangle).each do |rectangle|
  sizes << "  cpv(#{rectangle['x']},#{rectangle['y']})"
end

puts sizes.join(",\n")
