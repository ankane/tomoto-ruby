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

    # returns string instead of printing
    def summary(initial_hp: true, params: true, topic_word_top_n: 5)
      summary = []

      sum = used_vocab_freq.sum.to_f
      mapped = used_vocab_freq.map { |v| v / sum }
      entropy = mapped.map { |v| v * Math.log(v) }.sum

      summary << "<Basic Info>"
      summary << "| #{self.class.name.sub("Tomoto::", "")} (current version: #{VERSION})"
      summary << "| #{num_docs} docs, #{num_words} words"
      summary << "| Total Vocabs: #{vocabs.size}, Used Vocabs: #{used_vocabs.size}"
      summary << "| Entropy of words: %.5f" % entropy
      summary << "| Removed Vocabs: #{removed_top_words.join(" ")}"
      summary << "|"

      summary << "<Training Info>"
      summary << "| Iterations: #{global_step}, Burn-in steps: #{burn_in}"
      summary << "| Optimization Interval: #{optim_interval}"
      summary << "| Log-likelihood per word: %.5f" % ll_per_word
      summary << "|"

      # if initial_hp
      #   summary << "<Initial Parameters>"
      #   summary << "| todo"
      #   summary << "|"
      # end

      # if params
      #   summary << "<Parameters>"
      #   summary << "| todo"
      #   summary << "|"
      # end

      if topic_word_top_n > 0
        summary << "<Topics>"
        counts = count_by_topics
        topic_words(top_n: topic_word_top_n).each_with_index do |words, i|
          summary << "| ##{i} (#{counts[i]}) : #{words.keys.join(" ")}"
        end
        # skip ending |
      end

      summary.join("\n")
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

    def tw
      TERM_WEIGHT[_tw]
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
