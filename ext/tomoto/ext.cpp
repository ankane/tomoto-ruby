// stdlib
#include <fstream>
#include <iostream>

// tomoto
#include <CT.h>
#include <DMR.h>
#include <HDP.h>
#include <LDA.h>

// rice
#include <rice/Array.hpp>
#include <rice/Hash.hpp>
#include <rice/Module.hpp>

using Rice::Array;
using Rice::Class;
using Rice::Hash;
using Rice::Module;
using Rice::Object;
using Rice::define_class_under;
using Rice::define_module;

template<>
Object to_ruby<std::vector<float>>(std::vector<float> const & x)
{
  Array res;
  for (auto const& v : x) {
    res.push(v);
  }
  return res;
}

extern "C"
void Init_ext()
{
  Module rb_mTomoto = define_module("Tomoto")
    .define_singleton_method(
      "isa",
      *[]() {
        #ifdef __AVX2__
          return "avx2";
        #elif defined(__AVX__)
          return "avx";
        #elif defined(__SSE2__) || defined(__x86_64__) || defined(_WIN64)
          return "sse2";
        #else
          return "none";
        #endif
      });

  Class rb_cLDA = define_class_under<tomoto::ILDAModel>(rb_mTomoto, "LDA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, float alpha, float eta, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::ILDAModel::create((tomoto::TermWeight)tw, k, alpha, eta, seed);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::ILDAModel& self, Array rb_words) {
        std::vector<std::string> words;
        words.reserve(rb_words.size());
        for (auto const& v : rb_words) {
          words.push_back(from_ruby<std::string>(v));
        }
        self.addDoc(words);
      })
    .define_method(
      "alpha",
      *[](tomoto::ILDAModel& self) {
        return self.getAlpha();
      })
    .define_method(
      "burn_in",
      *[](tomoto::ILDAModel& self) {
        return self.getBurnInIteration();
      })
    .define_method(
      "burn_in=",
      *[](tomoto::ILDAModel& self, size_t iteration) {
        self.setBurnInIteration(iteration);
        return iteration;
      })
    .define_method(
      "_count_by_topics",
      *[](tomoto::ILDAModel& self) {
        Array res;
        for (auto const& v : self.getCountByTopic()) {
          res.push(v);
        }
        return res;
      })
    .define_method(
      "eta",
      *[](tomoto::ILDAModel& self) {
        return self.getEta();
      })
    .define_method(
      "k",
      *[](tomoto::ILDAModel& self) {
        return self.getK();
      })
    .define_method(
      "_load",
      *[](tomoto::ILDAModel& self, const char* filename) {
        std::ifstream str{ filename, std::ios_base::binary };
        if (!str) throw std::runtime_error{ std::string("cannot open file '") + filename + std::string("'") };
        std::vector<uint8_t> extra_data;
        self.loadModel(str, &extra_data);
      })
    .define_method(
      "ll_per_word",
      *[](tomoto::ILDAModel& self) {
        return self.getLLPerWord();
      })
    .define_method(
      "num_words",
      *[](tomoto::ILDAModel& self) {
        return self.getN();
      })
    .define_method(
      "num_vocabs",
      *[](tomoto::ILDAModel& self) {
        return self.getV();
      })
    .define_method(
      "_prepare",
      *[](tomoto::ILDAModel& self, size_t minCnt, size_t minDf, size_t rmTop) {
        self.prepare(true, minCnt, minDf, rmTop);
      })
    .define_method(
      "_removed_top_words",
      *[](tomoto::ILDAModel& self, size_t rmTop) {
        Array res;
        auto dict = self.getVocabDict();
        size_t size = dict.size();
        for (size_t i = rmTop; i > 0; i--) {
          res.push(dict.toWord(size - i));
        }
        return res;
      })
    .define_method(
      "_save",
      *[](tomoto::ILDAModel& self, const char* filename, bool full) {
        std::ofstream str{ filename, std::ios_base::binary };
        std::vector<uint8_t> extra_data;
        self.saveModel(str, full, &extra_data);
      })
    .define_method(
      "_topic_words",
      *[](tomoto::ILDAModel& self, size_t topicId, size_t topN) {
        Hash res;
        for (auto const& v : self.getWordsByTopicSorted(topicId, topN)) {
          res[v.first] = v.second;
        }
        return res;
      })
    .define_method(
      "_train",
      *[](tomoto::ILDAModel& self, size_t iteration, size_t workers) {
        size_t ps = 0;
        self.train(iteration, workers, (tomoto::ParallelScheme)ps);
      })
    .define_method(
      "vocabs",
      *[](tomoto::ILDAModel& self) {
        auto dict = self.getVocabDict();
        Array res;
        auto utf8 = Class(rb_cEncoding).call("const_get", "UTF_8");
        for (size_t i = 0; i < dict.size(); i++) {
          res.push(to_ruby<std::string>(dict.toWord(i)).call("force_encoding", utf8));
        }
        return res;
      });

  Class rb_cCT = define_class_under<tomoto::ICTModel, tomoto::ILDAModel>(rb_mTomoto, "CT")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, float alpha, float eta, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::ICTModel::create((tomoto::TermWeight)tw, k, alpha, eta, seed);
      })
    .define_method(
      "num_beta_sample",
      *[](tomoto::ICTModel& self) {
        return self.getNumBetaSample();
      })
    .define_method(
      "num_beta_sample=",
      *[](tomoto::ICTModel& self, size_t numSample) {
        self.setNumBetaSample(numSample);
        return numSample;
      })
    .define_method(
      "num_tmn_sample",
      *[](tomoto::ICTModel& self) {
        return self.getNumTMNSample();
      })
    .define_method(
      "num_tmn_sample=",
      *[](tomoto::ICTModel& self, size_t numSample) {
        self.setNumTMNSample(numSample);
        return numSample;
      })
    .define_method(
      "prior_cov",
      *[](tomoto::ICTModel& self) {
        return self.getPriorCov();
      })
    .define_method(
      "prior_mean",
      *[](tomoto::ICTModel& self) {
        return self.getPriorMean();
      });

  Class rb_cDMR = define_class_under<tomoto::IDMRModel, tomoto::ILDAModel>(rb_mTomoto, "DMR")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, float alpha, float sigma, float eta, float alpha_epsilon, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::IDMRModel::create((tomoto::TermWeight)tw, k, alpha, sigma, eta, alpha_epsilon, seed);
      })
    .define_method(
      "alpha_epsilon",
      *[](tomoto::IDMRModel& self) {
        return self.getAlphaEps();
      })
    .define_method(
      "alpha_epsilon=",
      *[](tomoto::IDMRModel& self, float alphaEps) {
        self.setAlphaEps(alphaEps);
        return alphaEps;
      })
    .define_method(
      "f",
      *[](tomoto::IDMRModel& self) {
        return self.getF();
      })
    .define_method(
      "sigma",
      *[](tomoto::IDMRModel& self) {
        return self.getSigma();
      });

  Class rb_cHDP = define_class_under<tomoto::IHDPModel, tomoto::ILDAModel>(rb_mTomoto, "HDP")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, float alpha, float eta, float gamma, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::IHDPModel::create((tomoto::TermWeight)tw, k, alpha, eta, gamma, seed);
      })
    .define_method(
      "gamma",
      *[](tomoto::IHDPModel& self) {
        return self.getGamma();
      })
    .define_method(
      "live_k",
      *[](tomoto::IHDPModel& self) {
        return self.getLiveK();
      })
    .define_method(
      "live_topic?",
      *[](tomoto::IHDPModel& self, size_t tid) {
        return self.isLiveTopic(tid);
      })
    .define_method(
      "num_tables",
      *[](tomoto::IHDPModel& self) {
        return self.getTotalTables();
      });
}
