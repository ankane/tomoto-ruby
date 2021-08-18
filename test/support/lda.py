import tomotopy as tp

model = tp.LDAModel()
print(model.alpha)
print(model.eta)
print(model.global_step)
print(model.optim_interval)
print(model.perplexity)
print(model.tw)

model.add_doc(["new", "document"])
model.burn_in = 100
print(model.burn_in)
model.train(0)
print(model.num_words)
print(model.num_vocabs)
print(model.vocabs)

print(model.get_topic_words(0))

model = tp.LDAModel(k=2, seed=42)
model.add_doc(["this", "is", "a", "test"])
model.add_doc(["another", "document"])
model.add_doc(["a", "new", "document"])
model.train(100)
print(model.docs[0].get_topics())
doc = model.make_doc(['unseen', 'document'])
topic_dist, ll = model.infer(doc)
print(topic_dist)
print(ll)
