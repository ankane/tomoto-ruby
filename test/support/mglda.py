import tomotopy as tp

model = tp.MGLDAModel()
print(model.alpha_g)
print(model.alpha_l)
print(model.alpha_mg)
print(model.alpha_ml)
print(model.eta_g)
print(model.eta_l)
print(model.gamma)
print(model.k_g)
print(model.k_l)
print(model.t)

model.add_doc(["new", "document"], delimiter=".")
