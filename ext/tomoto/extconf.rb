require "mkmf-rice"

$CXXFLAGS += " -std=c++17 $(optflags) -DEIGEN_MPL2_ONLY"

unless ENV["RUBY_CC_VERSION"]
  # AVX-512F not support yet
  # https://github.com/bab2min/tomotopy/issues/188
  $CXXFLAGS << " " << with_config("optflags", "-march=native -mno-avx512f")
end

apple_clang = RbConfig::CONFIG["CC_VERSION_MESSAGE"] =~ /apple clang/i

if apple_clang
  # silence rice warnings
  $CXXFLAGS += " -Wno-deprecated-declarations"
else
  # silence eigen warnings
  $CXXFLAGS += " -Wno-ignored-attributes -Wno-deprecated-copy"
end

# silence tomoto warnings
$CXXFLAGS += " -Wno-unused-variable -Wno-switch"

ext = File.expand_path(".", __dir__)
tomoto = File.expand_path("../../vendor/tomotopy/src/TopicModel", __dir__)
eigen = File.expand_path("../../vendor/eigen", __dir__)
eigen_rand = File.expand_path("../../vendor/EigenRand", __dir__)
variant = File.expand_path("../../vendor/variant/include", __dir__)

$srcs = Dir["{#{ext},#{tomoto}}/*.cpp"]
$INCFLAGS += " -I#{tomoto} -I#{eigen} -I#{eigen_rand} -I#{variant}"
$VPATH << tomoto

create_makefile("tomoto/tomoto")
