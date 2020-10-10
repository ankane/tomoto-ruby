require_relative "test_helper"

class HLDATest < Minitest::Test
  def test_works
    model = Tomoto::HLDA.new
    assert_kind_of Tomoto::LDA, model
    model.train(0)

    assert_equal [], model.children_topics(0)
    assert_equal 2, model.depth
    assert_equal(-1, model.level(0))
    refute model.live_topic?(0)
    assert_in_delta 0.1, model.gamma
    assert_equal 0, model.live_k
    assert_equal 0, model.num_docs_of_topic(0)
    assert_equal(-1, model.parent_topic(0))
    assert model.summary
  end
end
