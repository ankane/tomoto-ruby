require_relative "test_helper"

class TomotoTest < Minitest::Test
  def test_isa
    assert_includes ["avx2", "avx", "sse2", "none"], Tomoto.isa
  end
end
