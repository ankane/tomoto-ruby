import tomotopy as tp

model = tp.DTModel()
print(model.alpha)
# print(model.eta)
print(model.lr_a)
print(model.lr_b)
print(model.lr_c)
print(model.num_timepoints)
print(model.num_docs_by_timepoint)

model.add_doc(["new", "document"], timepoint=0)
