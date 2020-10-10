require_relative "test_helper"

class DTTest < Minitest::Test
  def test_works
    model = Tomoto::DT.new
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha
    assert_in_delta 0.1, model.eta
    assert_in_delta 0.01, model.lr_a
    assert_in_delta 0.1, model.lr_b
    assert_in_delta 0.55, model.lr_c
    assert_equal 1, model.num_timepoints
    assert_equal [], model.num_docs_by_timepoint

    model.add_doc(["new", "document"], timepoint: 0)
  end
end
