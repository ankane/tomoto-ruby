require_relative "test_helper"

class HDPTest < Minitest::Test
  def test_works
    model = Tomoto::HDP.new
    assert_kind_of Tomoto::LDA, model
    assert_in_delta 0.1, model.alpha
    assert_in_delta 0.01, model.eta
    assert_in_delta 0.1, model.gamma
    assert_equal 0, model.live_k
    assert_equal 0, model.num_tables
  end

  def test_save_load
    model = Tomoto::HDP.new
    model.add_doc(["new", "document"])
    model.train(0)

    model.save(tempfile)
    model = Tomoto::HDP.load(tempfile)
    assert_equal 2, model.num_vocabs
  end
end
