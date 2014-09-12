require File.expand_path(File.join(File.dirname(__FILE__), "prepare"))

class TestFigureSetEmpty < Test::Unit::TestCase
  include TestFigureSetBase

  def test_empty_of_empty
    fs = FigureSet.new
    assert fs.empty?
  end

  def test_empty_of_present
    assert !FigureSet.new(FIRST_LEAF_VALUES).empty?
    assert !FigureSet.new(node_border_values).empty?
    assert !FigureSet.new([0]).empty?
  end
end
