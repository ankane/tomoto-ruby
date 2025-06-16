#include <string>
#include <vector>

#include <PLDA.h>

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "utils.h"

void init_plda(Rice::Module& m) {
  Rice::define_class_under<tomoto::IPLDAModel, tomoto::ILLDAModel>(m, "PLDA")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t latent_topics, tomoto::Float alpha, tomoto::Float eta, size_t seed) {
        tomoto::PLDAArgs args;
        args.numLatentTopics = latent_topics;
        args.alpha = {alpha};
        args.eta = eta;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::IPLDAModel::create((tomoto::TermWeight)tw, args);
      }, Rice::Return().takeOwnership())
    .define_method(
      "_add_doc",
      [](tomoto::IPLDAModel& self, std::vector<std::string> words, std::vector<std::string> labels) {
        auto doc = buildDoc(words);
        doc.misc["labels"] = labels;
        return self.addDoc(doc);
      })
    .define_method(
      "latent_topics",
      [](tomoto::IPLDAModel& self) {
        return self.getNumLatentTopics();
      });
}
