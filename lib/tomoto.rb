# ext
begin
  require "tomoto/#{RUBY_VERSION.to_f}/tomoto"
rescue LoadError
  require "tomoto/tomoto"
end

# modules
require_relative "tomoto/ct"
require_relative "tomoto/dmr"
require_relative "tomoto/dt"
require_relative "tomoto/gdmr"
require_relative "tomoto/hdp"
require_relative "tomoto/hlda"
require_relative "tomoto/hpa"
require_relative "tomoto/lda"
require_relative "tomoto/llda"
require_relative "tomoto/mglda"
require_relative "tomoto/pa"
require_relative "tomoto/plda"
require_relative "tomoto/slda"
require_relative "tomoto/version"

module Tomoto
  PARALLEL_SCHEME = [:default, :none, :copy_merge, :partition]
  TERM_WEIGHT = [:one, :idf, :pmi]
end
