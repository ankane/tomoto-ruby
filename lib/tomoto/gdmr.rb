module Tomoto
  class GDMR
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, degrees: [], alpha: 0.1, eta: 0.01, sigma: 1.0, sigma0: 3.0, alpha_epsilon: 1e-10, seed: nil)
      model = _new(to_tw(tw), k, degrees, alpha, sigma, sigma0, eta, alpha_epsilon, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      init_params(model, binding)
    end

    def add_doc(doc, numeric_metadata: [])
      _add_doc(prepare_doc(doc), numeric_metadata)
    end
  end
end
