module Tomoto
  class LDA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, alpha: 0.1, eta: 0.01, seed: nil)
      model = _new(to_tw(tw), k, alpha, eta, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      model
    end

    def self.load(filename)
      model = new
      model._load(filename)
      model
    end

    def add_doc(doc)
      _add_doc(prepare_doc(doc))
    end

    def count_by_topics
      prepare
      _count_by_topics
    end

    def removed_top_words
      prepare
      _removed_top_words(@rm_top)
    end

    def save(filename, full: true)
      _save(filename, full)
    end

    def topic_words(topic_id = nil, top_n: 10)
      if topic_id
        _topic_words(topic_id, top_n)
      else
        k.times.map { |i| _topic_words(i, top_n) }
      end
    end

    def train(iterations = 10, workers: 0)
      prepare
      _train(iterations, workers)
    end

    private

    def prepare
      unless defined?(@prepared)
        _prepare(@min_cf, @min_df, @rm_top)
        @prepared = true
      end
    end

    def prepare_doc(doc)
      raise "cannot add_doc() after train()" if defined?(@prepared)
      doc = doc.split(/[[:space:]]+/) unless doc.is_a?(Array)
      doc
    end

    class << self
      private

      def to_tw(tw)
        TERM_WEIGHT.index(tw) || (raise ArgumentError, "Invalid tw: #{tw}")
      end
    end
  end
end
