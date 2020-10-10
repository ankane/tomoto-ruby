require_relative "test_helper"

class MGLDATest < Minitest::Test
  def test_works
    model = Tomoto::MGLDA.new
    assert_kind_of Tomoto::LDA, model

    model.add_doc(["new", "document"], delimiter: ".")
  end
end
