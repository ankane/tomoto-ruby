import tomotopy as tp

model = tp.PLDAModel()
print(model.alpha)
print(model.latent_topics)
print(model.topics_per_label)

model.add_doc(["new", "document"], labels=["spam"])
