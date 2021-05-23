require_relative "lib/tomoto/version"

Gem::Specification.new do |spec|
  spec.name          = "tomoto"
  spec.version       = Tomoto::VERSION
  spec.summary       = "High performance topic modeling for Ruby"
  spec.homepage      = "https://github.com/ankane/tomoto"
  spec.license       = "MIT"

  spec.author        = "Andrew Kane"
  spec.email         = "andrew@ankane.org"

  spec.files         = Dir[
    "*.{md,txt}", "{ext,lib}/**/*", "vendor/**/{README*,LICENSE*,COPYING*}",
    "vendor/eigen/Eigen/**/*", "vendor/EigenRand/EigenRand/**/*",
    "vendor/tomotopy/src/{Labeling,TopicModel,Utils}/**/*",
    "vendor/variant/include/**/*"
  ]
  spec.require_path  = "lib"
  spec.extensions    = ["ext/tomoto/extconf.rb"]

  spec.required_ruby_version = ">= 2.6"

  spec.add_dependency "rice", "~> 3"
end
