import tomotopy as tp

model = tp.HLDAModel()
print(model.alpha)
model.train(0)

print(model.children_topics(0))
print(model.depth)
print(model.level(0))
print(model.is_live_topic(0))
print(model.gamma)
print(model.live_k)
print(model.num_docs_of_topic(0))
print(model.parent_topic(0))
