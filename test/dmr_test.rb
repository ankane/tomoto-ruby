require_relative "test_helper"

class DMRTest < Minitest::Test
  def test_works
    model = Tomoto::DMR.new
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha
    assert_in_delta 0.01, model.eta
    assert_in_delta 1, model.sigma
    assert_in_delta 1e-10, model.alpha_epsilon
    assert_equal 0, model.f

    # model.add_doc(["new", "document"], metadata: "hello")
  end
end
