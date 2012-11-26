require File.expand_path(File.join(File.dirname(__FILE__), "test_figure_set_base"))

class TestFigureSetOr < Test::Unit::TestCase
  include TestFigureSetBase

  def test_or_empty_and_empty
    fs0 = FigureSet.new
    fs1 = FigureSet.new
    fs_and = fs0 | fs1
    assert_equal fs_and.size, 0
    assert_equal fs_and.to_a, []
  end

  def test_or_empty_and_present
    fs0 = FigureSet.new
    fs1 = FigureSet.new(FIRST_LEAF_VALUES)
    fs_and = fs0 | fs1
    assert_equal fs_and.size, FIRST_LEAF_VALUES.size
    assert_equal fs_and.to_a, FIRST_LEAF_VALUES
  end

  def test_or_present_and_empty
    fs0 = FigureSet.new(FIRST_LEAF_VALUES)
    fs1 = FigureSet.new
    fs_and = fs0 | fs1
    assert_equal fs_and.size, FIRST_LEAF_VALUES.size
    assert_equal fs_and.to_a, FIRST_LEAF_VALUES
  end

  def test_or_not_match_present_and_present
    fs0 = FigureSet.new(FIRST_LEAF_VALUES)
    fs1 = FigureSet.new(node_border_values)
    fs_and = fs0 | fs1
    result_ary = FIRST_LEAF_VALUES + node_border_values
    assert_equal fs_and.size, result_ary.size
    assert_equal fs_and.to_a, result_ary
  end

  def test_or_same_set
    fs0 = FigureSet.new(node_border_values)
    fs1 = FigureSet.new(node_border_values)
    fs_and = fs0 | fs1
    assert_equal fs_and.size, node_border_values.size
    assert_equal fs_and.to_a, node_border_values
  end

  def test_or_leaf_node_0_1
    result_ary = FIRST_LEAF_VALUES + node_border_values
    fs0 = FigureSet.new(FIRST_LEAF_VALUES[0..31])
    fs1 = FigureSet.new(result_ary)
    fs_and = fs0 | fs1
    assert_equal fs_and.size, result_ary.size
    assert_equal fs_and.to_a, result_ary
  end
end
