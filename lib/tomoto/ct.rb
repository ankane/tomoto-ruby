module Tomoto
  class CT
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, alpha: 0.1, eta: 0.01, seed: nil)
      model = _new(to_tw(tw), k, alpha, eta, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      model
    end

    def correlations(topic_id = nil)
      prepare
      if topic_id
        _correlations(topic_id)
      else
        k.times.map { |i| _correlations(i) }
      end
    end

    def prior_cov
      _prior_cov.each_slice(k).to_a
    end
  end
end
