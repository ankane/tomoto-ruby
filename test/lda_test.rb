require_relative "test_helper"

class LDATest < Minitest::Test
  def test_works
    model = Tomoto::LDA.new
    assert_in_delta 0.1, model.alpha
    assert_in_delta 0.01, model.eta

    model.add_doc(["new", "document"])
    model.burn_in = 100
    assert_equal 100, model.burn_in
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
    model = Tomoto::HDP.new
    model.save(tempfile)

    error = assert_raises(RuntimeError) do
      Tomoto::LDA.load(tempfile)
    end
    assert_equal "matrix cols != 1': unspecified iostream_category error", error.message
  end
end
