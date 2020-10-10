require_relative "test_helper"

class CTTest < Minitest::Test
  def test_works
    model = Tomoto::CT.new(k: 2)
    assert_kind_of Tomoto::LDA, model
    assert_equal [[1.0, 0.0], [0.0, 1.0]], model.correlations
    assert_equal [1.0, 0.0], model.correlations(0)
    assert_equal 10, model.num_beta_sample
    assert_equal 5, model.num_tmn_sample
    assert_equal [[1.0, 0.0], [0.0, 1.0]], model.prior_cov
    assert_equal [0.0, 0.0], model.prior_mean
    assert model.summary
  end
end
