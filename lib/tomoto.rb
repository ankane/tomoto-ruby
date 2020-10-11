# ext
require "tomoto/ext"

# modules
require "tomoto/ct"
require "tomoto/dmr"
require "tomoto/dt"
require "tomoto/gdmr"
require "tomoto/hdp"
require "tomoto/hlda"
require "tomoto/hpa"
require "tomoto/lda"
require "tomoto/llda"
require "tomoto/mglda"
require "tomoto/pa"
require "tomoto/plda"
require "tomoto/slda"
require "tomoto/version"

module Tomoto
  PARALLEL_SCHEME = [:default, :none, :copy_merge, :partition]
  TERM_WEIGHT = [:one, :idf, :pmi]
end
