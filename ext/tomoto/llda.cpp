#include <cstddef>
#include <string>
#include <vector>

#include <Dictionary.h>
#include <LDA.h>
#include <LLDA.h>
#include <TopicModel.hpp>

#include <rice/rice.hpp>
#include <rice/stl.hpp>

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
        return tomoto::ILLDAModel::create(static_cast<tomoto::TermWeight>(tw), args).release();
      }, Rice::Return().takeOwnership())
    .define_method(
      "_add_doc",
      [](tomoto::ILLDAModel& self, const std::vector<std::string>& words, const std::vector<std::string>& labels) {
        tomoto::RawDoc doc = buildDoc(words);
        doc.misc["labels"] = labels;
        return self.addDoc(doc);
      })
    .define_method(
      "topics_per_label",
      [](tomoto::ILLDAModel& self) {
        return self.getNumTopicsPerLabel();
      })
    .define_method(
      "topic_label_dict",
      [](tomoto::ILLDAModel& self) {
        const auto& dict = self.getTopicLabelDict();
        Rice::Array res;
        Rice::Object utf8(Rice::Encoding::utf8());
        for (size_t i = 0; i < dict.size(); i++) {
          Rice::String value(dict.toWord(i));
          res.push(value.call("force_encoding", utf8), false);
        }
        return res;
      });
}
