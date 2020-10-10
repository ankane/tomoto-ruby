require_relative "test_helper"

class PATest < Minitest::Test
  def test_works
    model = Tomoto::PA.new
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha
  end
end
