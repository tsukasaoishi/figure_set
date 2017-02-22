# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'figure_set/version'

Gem::Specification.new do |spec|
  spec.name          = "figure_set"
  spec.version       = FigureSet::VERSION
  spec.authors       = ["Tsukasa OISHI"]
  spec.email         = ["tsukasa.oishi@gmail.com"]

  spec.summary       = %q{FigureSet is the library which treats set operation.}
  spec.description   = %q{FigureSet is the library which treats set operation.}
  spec.homepage      = "https://github.com/tsukasaoishi/figure_set"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib", "ext"]
  spec.extensions    = ["ext/figure_set/extconf.rb"]

  spec.required_ruby_version = '>= 2.1'

  spec.add_development_dependency "bundler", ">= 1.3.0", "< 2.0"
  spec.add_development_dependency "rake", ">= 0.8.7"
  spec.add_development_dependency "rake-compiler", '~> 0.9'
  spec.add_development_dependency "test-unit"
  spec.add_development_dependency "benchmark-ips"
end
