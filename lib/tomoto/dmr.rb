module Tomoto
  class DMR
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, alpha: 0.1, eta: 0.01, sigma: 1.0, alpha_epsilon: 1e-10, seed: nil)
      model = _new(to_tw(tw), k, alpha, sigma, eta, alpha_epsilon, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      init_params(model, binding)
    end

    def add_doc(doc, metadata: "")
      _add_doc(prepare_doc(doc), metadata)
    end

    def lambdas
      if f == 0
        []
      else
        k.times.map { |i| _lambdas(i) }
      end
    end

    def alpha
      lambdas.map { |v| v.map { |v2| Math.exp(v2) } }
    end
  end
end
