require File.expand_path(File.join(File.dirname(__FILE__), "prepare"))

class TestFigureSetAnd < Test::Unit::TestCase
  include TestFigureSetBase

  def test_and_empty_and_empty
    fs0 = FigureSet.new
    fs1 = FigureSet.new
    fs_and = fs0 & fs1
    assert_equal fs_and.size, 0
    assert_equal fs_and.to_a, []
  end

  def test_and_empty_and_present
    fs0 = FigureSet.new
    fs1 = FigureSet.new(FIRST_LEAF_VALUES)
    fs_and = fs0 & fs1
    assert_equal fs_and.size, 0
    assert_equal fs_and.to_a, []
  end

  def test_and_present_and_empty
    fs0 = FigureSet.new(FIRST_LEAF_VALUES)
    fs1 = FigureSet.new
    fs_and = fs0 & fs1
    assert_equal fs_and.size, 0
    assert_equal fs_and.to_a, []
  end

  def test_and_not_match_present_and_present
    fs0 = FigureSet.new(FIRST_LEAF_VALUES)
    fs1 = FigureSet.new(node_border_values)
    fs_and = fs0 & fs1
    assert_equal fs_and.size, 0
    assert_equal fs_and.to_a, []
  end

  def test_and_same_set
    fs0 = FigureSet.new(node_border_values)
    fs1 = FigureSet.new(node_border_values)
    fs_and = fs0 & fs1
    assert_equal fs_and.size, node_border_values.size
    assert_equal fs_and.to_a, node_border_values
  end

  def test_and_leaf_node_0_1
    result_ary = FIRST_LEAF_VALUES[0..31]
    fs0 = FigureSet.new(FIRST_LEAF_VALUES)
    fs1 = FigureSet.new(result_ary + node_border_values)
    fs_and = fs0 & fs1
    assert_equal fs_and.size, result_ary.size
    assert_equal fs_and.to_a, result_ary
  end
end
