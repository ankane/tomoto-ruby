# tomoto

:tomato: [tomoto](https://github.com/bab2min/tomotopy) - high performance topic modeling - for Ruby

[![Build Status](https://travis-ci.org/ankane/tomoto.svg?branch=master)](https://travis-ci.org/ankane/tomoto)

## Installation

Add this line to your application’s Gemfile:

```ruby
gem 'tomoto'
```

It can take 10-20 minutes to compile the extension.

## Getting Started

Train a model

```ruby
model = Tomoto::LDA.new(k: 3)
model.add_doc("text from document one")
model.add_doc("text from document two")
model.add_doc("text from document three")
model.train(100)
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

## Models

Supports:

- Latent Dirichlet Allocation (`LDA`)
- Labeled LDA (`LLDA`) - *in development*
- Partially Labeled LDA (`PLDA`) - *in development*
- Supervised LDA (`SLDA`) - *in development*
- Dirichlet Multinomial Regression (`DMR`)
- Generalized Dirichlet Multinomial Regression (`GDMR`) - *in development*
- Hierarchical Dirichlet Process (`HDP`)
- Hierarchical LDA (`HLDA`)
- Multi Grain LDA (`MGLDA`) - *in development*
- Pachinko Allocation (`PA`) - *in development*
- Hierarchical PA (`HPA`)
- Correlated Topic Model (`CT`)
- Dynamic Topic Model (`DT`)

## Parameters

```ruby
Tomoto::LDA.new(
  tw: :one, # or :idf, :pmi
  min_cf: 0,
  min_df: 0,
  rm_top: 0,
  k: 1,
  alpha: 0.1,
  eta: 0.01,
  seed: nil
)
```

## Tokenization

Documents are tokenized by whitespace by default, or you can perform your own tokenization.

```ruby
model.add_doc(["tokens", "from", "document", "one"])
```

## Performance

tomoto uses AVX2, AVX, or SSE2 instructions to increase performance on machines that support it. Check what it’s using with:

```ruby
Tomoto.isa
```

## History

View the [changelog](https://github.com/ankane/tomoto/blob/master/CHANGELOG.md)

## Contributing

Everyone is encouraged to help improve this project. Here are a few ways you can help:

- [Report bugs](https://github.com/ankane/tomoto/issues)
- Fix bugs and [submit pull requests](https://github.com/ankane/tomoto/pulls)
- Write, clarify, or fix documentation
- Suggest or add new features

To get started with development:

```sh
git clone --recursive https://github.com/ankane/tomoto.git
cd tomoto
bundle install
bundle exec rake compile
bundle exec rake test
```
