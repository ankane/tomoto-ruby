require_relative "test_helper"

class DMRTest < Minitest::Test
  def test_works
    model = Tomoto::DMR.new(k: 2)
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha
    assert_in_delta 1e-10, model.alpha_epsilon
    assert_in_delta 0.01, model.eta
    assert_equal 0, model.f
    assert_equal [], model.lambdas
    assert_equal [], model.metadata_dict
    assert_in_delta 1, model.sigma

    model.add_doc(["new", "document"], metadata: "hello")

    model.train(0)
    assert_equal [1, 1], model.lambdas.map(&:size)
    assert_in_delta(-2.3025851, model.lambdas[0][0])
    assert_in_delta(-2.3025851, model.lambdas[1][0])
    assert_equal ["hello"], model.metadata_dict
  end
end
