require_relative "test_helper"

class SLDATest < Minitest::Test
  def test_works
    model = Tomoto::SLDA.new
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha
  end
end
