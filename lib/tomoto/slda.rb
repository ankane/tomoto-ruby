module Tomoto
  class SLDA
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, vars: "") #, seed: nil)
      model = _new(to_tw(tw), k, vars.split("").map { |v| to_glm(v) }) # , seed || -1)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      model
    end

    def add_doc(doc, y: [])
      _add_doc(prepare_doc(doc), y)
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
