require File.expand_path(File.join(File.dirname(__FILE__), "test_figure_set_base"))

class TestFigureSetDelete < Test::Unit::TestCase
  include TestFigureSetBase

  def test_del_from_empty
    fs = FigureSet.new
    node_border_values.each do |n|
      fs.delete(n)
      assert_equal fs.size, 0
      assert_equal fs.to_a, []
    end
  end

  def test_del_invalid_value
    fs = FigureSet.new(node_border_values)

    INVALID_VALUES.each do |n|
      fs.delete(n)
      assert_equal fs.size, node_border_values.size
      assert_equal fs.to_a, node_border_values
    end
  end

  def test_del_not_include_value
    fs = FigureSet.new(FIRST_LEAF_VALUES)

    node_border_values.each do |n|
      fs.delete(n)
      assert_equal fs.size, FIRST_LEAF_VALUES.size
      assert_equal fs.to_a, FIRST_LEAF_VALUES
    end
  end

  def test_del_from_first_leaf
    fs = FigureSet.new(FIRST_LEAF_VALUES)
    ary = FIRST_LEAF_VALUES.dup

    FIRST_LEAF_VALUES.each do |n|
      fs.delete(n)
      ary.delete(n)
      assert_equal fs.size, ary.size
      assert_equal fs.to_a, ary
    end
  end

  def test_del_from_node_border
    fs = FigureSet.new(node_border_values)
    ary = node_border_values.dup

    node_border_values.each do |n|
      fs.delete(n)
      ary.delete(n)
      assert_equal fs.size, ary.size
      assert_equal fs.to_a, ary
    end
  end
end
