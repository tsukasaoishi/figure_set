require File.expand_path(File.join(File.dirname(__FILE__), "prepare"))

class TestFigureSetCopy < Test::Unit::TestCase
  include TestFigureSetBase

  def test_copy_from_empty
    all_equal_check(FigureSet.new)
  end

  def test_copy_from_first_leaf
    all_equal_check(FigureSet.new(FIRST_LEAF_VALUES))
  end

  def test_copy_from_node_border
    all_equal_check(FigureSet.new(node_border_values))
  end

  def test_copy_not_share
    orig = FigureSet.new([1,2,3])
    dup_copy = orig.dup
    clone_copy = orig.clone

    dup_copy.delete(2)
    clone_copy << 4

    all_not_equal_check(orig, dup_copy, clone_copy)
  end

  private

  def all_equal_check(orig)
    dup_copy = orig.dup
    clone_copy = orig.clone
    assert_equal orig.size, dup_copy.size
    assert_equal orig.size, clone_copy.size
    assert_equal orig.to_a, dup_copy.to_a
    assert_equal orig.to_a, clone_copy.to_a
  end

  def all_not_equal_check(orig, dup_copy, clone_copy)
    assert_not_equal orig.size, dup_copy.size
    assert_not_equal orig.size, clone_copy.size
    assert_not_equal orig.to_a, dup_copy.to_a
    assert_not_equal orig.to_a, clone_copy.to_a
  end
end
