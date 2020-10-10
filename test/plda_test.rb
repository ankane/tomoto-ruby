require_relative "test_helper"

class PLDATest < Minitest::Test
  def test_works
    model = Tomoto::PLDA.new
    assert_kind_of Tomoto::LLDA, model
    assert_in_delta 0.1, model.alpha
    assert_equal 1, model.latent_topics
    assert_equal 1, model.topics_per_label

    model.add_doc(["new", "document"], labels: ["spam"])
  end
end
