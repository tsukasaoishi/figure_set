require "bundler/gem_tasks"
require "rake/extensiontask"
require 'rake/testtask'

# compile
gemspec = eval(File.read(File.expand_path('../figure_set.gemspec', __FILE__)))
Rake::ExtensionTask.new("figure_set", gemspec) do |ext|
  ext.ext_dir = "ext/figure_set/figure_set"
  ext.lib_dir = "lib/figure_set"
end

# test
Rake::TestTask.new do |t|
  t.test_files = FileList['test/**/test_*.rb']
end

desc 'generate Manifest.txt'
task :manifest do |t|
  File.open(File.expand_path("../Manifest.txt", __FILE__), "w") do |out|
    gemspec.files.sort.each do |f|
      out.puts(f) if File.file?(f)
    end
  end
  puts "Generate Manifest.txt"
end
