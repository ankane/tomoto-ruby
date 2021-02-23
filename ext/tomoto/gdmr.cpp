#include <GDMR.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_gdmr(Rice::Module& m) {
  Rice::define_class_under<tomoto::IGDMRModel, tomoto::IDMRModel>(m, "GDMR")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, std::vector<uint64_t> degrees, tomoto::Float alpha, tomoto::Float sigma, tomoto::Float sigma0, tomoto::Float eta, tomoto::Float alpha_epsilon, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::IGDMRModel::create((tomoto::TermWeight)tw, k, degrees, alpha, sigma, sigma0, eta, alpha_epsilon, seed);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::IGDMRModel& self, std::vector<std::string> words, std::vector<tomoto::Float> metadata) {
        auto doc = buildDoc(words);
        doc.misc["metadata"] = metadata;
        self.addDoc(doc);
      })
    .define_method(
      "degrees",
      *[](tomoto::IGDMRModel& self) {
        return self.getFs();
      })
    .define_method(
      "sigma0",
      *[](tomoto::IGDMRModel& self) {
        return self.getSigma0();
      });
}
