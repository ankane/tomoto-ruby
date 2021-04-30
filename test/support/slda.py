import tomotopy as tp

model = tp.SLDAModel(vars=["l"])
print(model.alpha)
print(model.f)

model.add_doc(["new", "document"], y=[1.0])

model.train(0)
print(model.get_var_type(0))
