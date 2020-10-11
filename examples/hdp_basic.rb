# ported from https://github.com/bab2min/tomotopy/blob/main/examples/hdp_basic.py

require "tomoto"

def hdp_example(input_file, save_path)
  mdl = Tomoto::HDP.new(tw: :one, min_cf: 3, rm_top: 5, seed: 42)
  File.foreach(input_file) do |line|
    ch = line.strip.split(/[[:space:]]+/)
    mdl.add_doc(ch)
  end
  mdl.burn_in = 100
  mdl.train(0)
  puts "Num docs: #{mdl.num_docs}, Vocab size: #{mdl.used_vocabs.length}, Num words: #{mdl.num_words}"
  puts "Removed top words: #{mdl.removed_top_words}"
  puts "Training..."
  100.times do |i|
    mdl.train(10)
    puts "Iteration: #{i * 10}\tLog-likelihood: #{mdl.ll_per_word}\tNum. of topics: #{mdl.live_k}"
  end

  puts mdl.summary
  puts "Saving..."
  mdl.save(save_path)

  important_topics = mdl.count_by_topics.map.with_index.sort_by { |x| -x[0] }.map { |x| x[1] }
  important_topics.each do |k|
    next unless mdl.live_topic?(k)
    puts "Topic ##{k}"
    mdl.topic_words(k).each do |word, prob|
      puts "\t\t#{word}\t#{prob}"
    end
  end
end

# You can get the sample data file 'enwiki-stemmed-1000.txt'
# at https://drive.google.com/file/d/18OpNijd4iwPyYZ2O7pQoPyeTAKEXa71J/view?usp=sharing

puts "Running HDP"
hdp_example("enwiki-stemmed-1000.txt", "test.hdp.bin")
