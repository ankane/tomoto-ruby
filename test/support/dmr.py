import tomotopy as tp

model = tp.DMRModel(k=2)
print(model.alpha)
print(model.alpha_epsilon)
print(model.eta)
print(model.f)
print(model.lambdas)
print(model.metadata_dict)
print(model.sigma)

model.add_doc(["new", "document"], metadata="hello")

model.train(0)
print([len(x) for x in model.alpha])
print(model.alpha[0][0])
print(model.alpha[1][0])
print([len(x) for x in model.lambdas])
print(model.lambdas[0][0])
print(model.lambdas[1][0])
print(model.metadata_dict)
