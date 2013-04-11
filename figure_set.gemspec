# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{figure_set}
  s.version = "0.0.2"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Tsukasa OISHI"]
  s.date = %q{2012-11-26}
  s.description = %q{FigureSet.}
  s.email = ["tsukasa.oishi@gmail.com"]
  s.extensions = ["ext/extconf.rb"]
  s.extra_rdoc_files = ["History.txt", "Manifest.txt", "README.rdoc"]
  s.files = %w|
    History.txt
    Manifest.txt
    README.rdoc
    Rakefile
    lib/figure_set.rb
    ext/extconf.rb
    ext/figure_set.h
    ext/methods.c
    ext/init.c
    ext/index.c
    ext/and.c
    ext/or.c
    ext/array.c
    ext/sample.c
  |
  s.has_rdoc = false
  s.homepage = %q{http://www.kaeruspoon.net/}
  s.rdoc_options = ["--main", "README.rdoc"]
  s.require_paths = ["lib", "ext"]
  s.rubyforge_project = %q{figure_set}
  s.rubygems_version = %q{1.3.1}
  s.summary = %q{FigureSet.}

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 2

    if Gem::Version.new(Gem::RubyGemsVersion) >= Gem::Version.new('1.2.0') then
      s.add_development_dependency(%q<newgem>, [">= 1.2.3"])
      s.add_development_dependency(%q<hoe>, [">= 1.8.0"])
    else
      s.add_dependency(%q<newgem>, [">= 1.2.3"])
      s.add_dependency(%q<hoe>, [">= 1.8.0"])
    end
  else
    s.add_dependency(%q<newgem>, [">= 1.2.3"])
    s.add_dependency(%q<hoe>, [">= 1.8.0"])
  end
end
