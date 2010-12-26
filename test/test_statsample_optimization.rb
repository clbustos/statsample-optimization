$:.unshift(File.dirname(__FILE__)+"/lib")
require "test/unit"
#require "statsample"
require "statsamplert"
require "statsample"
class TestRubyStatsampleOpt < Test::Unit::TestCase
  def test_base
    assert(Statsample::OPTIMIZED,"should be true")
  end
  def test_frequencies
    assert(Statsample::STATSAMPLE__.respond_to?(:frequencies))
    v=[1,1,2].to_vector
    exp={1=>2,2=>1}
    assert_equal(exp,Statsample::STATSAMPLE__.frequencies(v.data))
    assert_equal(v._frequencies, v.frequencies)
  end
  def test_set_valid_data
    assert(Statsample::STATSAMPLE__.respond_to?(:set_valid_data_intern))
    v=[2,3,4].to_vector
    v.add(5)
    assert_equal([2,3,4,5], v.valid_data)
    v.add(nil,false)
    assert_equal([2,3,4,5], v.valid_data)
    assert_equal([2,3,4,5,nil], v.data)
  end
  def test_case_as_array
    assert(Statsample::STATSAMPLE__.respond_to?(:case_as_array))
    a=[1,2,3].to_vector(:scale)
    b=[4,5,6].to_vector(:scale)
    ds={"a"=>a,"b"=>b}.to_dataset
    assert_equal([1,4],Statsample::STATSAMPLE__.case_as_array(ds,0))
    assert_equal([2,5],Statsample::STATSAMPLE__.case_as_array(ds,1))
    assert_equal([3,6],Statsample::STATSAMPLE__.case_as_array(ds,2))
  end
  def test_case_as_hash
    assert(Statsample::STATSAMPLE__.respond_to?(:case_as_hash))
    a=[1,2,3].to_vector(:scale)
    b=[4,5,6].to_vector(:scale)
    ds={"a"=>a,"b"=>b}.to_dataset
    assert_equal({"a"=>1,"b"=>4},Statsample::STATSAMPLE__.case_as_hash(ds,0))
  end
  def test_tetrachoric
    assert(Statsample::STATSAMPLE__.respond_to?(:tetrachoric))
    a,b,c,d = 30,40,70,20
    result=Statsample::STATSAMPLE__.tetrachoric(a,b,c,d)
    assert_in_delta(-0.53980, result[:r], 0.0001)
    assert_in_delta(0.09940, result[:sdr], 0.0001)
    assert_in_delta(-0.15731, result[:threshold_x], 0.0001)
    assert_in_delta(0.31864, result[:threshold_y], 0.0001)
    
  end

end
