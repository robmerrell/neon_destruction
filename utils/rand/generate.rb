alphanumerics = [('0'..'9'),('A'..'Z'),('a'..'z')].map {|range| range.to_a}.flatten
puts (0...10).map { alphanumerics[Kernel.rand(alphanumerics.size)] }.join
