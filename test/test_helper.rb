require "bundler/setup"
Bundler.require(:default)
require "minitest/autorun"
require "minitest/pride"
require "tmpdir"

class Minitest::Test
  def assert_elements_in_delta(expected, actual)
    assert_equal expected.size, actual.size
    expected.zip(actual) do |exp, act|
      assert_in_delta exp, act
    end
  end

  def teardown
    @tempfile = nil
  end

  def tempfile
    @tempfile ||= "#{Dir.mktmpdir}/#{Time.now.to_f}"
  end
end
