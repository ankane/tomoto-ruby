# ext
require "tomoto/ext"

# modules
require "tomoto/ct"
require "tomoto/dmr"
require "tomoto/dt"
require "tomoto/hdp"
require "tomoto/hlda"
require "tomoto/hpa"
require "tomoto/lda"
require "tomoto/llda"
require "tomoto/plda"
require "tomoto/version"

module Tomoto
  TERM_WEIGHT = [:one, :idf, :pmi]
end
