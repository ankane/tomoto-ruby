import tomotopy as tp

model = tp.LLDAModel()
print(model.alpha)

model.add_doc(["new", "document"], labels=["spam"])
