# tomoto.rb

:tomato: [tomoto](https://github.com/bab2min/tomotopy) - high performance topic modeling - for Ruby

[![Build Status](https://github.com/ankane/tomoto-ruby/workflows/build/badge.svg?branch=master)](https://github.com/ankane/tomoto-ruby/actions)

## Installation

Add this line to your application’s Gemfile:

```ruby
gem "tomoto"
```

ARM is not currently supported

## Getting Started

Train a model

```ruby
model = Tomoto::LDA.new(k: 2)
model.add_doc("text from document one")
model.add_doc("text from document two")
model.add_doc("text from document three")
model.train(100) # iterations
```

Get the summary

```ruby
model.summary
```

Get topic words

```ruby
model.topic_words
```

Save the model to a file

```ruby
model.save("model.bin")
```

Load the model from a file

```ruby
model = Tomoto::LDA.load("model.bin")
```

Get topic probabilities for a document

```ruby
doc = model.docs[0]
doc.topics
```

Get the number of words for each topic

```ruby
model.count_by_topics
```

Get the vocab

```ruby
model.vocabs
```

Get the log likelihood per word

```ruby
model.ll_per_word
```

Perform inference for unseen documents

```ruby
doc = model.make_doc("unseen doc")
topic_dist, ll = model.infer(doc)
```

## Models

Supports:

- Latent Dirichlet Allocation (`LDA`)
- Labeled LDA (`LLDA`)
- Partially Labeled LDA (`PLDA`)
- Supervised LDA (`SLDA`)
- Dirichlet Multinomial Regression (`DMR`)
- Generalized Dirichlet Multinomial Regression (`GDMR`)
- Hierarchical Dirichlet Process (`HDP`)
- Hierarchical LDA (`HLDA`)
- Multi Grain LDA (`MGLDA`)
- Pachinko Allocation (`PA`)
- Hierarchical PA (`HPA`)
- Correlated Topic Model (`CT`)
- Dynamic Topic Model (`DT`)

## API

This library follows the [tomotopy API](https://bab2min.github.io/tomotopy/v0.9.0/en/). There are a few changes to make it more Ruby-like:

- The `get_` prefix has been removed from methods (`topic_words` instead of `get_topic_words`)
- Methods that return booleans use `?` instead of `is_`  (`live_topic?` instead of `is_live_topic`)

If a method or option you need isn’t supported, feel free to open an issue.

## Examples

- [LDA](examples/lda_basic.rb)
- [HDP](examples/hdp_basic.rb)

## Tokenization

Documents are tokenized by whitespace by default, or you can perform your own tokenization.

```ruby
model.add_doc(["tokens", "from", "document", "one"])
```

## Performance

tomoto uses AVX2, AVX, or SSE2 instructions to increase performance on machines that support it. Check which instruction set architecture it’s using with:

```ruby
Tomoto.isa
```

## Parallelism

Choose a [parallelism algorithm](https://bab2min.github.io/tomotopy/v0.9.0/en/#parallel-sampling-algorithms) with:

```ruby
model.train(parallel: :partition)
```

Supported values are `:default`, `:none`, `:copy_merge`, and `:partition`.

## History

View the [changelog](https://github.com/ankane/tomoto-ruby/blob/master/CHANGELOG.md)

## Contributing

Everyone is encouraged to help improve this project. Here are a few ways you can help:

- [Report bugs](https://github.com/ankane/tomoto-ruby/issues)
- Fix bugs and [submit pull requests](https://github.com/ankane/tomoto-ruby/pulls)
- Write, clarify, or fix documentation
- Suggest or add new features

To get started with development:

```sh
git clone --recursive https://github.com/ankane/tomoto-ruby.git
cd tomoto-ruby
bundle install
bundle exec rake compile
bundle exec rake test
```
