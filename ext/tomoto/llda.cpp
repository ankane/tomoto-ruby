#include <LLDA.h>

#include <rice/rice.hpp>

#include "utils.h"

void init_llda(Rice::Module& m) {
  Rice::define_class_under<tomoto::ILLDAModel, tomoto::ILDAModel>(m, "LLDA")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t k, tomoto::Float alpha, tomoto::Float eta, size_t seed) {
        tomoto::LDAArgs args;
        args.k = k;
        args.alpha = {alpha};
        args.eta = eta;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::ILLDAModel::create((tomoto::TermWeight)tw, args);
      }, Rice::Return().takeOwnership())
    .define_method(
      "_add_doc",
      [](tomoto::ILLDAModel& self, std::vector<std::string> words, std::vector<std::string> labels) {
        auto doc = buildDoc(words);
        doc.misc["labels"] = labels;
        return self.addDoc(doc);
      })
    .define_method(
      "topics_per_label",
      [](tomoto::ILLDAModel& self) {
        return self.getNumTopicsPerLabel();
      });
}
