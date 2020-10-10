require_relative "test_helper"

class SLDATest < Minitest::Test
  def test_works
    model = Tomoto::SLDA.new(vars: "l")
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha
    assert_equal 1, model.f

    model.add_doc(["new", "document"], y: [1.0])

    model.train(0)
    assert_equal "l", model.var_type(0)
    assert model.summary
  end
end
