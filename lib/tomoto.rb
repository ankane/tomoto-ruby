# ext
require "tomoto/ext"

# modules
require "tomoto/ct"
require "tomoto/dmr"
require "tomoto/dt"
require "tomoto/hdp"
require "tomoto/hlda"
require "tomoto/lda"
require "tomoto/version"

module Tomoto
  TERM_WEIGHT = [:one, :idf, :pmi]
end
