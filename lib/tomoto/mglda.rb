module Tomoto
  class MGLDA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k_g: 1, k_l: 1, t: 3, alpha_g: 0.1, alpha_l: 0.1, alpha_mg: 0.1, alpha_ml: 0.1, eta_g: 0.01) #, eta_l: 0.01, gamma: 0.1, seed: nil)
      model = _new(to_tw(tw), k_g, k_l, t, alpha_g, alpha_l, alpha_mg, alpha_ml, eta_g)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      model
    end

    def add_doc(doc, delimiter: ".")
      _add_doc(prepare_doc(doc), delimiter)
    end
  end
end
