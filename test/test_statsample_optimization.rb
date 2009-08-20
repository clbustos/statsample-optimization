$:.unshift(File.dirname(__FILE__)+"/ext")
require "test/unit"
require "statsample"
require "statsamplert"

class TestRubyStatsampleOpt < Test::Unit::TestCase
    def test_base
        assert(Statsample::OPTIMIZED,true)
    end
    def test_frequencies
        assert(Statsample.respond_to?(:_frequencies))
        v=[1,1,2].to_vector
        exp={1=>2,2=>1}
        assert_equal(exp,Statsample._frequencies(v.data))
    end
end
