require_relative "test_helper"

class CTTest < Minitest::Test
  def test_works
    model = Tomoto::CT.new
    assert_kind_of Tomoto::LDA, model
    assert_equal 10, model.num_beta_sample
    assert_equal 5, model.num_tmn_sample
    assert_equal [], model.prior_cov
    assert_equal [], model.prior_mean
  end
end
