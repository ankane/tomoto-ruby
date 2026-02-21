#include <string>
#include <vector>

#include <GDMR.h>

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "utils.h"

void init_gdmr(Rice::Module& m) {
  Rice::define_class_under<tomoto::IGDMRModel, tomoto::IDMRModel>(m, "GDMR")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t k, std::vector<uint64_t> degrees, tomoto::Float alpha, tomoto::Float sigma, tomoto::Float sigma0, tomoto::Float eta, tomoto::Float alpha_epsilon, size_t seed) {
        tomoto::GDMRArgs args;
        args.k = k;
        args.degrees = degrees;
        args.alpha = {alpha};
        args.sigma = sigma;
        args.sigma0 = sigma0;
        args.eta = eta;
        args.alphaEps = alpha_epsilon;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::IGDMRModel::create((tomoto::TermWeight)tw, args).release();
      }, Rice::Return().takeOwnership())
    .define_method(
      "_add_doc",
      [](tomoto::IGDMRModel& self, std::vector<std::string> words, std::vector<tomoto::Float> numeric_metadata) {
        auto doc = buildDoc(words);
        doc.misc["numeric_metadata"] = numeric_metadata;
        return self.addDoc(doc);
      })
    .define_method(
      "degrees",
      [](tomoto::IGDMRModel& self) {
        return self.getFs();
      })
    .define_method(
      "sigma0",
      [](tomoto::IGDMRModel& self) {
        return self.getSigma0();
      });
}
