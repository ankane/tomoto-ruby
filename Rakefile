require "bundler/gem_tasks"
require "rake/testtask"
require "rake/extensiontask"

task default: :test
Rake::TestTask.new do |t|
  t.libs << "test"
  t.pattern = "test/**/*_test.rb"
end

Rake::ExtensionTask.new("tomoto") do |ext|
  ext.name = "ext"
  ext.lib_dir = "lib/tomoto"
end

task :check_license do
  raise "Missing vendor license" unless File.exist?("vendor/tomotopy/LICENSE")
end

task :remove_ext do
  Dir["lib/tomoto/**/*.{bundle,so}"].each do |path|
    File.unlink(path)
  end
end

Rake::Task["build"].enhance [:check_license, :remove_ext]

# rake clean excludes **/core by default
CLEAN.exclude("**/Eigen/Core")
