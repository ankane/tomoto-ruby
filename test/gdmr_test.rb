require_relative "test_helper"

class GDMRTest < Minitest::Test
  def test_works
    model = Tomoto::GDMR.new
    assert_kind_of Tomoto::DMR, model
    assert_kind_of Tomoto::LDA, model

    # model.add_doc(["new", "document"], metadata: [1.0])
  end
end
