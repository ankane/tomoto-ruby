import tomotopy as tp

model = tp.LDAModel(k=2, seed=42)
model.add_doc(["this is a test"])
model.add_doc(["another document"])
model.add_doc(["a new document"])
model.train(100)
print(model.docs[0].get_topics())
