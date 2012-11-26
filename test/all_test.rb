DIR_NAME = File.dirname(__FILE__)
IGNORE_FILE = [".", "..", "all_test.rb", "test_figure_set_base.rb"]
files = Dir::entries(DIR_NAME) - IGNORE_FILE
files.each do |f| 
  puts `ruby #{File.join(DIR_NAME, f)}`
  puts
end
