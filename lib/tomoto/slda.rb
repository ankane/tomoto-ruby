module Tomoto
  class SLDA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, vars: "", alpha: 0.1, eta: 0.01, mu: [], nu_sq: [], glm_param: [], seed: nil)
      model = _new(to_tw(tw), k, vars.split("").map { |v| to_glm(v) }, alpha, eta, mu, nu_sq, glm_param, seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      init_params(model, binding)
    end

    def add_doc(doc, y: [])
      _add_doc(prepare_doc(doc), y)
    end

    def var_type(var_id)
      raise "train() should be called first" unless @prepared
      _var_type(var_id)
    end

    private

    class << self
      private

      def to_glm(v)
        case v
        when "l"
          0
        when "b"
          1
        else
          raise "Invalid var: #{v}"
        end
      end
    end
  end
end
