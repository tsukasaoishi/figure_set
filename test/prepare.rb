require 'rubygems'
require 'figure_set'
require 'test/unit'

module TestFigureSetBase
  INVALID_VALUES = [-1, 2 ** 32]
  FIRST_LEAF_VALUES = (0..63).to_a

  private

  def node_border_values
    return @_node_border_values if defined?(@_node_border_values)

    all_num = []
    0.step((2 ** 32) - 1, (64 * (16 ** 5))) do |i|
      offset = i / 64
      (1..15).each do |n|
        leaf_wide = [(offset + n * 64), ((offset + (n + 1) * 64) - 1)]
        all_num += leaf_wide
      end
    end
    @_node_border_values = all_num
  end

  def check_all_num(ary)
    fs = FigureSet.new
    ary.each {|n| fs << n}
    assert_equal fs.size, ary.size
    assert_equal fs.to_a, ary
  end
end
