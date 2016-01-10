require 'rubygems'
require 'figure_set'
require 'benchmark/ips'

fs = FigureSet.new((0..100000).to_a)

Benchmark.ips do |x|
  x.report("smaple") { fs.sample }
  x.report("array sample") { fs.to_a.sample }

  x.compare!
end
