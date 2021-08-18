#include <fstream>
#include <iostream>

#include <LDA.h>

#include <rice/Class.hpp>
#include <rice/Hash.hpp>
#include <rice/Module.hpp>

#include "utils.h"

class DocumentObject
{
public:
  DocumentObject(const tomoto::DocumentBase* _doc, const tomoto::ITopicModel* _tm) : doc{ _doc }, tm{ _tm } {}

  const tomoto::DocumentBase* doc;
  const tomoto::ITopicModel* tm;
};

void init_lda(Rice::Module& m) {
  Rice::define_class_under<DocumentObject>(m, "Document")
    .define_method(
      "topics",
      *[](DocumentObject& self) {
        Rice::Hash res;
        auto topics = self.tm->getTopicsByDoc(self.doc);
        for (size_t i = 0; i < topics.size(); i++) {
          res[i] = topics[i];
        }
        return res;
      });

  Rice::define_class_under<tomoto::ILDAModel>(m, "LDA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, tomoto::Float alpha, tomoto::Float eta, size_t seed) {
        tomoto::LDAArgs args;
        args.k = k;
        args.alpha = {alpha};
        args.eta = eta;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::ILDAModel::create((tomoto::TermWeight)tw, args);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::ILDAModel& self, std::vector<std::string> words) {
        return self.addDoc(buildDoc(words));
      })
    .define_method(
      "_make_doc",
      *[](tomoto::ILDAModel& self, std::vector<std::string> words) {
        return DocumentObject(self.makeDoc(buildDoc(words)).release(), &self);
      })
    .define_method(
      "_infer",
      *[](tomoto::ILDAModel& self, DocumentObject& doc_object) {
        size_t iteration = 100, workers = 0, together = 0, ps = 0;
        float tolerance = -1;

        std::vector<tomoto::DocumentBase*> docs;
        auto doc = doc_object.doc;
        docs.emplace_back(const_cast<tomoto::DocumentBase*>(doc));
        float ll = self.infer(docs, iteration, tolerance, workers, (tomoto::ParallelScheme)ps, !!together)[0];

        auto topic_dist = self.getTopicsByDoc(doc);
        auto topic_res = Array();
        for (size_t i = 0; i < topic_dist.size(); i++) {
          topic_res.push(topic_dist[i]);
        }

        auto res = Array();
        res.push(topic_res);
        res.push(ll);
        return res;
      })
    .define_method(
      "alpha",
      *[](tomoto::ILDAModel& self) {
        Array res;
        for (size_t i = 0; i < self.getK(); i++) {
          res.push(self.getAlpha(i));
        }
        return res;
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
      "docs",
      *[](tomoto::ILDAModel& self) {
        Array res;
        auto n = self.getNumDocs();
        for (size_t i = 0; i < n; i++) {
          res.push(DocumentObject(self.getDoc(i), &self));
        }
        return res;
      })
    .define_method(
      "eta",
      *[](tomoto::ILDAModel& self) {
        return self.getEta();
      })
    .define_method(
      "global_step",
      *[](tomoto::ILDAModel& self) {
        return self.getGlobalStep();
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
      "num_docs",
      *[](tomoto::ILDAModel& self) {
        return self.getNumDocs();
      })
    .define_method(
      "num_vocabs",
      *[](tomoto::ILDAModel& self) {
        return self.getV();
      })
    .define_method(
      "num_words",
      *[](tomoto::ILDAModel& self) {
        return self.getN();
      })
    .define_method(
      "optim_interval",
      *[](tomoto::ILDAModel& self) {
        return self.getOptimInterval();
      })
    .define_method(
      "optim_interval=",
      *[](tomoto::ILDAModel& self, size_t value) {
        self.setOptimInterval(value);
        return value;
      })
    .define_method(
      "perplexity",
      *[](tomoto::ILDAModel& self) {
        return self.getPerplexity();
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
        Rice::Hash res;
        for (auto const& v : self.getWordsByTopicSorted(topicId, topN)) {
          res[v.first] = v.second;
        }
        return res;
      })
    .define_method(
      "_train",
      *[](tomoto::ILDAModel& self, size_t iteration, size_t workers, size_t ps) {
        self.train(iteration, workers, (tomoto::ParallelScheme)ps);
      })
    .define_method(
      "_tw",
      *[](tomoto::ILDAModel& self) {
        return (int)self.getTermWeight();
      })
    .define_method(
      "used_vocab_df",
      *[](tomoto::ILDAModel& self) {
        auto vocab = self.getVocabDf();
        Array res;
        for (size_t i = 0; i < self.getV(); i++) {
          res.push(vocab[i]);
        }
        return res;
      })
    .define_method(
      "used_vocab_freq",
      *[](tomoto::ILDAModel& self) {
        auto vocab = self.getVocabCf();
        Array res;
        for (size_t i = 0; i < self.getV(); i++) {
          res.push(vocab[i]);
        }
        return res;
      })
    .define_method(
      "used_vocabs",
      *[](tomoto::ILDAModel& self) {
        auto dict = self.getVocabDict();
        Array res;
        auto utf8 = Rice::Class(rb_cEncoding).call("const_get", "UTF_8");
        for (size_t i = 0; i < self.getV(); i++) {
          res.push(to_ruby<std::string>(dict.toWord(i)).call("force_encoding", utf8));
        }
        return res;
      })
    .define_method(
      "vocab_df",
      *[](tomoto::ILDAModel& self) {
        auto vocab = self.getVocabDf();
        Array res;
        for (size_t i = 0; i < vocab.size(); i++) {
          res.push(vocab[i]);
        }
        return res;
      })
    .define_method(
      "vocab_freq",
      *[](tomoto::ILDAModel& self) {
        auto vocab = self.getVocabCf();
        Array res;
        for (size_t i = 0; i < vocab.size(); i++) {
          res.push(vocab[i]);
        }
        return res;
      })
    .define_method(
      "vocabs",
      *[](tomoto::ILDAModel& self) {
        auto dict = self.getVocabDict();
        Array res;
        auto utf8 = Rice::Class(rb_cEncoding).call("const_get", "UTF_8");
        for (size_t i = 0; i < dict.size(); i++) {
          res.push(to_ruby<std::string>(dict.toWord(i)).call("force_encoding", utf8));
        }
        return res;
      });
}
