require_relative "test_helper"

class LDATest < Minitest::Test
  def test_works
    model = Tomoto::LDA.new
    assert_elements_in_delta [0.1], model.alpha
    assert_in_delta 0.01, model.eta
    assert_equal 0, model.global_step
    assert_equal 10, model.optim_interval
    assert_in_delta 1, model.perplexity
    assert_equal :one, model.tw

    model.add_doc(["new", "document"])
    model.burn_in = 100
    assert_equal 100, model.burn_in
    assert model.summary
    model.train(0)
    assert_equal 2, model.num_words
    assert_equal 2, model.num_vocabs
    assert_equal ["new", "document"], model.vocabs

    expected = {
      "new" => 0.5,
      "document" => 0.5
    }
    assert_equal expected, model.topic_words(0)

    model.save(tempfile)
    model = Tomoto::LDA.load(tempfile)
    assert_equal 2, model.num_vocabs
    assert model.summary
  end

  def test_topics
    model = Tomoto::LDA.new(k: 2, seed: 42)
    model.add_doc(["this", "is", "a", "test"])
    model.add_doc(["another", "document"])
    model.add_doc(["a", "new", "document"])
    model.train(100)

    topics = model.docs[0].topics
    assert_in_delta 0.4222874939441681, topics[0]
    assert_in_delta 0.5777125954627991, topics[1]
  end

  def test_tw_invalid
    error = assert_raises(ArgumentError) do
      Tomoto::LDA.new(tw: :bad)
    end
    assert_equal "Invalid tw: bad", error.message
  end

  def test_add_doc_after_train
    model = Tomoto::LDA.new
    model.train
    error = assert_raises(RuntimeError) do
      model.add_doc(["new", "document"])
    end
    assert_equal "cannot add_doc() after train()", error.message
  end

  def test_load_missing
    error = assert_raises(RuntimeError) do
      Tomoto::LDA.load("missing.bin")
    end
    assert_equal "cannot open file 'missing.bin'", error.message
  end

  def test_load_another_type
    skip

    model = Tomoto::HDP.new
    model.save(tempfile)

    error = assert_raises(RuntimeError) do
      Tomoto::LDA.load(tempfile)
    end
    assert_match "matrix cols != 1", error.message
  end
end
