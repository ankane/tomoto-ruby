require_relative "test_helper"

class HLDATest < Minitest::Test
  def test_works
    model = Tomoto::HLDA.new
    assert_kind_of Tomoto::LDA, model
    assert_equal 2, model.depth
    assert_in_delta 0.1, model.gamma
    assert_equal 0, model.live_k
  end
end
