#!/usr/bin/ruby
# -*- ruby -*-

require 'rubygems'
require 'rake/extensiontask'

task "test" => ["lib/statsamplert.so"]

spec=eval(File.read("statsample-optimization.gemspec"))

Gem::PackageTask.new(spec) do |pkg|
end


Rake::ExtensionTask.new('statsamplert',spec) do |ext|
  ext.cross_compile= true
  ext.cross_platform= "i386-mingw32"
  ext.cross_config_options << "--with-something"
  ext.cross_compiling do |gem_spec|
    gem_spec.post_install_message = "You installed the binary version of the gem!"
  end
end

# vim: syntax=ruby
