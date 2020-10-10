module Tomoto
  class HLDA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, depth: 2, alpha: 0.1, eta: 0.01, gamma: 0.1, seed: nil)
      model = _new(to_tw(tw), depth, alpha, eta, gamma, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      model
    end

    def children_topics(topic_id)
      check_topic(topic_id)
      _children_topics(topic_id)
    end

    def level(topic_id)
      check_topic(topic_id)
      _live_topic?(topic_id) ? _level(topic_id) : -1
    end

    def live_topic?(topic_id)
      check_topic(topic_id)
      _live_topic?(topic_id)
    end

    private

    def check_topic(topic_id)
      raise "topic_id must be < K" if topic_id >= k
      raise "train() should be called first" unless @prepared
    end
  end
end
