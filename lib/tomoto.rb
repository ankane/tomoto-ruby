# ext
require "tomoto/ext"

# modules
require "tomoto/ct"
require "tomoto/hdp"
require "tomoto/lda"
require "tomoto/version"

module Tomoto
  TERM_WEIGHT = [:one, :idf, :pmi]
end
