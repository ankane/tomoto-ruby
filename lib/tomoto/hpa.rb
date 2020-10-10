module Tomoto
  class HPA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k1: 1, k2: 1, alpha: 0.1, eta: 0.01, seed: nil)
      model = _new(to_tw(tw), k1, k2, alpha, eta, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      init_params(model, binding)
    end
  end
end
