# -*- encoding: utf-8 -*-
#require File.expand_path("../lib/statsamplert", __FILE__)

Gem::Specification.new do |s|
  s.name = "statsamplert"
  s.version = "0.2.0"
  s.platform = Gem::Platform::RUBY
  s.authors = ['Claudio Bustos']
  s.email = []
  s.homepage = "http://rubygems.org/gems/distribution"
  s.summary = "Distribution"
  s.description = "Distribution"

  s.required_rubygems_version = ">= 1.3.6"
  s.add_development_dependency "bundler", ">= 1.0.0"
  s.add_development_dependency "rspec"
  s.files = `git ls-files`.split("\n")
  s.executables = `git ls-files`.split("\n").map{|f| f =~ /^bin\/(.*)/ ? $1 : nil}.compact
  s.require_path = 'lib'
end
