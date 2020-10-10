require_relative "test_helper"

class SLDATest < Minitest::Test
  def test_works
    model = Tomoto::SLDA.new(vars: "l")
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha

    model.add_doc(["new", "document"], y: [1.0])
  end
end
