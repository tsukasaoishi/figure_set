require File.expand_path(File.join(File.dirname(__FILE__), "test_figure_set_base"))

class TestFigureSetNew < Test::Unit::TestCase
  include TestFigureSetBase

  def test_new_invalid_value
    fs = FigureSet.new(INVALID_VALUES)
    assert_equal fs.size, 0
    assert_equal fs.to_a, []
  end

  def test_new_to_first_leaf
    check_all_num(FIRST_LEAF_VALUES)
  end

  def test_new_to_node_border
    check_all_num(node_border_values)
  end
end
