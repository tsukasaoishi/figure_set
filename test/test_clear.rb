require File.expand_path(File.join(File.dirname(__FILE__), "test_figure_set_base"))

class TestFigureSetClear < Test::Unit::TestCase
  include TestFigureSetBase

  def test_clear_of_empty
    fs = FigureSet.new
    fs.clear
    check_empty(fs)
  end

  def test_empty_of_present
    fs1 = FigureSet.new(FIRST_LEAF_VALUES)
    fs2 = FigureSet.new(node_border_values)
    fs1.clear
    fs2.clear
    check_empty(fs1)
    check_empty(fs2)
  end

  private

  def check_empty(fs)
    assert_equal fs.size, 0
    assert_equal fs.to_a, []
  end
end
