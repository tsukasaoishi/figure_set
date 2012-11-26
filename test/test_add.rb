require File.expand_path(File.join(File.dirname(__FILE__), "test_figure_set_base"))

class TestFigureSetAdd < Test::Unit::TestCase
  include TestFigureSetBase

  def test_add_invalid_value
    INVALID_VALUES.each do |n|
      fs = FigureSet.new
      fs << n
      assert_equal fs.size, 0
      assert_equal fs.to_a, []
    end

    fs_all = FigureSet.new
    INVALID_VALUES.each {|n| fs_all << n}
    assert_equal fs_all.size, 0
    assert_equal fs_all.to_a, []
  end

  def test_add_to_first_leaf
    FIRST_LEAF_VALUES.each do |n|
      fs = FigureSet.new
      fs << n
      assert_equal fs.to_a, [n] 
    end
    check_all_num(FIRST_LEAF_VALUES)
  end

  def test_add_to_node_border
    node_border_values.each do |n|
      fs = FigureSet.new
      fs << n
      assert_equal fs.to_a, [n]
    end
    check_all_num(node_border_values)
  end

  def test_add_to_increase
    ary = []
    fs = FigureSet.new
    node_border_values.each do |n|
      fs << n
      ary << n
      assert_equal fs.size, ary.size
      assert_equal fs.to_a, ary
    end
  end
end
