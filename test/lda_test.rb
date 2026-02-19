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
    assert_in_delta 0.41782236099243164, topics[0]
    assert_in_delta 0.5821776986122131, topics[1]
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

  def test_infer
    model = Tomoto::LDA.new(k: 2, seed: 42)
    model.add_doc(["this", "is", "a", "test"])
    model.add_doc(["another", "document"])
    model.add_doc(["a", "new", "document"])
    model.train(100)

    doc = model.make_doc(["unseen", "document"])
    topic_dist, ll = model.infer(doc)
    assert_elements_in_delta [0.47528052, 0.52471954], topic_dist
    assert_in_delta(-1.5038636922836304, ll)
  end

  def test_infer_after_load_of_trained_model
    steps = 100
    model = Tomoto::LDA.new(k: 2, seed: 42)
    model.add_doc(["this", "is", "a", "test"])
    model.add_doc(["another", "document"])
    model.add_doc(["a", "new", "document"])
    model.train(steps)

    model.save(tempfile)
    model = Tomoto::LDA.load(tempfile)

    assert_equal steps, model.global_step

    doc = model.make_doc(["unseen", "document"])
    topic_dist, ll = model.infer(doc)
    assert_elements_in_delta [0.47528052, 0.52471954], topic_dist
    assert_in_delta(-1.5038636922836304, ll)
  end

  def test_infer_after_load_of_untrained_model
    model = Tomoto::LDA.new(k: 2, seed: 42)
    model.add_doc(["this", "is", "a", "test"])
    model.add_doc(["another", "document"])
    model.add_doc(["a", "new", "document"])

    model.save(tempfile)
    model = Tomoto::LDA.load(tempfile)

    doc = model.make_doc(["unseen", "document"])
    error = assert_raises(RuntimeError) do
      model.infer(doc)
    end
    assert_equal "cannot infer with untrained model", error.message
  end

  def test_load_missing
    error = assert_raises(RuntimeError) do
      Tomoto::LDA.load("missing.bin")
    end
    assert_equal "cannot open file 'missing.bin'", error.message
  end

  def test_load_another_type
    model = Tomoto::HDP.new
    model.save(tempfile)

    error = assert_raises(SystemCallError) do
      Tomoto::LDA.load(tempfile)
    end
    assert_match "matrix cols != 1", error.message
  end
end
