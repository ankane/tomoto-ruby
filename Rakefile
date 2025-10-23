require "bundler/gem_tasks"
require "rake/testtask"
require "rake/extensiontask"
require "rake_compiler_dock"

Rake::TestTask.new do |t|
  t.pattern = "test/**/*_test.rb"
end

task default: :test

RakeCompilerDock.set_ruby_cc_version("~> 3.2")
ENV["MACOSX_DEPLOYMENT_TARGET"] = "11"

platforms = [
  "x86_64-linux",
  "aarch64-linux",
  "x86_64-darwin",
  "arm64-darwin",
  "x64-mingw-ucrt",
  "x64-mingw32"
]

gemspec = Bundler.load_gemspec("tomoto.gemspec")
Rake::ExtensionTask.new("tomoto", gemspec) do |ext|
  ext.ext_dir = "ext/tomoto"
  ext.lib_dir = "lib/tomoto"
  ext.cross_compile = true
  ext.cross_platform = platforms
  ext.cross_compiling do |spec|
    spec.dependencies.reject! { |dep| dep.name == "rice" }
    spec.files.reject! { |file| File.fnmatch?("vendor/**.{c,cpp,h,hpp}", file, File::FNM_EXTGLOB) }
  end
end

namespace :gem do
  task :prepare do
    require "rake_compiler_dock"
    sh "bundle", "config", "set", "cache_all", "true"
    sh "bundle", "package"
  end

  platforms.each do |platform|
    desc "Build the native binary gems"
    multitask native: platform

    desc "Build the native binary gem for #{platform}"
    task platform => :prepare do
      RakeCompilerDock.sh <<~EOS, platform: platform
        bundle --local &&
        bundle exec rake native:#{platform} pkg/#{gemspec.full_name}-#{platform}.gem --verbose
      EOS
    end
  end
end

task :release_platform do
  require_relative "lib/tomoto/version"

  Dir["pkg/tomoto-#{Tomoto::VERSION}-*.gem"].each do |file|
    sh "gem", "push", file
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
