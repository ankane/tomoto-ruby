require "bundler/gem_tasks"
require "rake/testtask"
require "rake/extensiontask"

task default: :test
Rake::TestTask.new do |t|
  t.libs << "test"
  t.pattern = "test/**/*_test.rb"
end

ENV["RUBY_CC_VERSION"] = "3.1.0:3.0.0:2.7.0"
ENV["MACOSX_DEPLOYMENT_TARGET"] = "10.14"

gemspec = Bundler.load_gemspec("tomoto.gemspec")
exttask = Rake::ExtensionTask.new("tomoto", gemspec) do |ext|
  ext.ext_dir = "ext/tomoto"
  ext.lib_dir = File.join(*["lib", "tomoto", ENV["FAT_DIR"]].compact)
  ext.cross_compile = true
  ext.cross_platform = %w[x86_64-linux x86_64-darwin]
end

namespace "gem" do
  exttask.cross_platform.each do |platform|
    desc "Build the native binary gems"
    multitask "native" => platform

    task "prepare" do
      require "rake_compiler_dock"
    end

    desc "Build the native binary gem for #{platform}"
    task platform => "prepare" do
      RakeCompilerDock.sh <<~EOS, platform: platform
        bundle --local &&
        bundle exec rake native:#{platform} pkg/#{exttask.gem_spec.full_name}-#{platform}.gem --verbose
      EOS
    end
  end
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
