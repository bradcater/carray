# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'carray/version'

Gem::Specification.new do |spec|
  spec.name          = "carray"
  spec.version       = Carray::VERSION
  spec.authors       = ["Brad Cater"]
  spec.email         = ["bradcater@gmail.com"]
  spec.description   = %q{This gem is a collection of Array extensions for Arrays of Fixnums.}
  spec.summary       = %q{This gem is a collection of Array extensions for Arrays of Fixnums.}
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.extensions << "ext/carray/extconf.rb"

  spec.add_development_dependency "bundler", "~> 1.3"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "rake", ">= 1.9.1"
  spec.add_development_dependency "rspec", ">= 2.13.0"
end
