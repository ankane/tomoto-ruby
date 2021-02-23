#include <LLDA.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_llda(Rice::Module& m) {
  Rice::define_class_under<tomoto::ILLDAModel, tomoto::ILDAModel>(m, "LLDA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, tomoto::Float alpha, tomoto::Float eta, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::ILLDAModel::create((tomoto::TermWeight)tw, k, alpha, eta, seed);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::ILLDAModel& self, std::vector<std::string> words, std::vector<std::string> labels) {
        auto doc = buildDoc(words);
        doc.misc["labels"] = labels;
        self.addDoc(doc);
      })
    .define_method(
      "topics_per_label",
      *[](tomoto::ILLDAModel& self) {
        return self.getNumTopicsPerLabel();
      });
}
