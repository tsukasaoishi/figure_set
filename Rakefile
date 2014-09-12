require "bundler/gem_tasks"
require "rake/extensiontask"
require 'rake/testtask'

# compile
gemspec = eval(File.read(File.expand_path('../figure_set.gemspec', __FILE__)))
Rake::ExtensionTask.new("figure_set", gemspec) do |ext|
  ext.lib_dir = "lib/figure_set"
end

# test
Rake::TestTask.new do |t|
  t.test_files = FileList['test/**/test_*.rb']
end
