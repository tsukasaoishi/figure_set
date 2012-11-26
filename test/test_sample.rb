require File.expand_path(File.join(File.dirname(__FILE__), "test_figure_set_base"))

class TestFigureSetSample < Test::Unit::TestCase
  include TestFigureSetBase

  def test_sample_empty_set
    fs = FigureSet.new
    assert_equal fs.sample, []
  end

  def test_sample_invalid_value
    fs = FigureSet.new(FIRST_LEAF_VALUES)
    [0, -1, FIRST_LEAF_VALUES.size + 1].each do |n|
      s = fs.sample(n).uniq
      assert_equal s.size, 1
      assert FIRST_LEAF_VALUES.include?(s.first)
    end
  end

  def test_sample_from_leaf_node_all
    fs = FigureSet.new(FIRST_LEAF_VALUES)
    10.times do |n|
      s = fs.sample(n+1)
      assert_equal s.size, n+1
      s.each do |i|
        assert FIRST_LEAF_VALUES.include?(i)
      end
    end
  end

  def test_sample_node_border
    base_set = node_border_values.sort_by{rand}[0..99]
    fs = FigureSet.new(base_set)
    10.times do |n|
      s = fs.sample(n+1).uniq
      assert_equal s.size, n+1
      s.each do |i|
        assert base_set.include?(i)
      end
    end
  end
end
