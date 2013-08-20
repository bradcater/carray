require "bundler/gem_tasks"
require "rake/extensiontask"
require "rspec/core/rake_task"

spec = Gem::Specification.load('carray.gemspec')
Rake::ExtensionTask.new('carray', spec)

desc "carray unit tests"
RSpec::Core::RakeTask.new(:spec) do |t|
  t.pattern = "spec/*_spec.rb"
  t.verbose = true
end

task :default => [:compile, :spec]
