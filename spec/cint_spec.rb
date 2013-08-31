require 'spec_helper'

describe Carray do
  it 'should do to_i' do
    '1'.c_to_i.should eq(1)
    '-1'.c_to_i.should eq(-1)
    '123'.c_to_i.should eq(123)
    '-123'.c_to_i.should eq(-123)
    expect{''.c_to_i}.to raise_error(RangeError)
    expect{'abc'.c_to_i}.to raise_error(ArgumentError)
  end
end
