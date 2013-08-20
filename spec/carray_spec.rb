require 'spec_helper'

describe Carray do
  it 'should do dot_products' do
    [1, 2, 3].c_dot_product([4, 5, 6]).should eq(32)
  end
  it 'should do euclidean_distance' do
    [1, 2].c_euclidean_distance([3, 4]).should eq(2 * Math.sqrt(2))
  end
  it 'should do c_int_include' do
    [1, 2, 3].c_int_include(1).should be true
    [1, 2, 3].c_int_include(0).should be false
  end
  it 'should do c_int_uniq' do
    [].c_int_uniq.should eq([])
    [1, 2, 3, 2, 1].c_int_uniq.sort.should eq([1, 2, 3])
  end
  it 'should do c_magnitude' do
    [1, 2, 3].c_magnitude.should eq(Math.sqrt(14))
  end
  it 'should do c_mean' do
    [1, 2, 3].c_mean.should eq(2)
  end
  it 'should do c_pearson_correlation' do
    [1, 2, 3].c_pearson_correlation([4, 5, 6]).should eq(1)
  end
  it 'should do c_variance' do
    [1, 2, 3].c_variance.should eq(2.0 / 3.0)
  end
end
