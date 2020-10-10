module Tomoto
  class HLDA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, depth: 2, alpha: 0.1, eta: 0.01, gamma: 0.1, seed: nil)
      model = _new(to_tw(tw), depth, alpha, eta, gamma, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      model
    end
  end
end
