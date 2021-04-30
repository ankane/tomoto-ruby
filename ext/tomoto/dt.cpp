#include <DT.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_dt(Rice::Module& m) {
  Rice::define_class_under<tomoto::IDTModel, tomoto::ILDAModel>(m, "DT")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, size_t t, tomoto::Float alphaVar, tomoto::Float etaVar, tomoto::Float phiVar, tomoto::Float shapeA, tomoto::Float shapeB, tomoto::Float shapeC) {
        // Rice only supports 10 arguments
        size_t seed = -1;
        tomoto::DTArgs args;
        args.k = k;
        args.t = t;
        args.alpha = {alphaVar};
        args.eta = etaVar;
        args.phi = phiVar;
        args.shapeA = shapeA;
        args.shapeB = shapeB;
        args.shapeC = shapeC;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::IDTModel::create((tomoto::TermWeight)tw, args);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::IDTModel& self, std::vector<std::string> words, uint32_t timepoint) {
        auto doc = buildDoc(words);
        doc.misc["timepoint"] = timepoint;
        return self.addDoc(doc);
      })
    .define_method(
      "alpha",
      *[](tomoto::IDTModel& self) {
        Array res;
        for (size_t i = 0; i < self.getK(); i++) {
          Array res2;
          for (size_t j = 0; j < self.getT(); j++) {
            res2.push(self.getAlpha(i, j));
          }
          res.push(res2);
        }
        return res;
      })
    .define_method(
      "lr_a",
      *[](tomoto::IDTModel& self) {
        return self.getShapeA();
      })
    .define_method(
      "lr_a=",
      *[](tomoto::IDTModel& self, tomoto::Float value) {
        self.setShapeA(value);
        return value;
      })
    .define_method(
      "lr_b",
      *[](tomoto::IDTModel& self) {
        return self.getShapeB();
      })
    .define_method(
      "lr_b=",
      *[](tomoto::IDTModel& self, tomoto::Float value) {
        self.setShapeB(value);
        return value;
      })
    .define_method(
      "lr_c",
      *[](tomoto::IDTModel& self) {
        return self.getShapeC();
      })
    .define_method(
      "lr_c=",
      *[](tomoto::IDTModel& self, tomoto::Float value) {
        self.setShapeC(value);
        return value;
      })
    .define_method(
      "num_docs_by_timepoint",
      *[](tomoto::IDTModel& self) {
        return self.getNumDocsByT();
      })
    .define_method(
      "num_timepoints",
      *[](tomoto::IDTModel& self) {
        return self.getT();
      });
}
