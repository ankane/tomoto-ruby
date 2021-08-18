module Tomoto
  class LDA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, alpha: 0.1, eta: 0.01, seed: nil)
      model = _new(to_tw(tw), k, alpha, eta, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      init_params(model, binding)
    end

    def self.load(filename)
      model = new
      model._load(filename)
      model
    end

    def add_doc(doc)
      _add_doc(prepare_doc(doc))
    end

    def make_doc(doc)
      _make_doc(tokenize_doc(doc))
    end

    # TODO support multiple docs
    def infer(doc, iter: 100, tolerance: -1, workers: 0, parallel: :default, together: 0)
      raise "cannot infer with untrained model" unless defined?(@prepared)
      _infer(doc, iter, tolerance, workers, to_ps(parallel), together)
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

      summary << "<Basic Info>"
      basic_info(summary)
      summary << "|"

      summary << "<Training Info>"
      training_info(summary)
      summary << "|"

      if initial_hp
        summary << "<Initial Parameters>"
        initial_params_info(summary)
        summary << "|"
      end

      if params
        summary << "<Parameters>"
        params_info(summary)
        summary << "|"
      end

      if topic_word_top_n > 0
        summary << "<Topics>"
        topics_info(summary, topic_word_top_n: topic_word_top_n)
        summary << "|"
      end

      # skip ending |
      summary.pop

      summary.join("\n")
    end

    def topic_words(topic_id = nil, top_n: 10)
      if topic_id
        _topic_words(topic_id, top_n)
      else
        k.times.map { |i| _topic_words(i, top_n) }
      end
    end

    def train(iterations = 10, workers: 0, parallel: :default)
      prepare
      _train(iterations, workers, to_ps(parallel))
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
      tokenize_doc(doc)
    end

    def tokenize_doc(doc)
      doc = doc.split(/[[:space:]]+/) unless doc.is_a?(Array)
      doc
    end

    def basic_info(summary)
      sum = used_vocab_freq.sum.to_f
      mapped = used_vocab_freq.map { |v| v / sum }
      entropy = mapped.map { |v| v * Math.log(v) }.sum

      summary << "| #{self.class.name.sub("Tomoto::", "")} (current version: #{VERSION})"
      summary << "| #{num_docs} docs, #{num_words} words"
      summary << "| Total Vocabs: #{vocabs.size}, Used Vocabs: #{used_vocabs.size}"
      summary << "| Entropy of words: %.5f" % entropy
      summary << "| Removed Vocabs: #{removed_top_words.any? ? removed_top_words.join(" ") : "<NA>"}"
    end

    def training_info(summary)
      summary << "| Iterations: #{global_step}, Burn-in steps: #{burn_in}"
      summary << "| Optimization Interval: #{optim_interval}"
      summary << "| Log-likelihood per word: %.5f" % ll_per_word
    end

    def initial_params_info(summary)
      if defined?(@init_params)
        @init_params.each do |k, v|
          summary << "| #{k}: #{v}"
        end
      else
        summary << "| Not Available"
      end
    end

    def params_info(summary)
      summary << "| alpha (Dirichlet prior on the per-document topic distributions)"
      summary << "|  #{alpha}"
      summary << "| eta (Dirichlet prior on the per-topic word distribution)"
      summary << "|  %.5f" % eta
    end

    def topics_info(summary, topic_word_top_n:)
      counts = count_by_topics
      topic_words(top_n: topic_word_top_n).each_with_index do |words, i|
        summary << "| ##{i} (#{counts[i]}) : #{words.keys.join(" ")}"
      end
    end

    def to_ps(ps)
      PARALLEL_SCHEME.index(ps) || (raise ArgumentError, "Invalid parallel scheme: #{ps}")
    end

    class << self
      private

      def to_tw(tw)
        TERM_WEIGHT.index(tw) || (raise ArgumentError, "Invalid tw: #{tw}")
      end

      def init_params(model, binding)
        init_params = {}
        method(:new).parameters.each do |v|
          next if v[0] != :key
          init_params[v[1]] = binding.local_variable_get(v[1]).inspect
        end
        model.instance_variable_set(:@init_params, init_params)
        model
      end
    end
  end
end
