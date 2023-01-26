require_relative "test_helper"

class LLDATest < Minitest::Test
  def test_works
    model = Tomoto::LLDA.new
    assert_kind_of Tomoto::LDA, model
    assert_elements_in_delta [0.1], model.alpha

    model.add_doc(["new", "document"], labels: ["spam"])
    model.add_doc(["cuban", "sandwiches"], labels: ["ham"])
    assert model.summary

    assert_equal ["spam", "ham"], model.topic_label_dict
  end
end
