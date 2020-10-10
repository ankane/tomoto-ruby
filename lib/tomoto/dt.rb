module Tomoto
  class DT
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, t: 1, alpha_var: 0.1, eta_var: 0.1, phi_var: 0.1, lr_a: 0.01, lr_b: 0.1, lr_c: 0.55) #, seed: nil)
      model = _new(to_tw(tw), k, t, alpha_var, eta_var, phi_var, lr_a, lr_b, lr_c)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      init_params(model, binding)
    end

    def add_doc(doc, timepoint: 0)
      _add_doc(prepare_doc(doc), timepoint)
    end
  end
end
