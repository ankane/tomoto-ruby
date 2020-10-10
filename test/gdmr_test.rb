require_relative "test_helper"

class GDMRTest < Minitest::Test
  def test_works
    model = Tomoto::GDMR.new
    assert_kind_of Tomoto::DMR, model
    assert_kind_of Tomoto::LDA, model
  end
end
