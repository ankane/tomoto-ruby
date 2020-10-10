module Tomoto
  class GDMR
    def self.new(tw: :one, min_cf: 0, min_df: 0, rm_top: 0, k: 1, degrees: [])
      model = _new(to_tw(tw), k, degrees)
      model.instance_variable_set(:@min_cf, min_cf)
      model.instance_variable_set(:@min_df, min_df)
      model.instance_variable_set(:@rm_top, rm_top)
      model
    end

    def add_doc(doc, metadata: [])
      _add_doc(prepare_doc(doc), metadata.map(&:to_s))
    end
  end
end
