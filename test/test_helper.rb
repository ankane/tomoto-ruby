require "bundler/setup"
Bundler.require(:default)
require "minitest/autorun"
require "minitest/pride"
require "tmpdir"

class Minitest::Test
  def teardown
    @tempfile = nil
  end

  def tempfile
    @tempfile ||= "#{Dir.mktmpdir}/#{Time.now.to_f}"
  end
end
