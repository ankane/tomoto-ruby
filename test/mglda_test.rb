require_relative "test_helper"

class MGLDATest < Minitest::Test
  def test_works
    model = Tomoto::MGLDA.new
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha_g
    assert_in_delta 0.1, model.alpha_l
    assert_in_delta 0.1, model.alpha_mg
    assert_in_delta 0.1, model.alpha_ml
    assert_in_delta 0.01, model.eta_g
    assert_in_delta 0.01, model.eta_l
    assert_in_delta 0.1, model.gamma
    assert_equal 1, model.k_g
    assert_equal 1, model.k_l
    assert_equal 3, model.t

    model.add_doc(["new", "document"], delimiter: ".")
    assert model.summary
  end
end
